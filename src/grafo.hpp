#ifndef GRAFO_HPP
#define GRAFO_HPP

#include <list>
using namespace std;

class Grafo {
	public:
		list<pair<int, int>> *adj; // Lista contendo as arestas
		int V;										 // Quantidade de vértices
		int M;										 // Quantidade de arestas
		int W;

		Grafo();
		Grafo(int V, int M, int W);
		void adicionarAresta(int v1, int v2, int cust);
};
#endif