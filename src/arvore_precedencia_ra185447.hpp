#ifndef arvore_precedencia_ra185447_HPP
#define arvore_precedencia_ra185447_HPP

#include <vector>
#include "grafo.hpp"

bool arvore_precedencia(int n, int m, int W, Grafo g, string &mensagem, int RA, int pred[], int dist[]);
void modified_dijkstra(int s, Grafo g, int pi[], int dist[]);
bool check_weight(Grafo g, string &mensagem);

bool is_strongly_connected(Grafo g);
void dfs_visit(int v, Grafo g, vector<bool> &visited);
Grafo get_transpose(Grafo g);
bool check_degrees(Grafo g);

#endif