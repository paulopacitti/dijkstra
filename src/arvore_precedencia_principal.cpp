/*
arvore_precedencia_principal

Arquio principal para a execução do segundo trabalho prático de MC558.
Qualquer dúvida ou problema com o código, mandar um e-mail para:
hismael.costa@gmail.com
*/

#include <iostream>
#include <list>
#include <fstream>
#include <sstream>
#include <string>
#include "grafo.hpp"
#include "arvore_precedencia_ra185447.hpp"

using namespace std;

// Leitura de um arquivo txt e retorno do grafo descrito neste arquivo.
Grafo criarGrafo(string file) {
    ifstream inFile(file.c_str());
    string line;

    // Caso exista algum problema na leitura, um erro será disparado.
    if (!inFile.is_open()) {
        cout << "Erro: Problema na leitura do grafo." << endl;
        return Grafo(0, 0, 0);
    }

    getline(inFile, line);
    istringstream ss(line);

    // Identificação da quantidade de vértices e arestas contidos na primeira linha do arquivo.
    int n, m, W;
    ss >> n >> m >> W;

    // Criação do objeto tipo Grafo.
    Grafo grafo(n, m, W);

    while (getline(inFile, line)) {
        istringstream ss(line);
        int v1, v2, cust;
        ss >> v1 >> v2 >> cust;
        // Criação das arestas contidas nas demais linhas do arquivo.
        grafo.adicionarAresta(v1, v2, cust);
    }

    return grafo;
}

int main() {
  string file = "../tests/teste_5_nos.txt";
  Grafo graph = criarGrafo(file);

  int *pi = new int[graph.V]; // List containing the parent of each vertex in the shortest path from s
  int *dist = new int[graph.V];
  string message = ""; // error message
  int RA = 185447;

  bool has_tree = arvore_precedencia(graph.V, graph.M, graph.W, graph, message, RA, pi, dist);
  if (RA == -1) {
    cout << "Erro: RA informado eh invalido." << endl;
    return 0;
  } 
  if (!has_tree) {
    cout << message << endl;
    return 0;
  } 

  for(int i = 0; i < graph.V; i++) {
    if(dist[i] == (graph.V-1)*graph.W)
      cout << i << " INF" <<  endl;
    else
      cout << i << " " << dist[i] <<  endl;
  }

  return 0;
}