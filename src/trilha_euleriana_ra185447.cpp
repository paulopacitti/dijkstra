/*
 * MC558
 * Paulo Pacitti
 * RA 185447
*/

#include <string>
#include <unordered_map>
#include <algorithm>
#include <stack>
#include <vector>

#include "trilha_euleriana_ra185447.hpp"
#include "Grafo.hpp"

using namespace std;

bool trilha_euleriana(int n, int m, Grafo g, int origem[], int destino[], int trilha[], string &mensagem, int RA) {
  if (!check_degrees(g)) {
    mensagem.assign("Erro: Existe vértice inviável.");
    return false;
  }

  if (!is_strongly_connected(g)) {
    mensagem.assign("Erro: Grafo não é fortemente conexo.");
    return false;
  }

  vector<int> circuit = hierholzer(copiar_grafo(g)); // run hierholzer's algorithm ina a copy of Grafo to preserve original one
  copy(circuit.begin(), circuit.end(), trilha); // copy vector content into int array
  for (int i = 0; i < circuit.size() - 1; i++) { // builds origem and destino
    origem[i] = circuit[i];
    destino[i] = circuit[i + 1];
  }

  return true;
}

vector<int> hierholzer(Grafo g) { // linear time, O(G.E)
  stack<int> current_path;   // stack to keep vertices
  vector<int> circuit;   // vector with final circuit

  current_path.push(0);  // start from first vertex

  while (!current_path.empty()) { 
    int current_vertex = current_path.top();

    if (!g.vizinhos[current_vertex].empty()) { // if there's remaining adjacent edge
      current_path.push(g.vizinhos[current_vertex].back());
      g.vizinhos[current_vertex].pop_back();
    }
    else { // backtrack
      circuit.push_back(current_path.top());
      current_path.pop();
    }
  }

  reverse(circuit.begin(), circuit.end()); // reverse euleurian circuit found
  return circuit;
}

bool is_strongly_connected(Grafo g) {
  vector<bool> visited;
  visited.assign(g.V, false);   // mark all the vertices as not visited

  // find the first vertex with non-zero degree
  int v;
  for (v = 0; v < g.V; v++)
    if (g.vizinhos[v].size() > 0)
      break;

  dfs_visit(v, g, visited);   // do DFS traversal

  for (int i = 0; i < g.V; i++)   // if DFS some vertex was not visited, it's not strongly connected
    if (visited[i] == false)
      return false;

  Grafo g_transposed = get_transpose(g);   // create a graph with reversed edges 
  visited.assign(g.V, false);

  dfs_visit(v, g_transposed, visited); // starting Vertex must be same starting point of first DFS

  for (int i = 0; i < g_transposed.V; i++)   // if DFS some vertex was not visited, it's not strongly connected
    if (visited[i] == false)
      return false;

  return true;
}

void dfs_visit(int v, Grafo g, vector<bool> &visited) {
  visited[v] = true; // mark the current node as visited

  for (auto i : g.vizinhos[v]) // recursive
    if (!visited[i])
      dfs_visit(i, g, visited);
}

Grafo get_transpose(Grafo g) {
  Grafo result(g.V, g.M); // create a new graph with same size

  for (int v = 0; v < g.V; v++) {  // reverse edges
    list<int>::iterator i;
    for (i = g.vizinhos[v].begin(); i != g.vizinhos[v].end(); ++i)
      result.vizinhos[*i].push_back(v);
  }
  return result;
}

bool check_degrees(Grafo g) {
  unordered_map<int, int> degrees;

  for (int v1 = 0; v1 < g.V; v1++)
    for (int v2 : g.vizinhos[v1]) {
      if (degrees.find(v1) != degrees.end())
        degrees[v1] -= 1; // in-degree
      else
        degrees[v1] = -1; // out-degree

      if (degrees.find(v2) != degrees.end())
        degrees[v2] += 1; // in-degree
      else
        degrees[v2] = 1; // out-degree
    }

  for (auto p : degrees)
    if (p.second != 0)
      return false;

  return true;
}

Grafo copiar_grafo(Grafo g) {
  Grafo h(g.V, g.M); // create a new graph with same size

  for (int v = 0; v < g.V; v++) // copy edges
    for (auto e : g.vizinhos[v])
      h.vizinhos[v].push_back(e);

  return h;
}