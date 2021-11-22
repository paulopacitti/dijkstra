#include<algorithm>
#include <iostream>
#include <limits.h>
#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "grafo.hpp"
#include "arvore_precedencia_ra185447.hpp"

using namespace std;

bool arvore_precedencia(int n, int m, int W, Grafo g, string &mensagem, int RA, int pred[], int dist[]) {
  if (!check_weight(g, mensagem))
    return false;

  modified_dijkstra(0, g, pred, dist);
  return true;
}

void modified_dijkstra(int s, Grafo g, int pi[], int dist[]){
  vector<unordered_set<int>> vertices_array(g.V*g.W + 1);
  vector<int> next_index_heap;

  // INITIALIZE-SINGLE-SOURCE
  for (int v = 0; v < g.V; v++) {
    dist[v] = g.V*g.W; // infinite
    pi[v] = -1;
    if(v != s)
      vertices_array[g.V*g.W].insert(v); // insert all vertices with size infinite
  }
  dist[s] = 0; // init "s" dist
  vertices_array[0].insert(s);
  next_index_heap.push_back(0);
  next_index_heap.push_back(g.V*g.W);

  for (int i = 0; i < g.V; i++) {
    make_heap(next_index_heap.begin(), next_index_heap.end(), greater<int>()); // heapify
    int j = next_index_heap.at(0);
    int v = *(vertices_array[j].begin()); // get the first value of the set
    vertices_array[j].erase(v);
    if(vertices_array[j].size() == 0)
      next_index_heap.erase(next_index_heap.begin());

    for (auto u : g.adj[v]) {
      if (dist[u.first] > dist[v] + u.second) {
        vertices_array[dist[u.first]].erase(u.first);
        if (vertices_array[dist[u.first]].size() == 0)
          next_index_heap.erase(find(next_index_heap.begin(), next_index_heap.end(), dist[u.first]));
        dist[u.first] = dist[v] + u.second;
        vertices_array[dist[u.first]].insert(u.first);
        if(find(next_index_heap.begin(), next_index_heap.end(), dist[u.first]) == next_index_heap.end())
          next_index_heap.push_back(dist[u.first]);
        pi[u.first] = v;
      }
    }
  }

  return;
}

bool check_weight(Grafo g, string &mensagem) {
  for (int v1 = 0; v1 < g.V; v1++)
    for (auto v2 : g.adj[v1]) {
      if(v2.second > g.W) {
        mensagem = "Erro: Existe peso fora do intervalo.";
        return false;
      }
    }
  return true;
}

void print_solution(int dist[], int V, int parent[]) {
  int src = 0;
  cout << "Origem -> Destino | Dist | Caminho" << endl;
  for (int i = 1; i < V; i++) {
      cout << src << " -> " << i << " | " << dist[i] << " | ";
      print_path(parent, i);
      cout << endl;
  }
}

void print_path(int parent[], int i) {  
  if(parent[i] == -1)
    return;
  
  print_path(parent, parent[i]);
  cout << i << " ";
}

bool is_strongly_connected(Grafo g) {
  vector<bool> visited;
  visited.assign(g.V, false); // mark all the vertices as not visited

  // find the first vertex with non-zero degree
  int v;
  for (v = 0; v < g.V; v++)
    if (g.adj[v].size() > 0)
      break;

  dfs_visit(v, g, visited); // do DFS traversal

  for (int i = 0; i < g.V; i++) // if DFS some vertex was not visited, it's not strongly connected
    if (visited[i] == false)
      return false;

  Grafo g_transposed = get_transpose(g); // create a graph with reversed edges
  visited.assign(g.V, false);

  dfs_visit(v, g_transposed, visited); // starting Vertex must be same starting point of first DFS

  for (int i = 0; i < g_transposed.V; i++) // if DFS some vertex was not visited, it's not strongly connected
    if (visited[i] == false)
      return false;

  return true;
}

void dfs_visit(int v, Grafo g, vector<bool> &visited)
{
  visited[v] = true; // mark the current node as visited

  for (auto e : g.adj[v]) // recursive
    if (!visited[e.first])
      dfs_visit(e.first, g, visited);
}

Grafo get_transpose(Grafo g) {
  Grafo result(g.V, g.M, g.W); // create a new graph with same size

  for (int v = 0; v < g.V; v++) // reverse edges
    for (auto e : g.adj[v])
      result.adj[e.first].push_back(make_pair(v, e.second));

  return result;
}

bool check_degrees(Grafo g) {
  unordered_map<int, int> degrees;

  for (int v1 = 0; v1 < g.V; v1++)
    for (auto v2 : g.adj[v1]) {
      if (degrees.find(v1) != degrees.end())
        degrees[v1] -= 1; // in-degree
      else
        degrees[v1] = -1; // out-degree

      if (degrees.find(v2.first) != degrees.end())
        degrees[v2.first] += 1; // in-degree
      else
        degrees[v2.first] = 1; // out-degree
    }

  for (auto p : degrees)
    if (p.second != 0)
      return false;

  return true;
}