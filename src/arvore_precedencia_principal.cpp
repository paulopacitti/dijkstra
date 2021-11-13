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
    string file = "nome-do-arquivo.txt";
    Grafo grafo = criarGrafo(file);

    //Inicializem as variáveis
    int arvore[][];  // Lista contendo os vértices de origem de cada aresta na trilha.
    string mensagem; // String que retorna algum erro no momento da criação da trilha.
    int RA = -1;     // RA do aluno que deve ser preenchido na função que irá criar.

    bool tem_arvore = arvore_precedencia(grafo.V, grafo.M, grafo.W, grafo, &mensagem, RA, &arvore[0][0]);
    if (RA == -1) {
        cout << "Erro: RA informado eh invalido." << endl;
    } else if (!tem_arvore) {
        cout << mensagem << endl;
    } else {
        //Mostra a arvore de precedencia
    }

    //Mostra o caminho minimo de cada vértice

    return 0;
}