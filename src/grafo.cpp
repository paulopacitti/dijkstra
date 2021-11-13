#include <iostream>
#include <list>
#include <string>
#include "grafo.hpp"

using namespace std;

Grafo::Grafo(int V, int M, int W){
	this->V = V; 
    this->M = M;
	this->W = W;
	adj = new list<pair<int, int> >[V]; 
}

// Criação da aresta (v1, v2) em G.
void Grafo::adicionarAresta(int v1, int v2, int cust){
	adj[v1].push_back(make_pair(v2, cust));
}
