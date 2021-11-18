#include <string>
#include <unordered_map>
#include <vector>
#include <queue>
#include <limits.h>

#include "grafo.hpp"
#include "arvore_precedencia_ra185447.hpp"

bool arvore_precedencia(int n, int m, int W, Grafo g, string &mensagem, int RA, int pred[], int dist[]) {
  if (!check_degrees(g) || !is_strongly_connected(g) || check_weight(g, mensagem))
    return false;

  return true;
}

bool modified_dijkstra(int s, Grafo g, int pred[], int dist[]){
  vector<vector<int>> vertices_array(g.M*g.W);
  priority_queue<int, vector<int>, greater<int>> next_index_heap;

  // INITIALIZE-SINGLE-SOURCE
  for (int v = 0; v < g.V; v++) {
    dist[v] = INT_MAX;
    pred[v] = NULL;
  }
  dist[s] = 0;


}

bool check_weight(Grafo g, string &mensagem){
  for (int v1 = 0; v1 < g.V; v1++)
    for (auto v2 : g.adj[v1]) {
      if(v2.second > g.W) {
        mensagem = "Erro: Existe peso fora do intervalo.";
        return false;
      }
    }
  return true;
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