/*
  RA 185447
  Paulo Pacitti
  MC558 - TP II
*/

#ifndef arvore_precedencia_ra185447_HPP
#define arvore_precedencia_ra185447_HPP

#include "grafo.hpp"

bool arvore_precedencia(int n, int m, int W, Grafo g, string &mensagem, int RA, int pred[], int dist[]);
void modified_dijkstra(int s, Grafo g, int pi[], int dist[]);
bool check_max_weight(Grafo g, string &mensagem);
bool check_int_weight(Grafo g, string &mensagem);
#endif