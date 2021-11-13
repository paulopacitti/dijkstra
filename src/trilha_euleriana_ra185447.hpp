/*
 * MC558
 * Paulo Pacitti
 * RA 185447
*/

#ifndef trilha_euleriana_ra185447_HPP
#define trilha_euleriana_ra185447_HPP

using namespace std;
#include <vector>
#include "Grafo.hpp"

bool check_degrees(Grafo g); // check if all vertices have indegree == outdegree
Grafo copiar_grafo(Grafo g); // create a copy of a Grafo
void dfs_visit(int v, Grafo g, vector<bool> &visited); // check if all vertices are visited in a DFS 
Grafo get_transpose(Grafo g); // create a tranposed version of a Grafo
vector<int> hierholzer(Grafo g); // find a euleuriand circuit
bool is_strongly_connected(Grafo g); // check if a Grafo is strongly connected
bool trilha_euleriana(int n, int m, Grafo g, int origem[], int destino[], int trilha[], string& mensagem, int RA); // check if has a euleurian cricuit and return it 

#endif