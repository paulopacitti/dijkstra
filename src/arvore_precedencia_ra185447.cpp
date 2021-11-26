#include <algorithm>
#include <limits.h>
#include <string>
#include <typeinfo>
#include <unordered_set>
#include <vector>

#include "grafo.hpp"
#include "arvore_precedencia_ra185447.hpp"

using namespace std;

bool arvore_precedencia(int n, int m, int W, Grafo g, string &mensagem, int RA, int pred[], int dist[]) {
  if (!check_max_weight(g, mensagem) || !check_int_weight(g, mensagem))
    return false;

  modified_dijkstra(0, g, pred, dist);
  return true;
}

void modified_dijkstra(int s, Grafo g, int pi[], int dist[]){
  vector<unordered_set<int>> vertices_array(g.V*g.W + 1); // vector where a vertex v is in index "i" if dist[v] = i
  vector<int> next_index_heap; // min-heap indicating which is the min index of vertices_array that contains a vertex

  // INITIALIZE-SINGLE-SOURCE
  for (int v = 0; v < g.V; v++) {
    dist[v] = (g.V-1)*g.W; // the maximum distance possible in this case will be (g.V-1)*g.W (inifinite)
    pi[v] = -1;
    if(v != s)
      vertices_array[(g.V-1)*g.W].insert(v); // insert all vertices with size infinite
  }
  dist[s] = 0; // init "s" dist
  vertices_array[0].insert(s);
  next_index_heap.push_back(0);
  next_index_heap.push_back((g.V-1)*g.W); // indicates that there are vertices with "infinite" value

  for (int i = 0; i < g.V; i++) {
    make_heap(next_index_heap.begin(), next_index_heap.end(), greater<int>()); // heapify
    int j = next_index_heap.at(0); // extract the vertice with min dist
    int v = *(vertices_array[j].begin()); // get the first value of the set with min distance
    vertices_array[j].erase(v); // remove from the set

    if(vertices_array[j].size() == 0) // if there's not any more vertices in the set, remove from the min-heap
      next_index_heap.erase(next_index_heap.begin());

    for (auto u : g.adj[v]) {
      if (dist[u.first] > dist[v] + u.second) { // RELAX
        vertices_array[dist[u.first]].erase(u.first); // remove from current position, because min distance from s will change
        if (vertices_array[dist[u.first]].size() == 0) // if the set is empty, there's no more vertices to visit. Remove from heap.
          next_index_heap.erase(find(next_index_heap.begin(), next_index_heap.end(), dist[u.first]));
        
        dist[u.first] = dist[v] + u.second; // updates min-distance from s
        vertices_array[dist[u.first]].insert(u.first); // inserts in the set of vertices with distance with value dist[v] + u.second

        if(find(next_index_heap.begin(), next_index_heap.end(), dist[u.first]) == next_index_heap.end()) 
          next_index_heap.push_back(dist[u.first]); // if the new position that u was put is not in the heap, add it to the heap
        pi[u.first] = v; // u's parent is v
      }
    }
  }

  return;
}

bool check_max_weight(Grafo g, string &mensagem) {
  for (int v1 = 0; v1 < g.V; v1++)
    for (auto v2 : g.adj[v1]) {
      if(v2.second > g.W || v2.second < 0) {
        mensagem = "Erro: Existe peso fora do intervalo.";
        return false;
      }
    }
  return true;
}

// This method does not work because the routine that reads the input casts to integer. Graph implementation
// would have to accept float values and the whole code would have to be changed to work iwht non-integer weights,
// because C++ is statically typed language. Talknig to the PED, this verification will not be used.
bool check_int_weight(Grafo g, string &mensagem) {
  for (int v1 = 0; v1 < g.V; v1++)
    for (auto v2 : g.adj[v1]) {
      if(typeid(v2.second) != typeid(1)) { // check if it's integer
        mensagem = "Erro: Existe peso não inteiro.";
        return false;
      }
    }
  return true;
}