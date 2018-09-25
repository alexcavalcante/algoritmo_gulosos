//============================================================================
// Name        : kruskal.cpp
// Author      : Alex Cavalcante
// Version     :
// Copyright   : 2018.1
// Description : Algoritmos Gulosos - Kruskal
//============================================================================

#include<bits/stdc++.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string>
#include <fstream>
#include <cstdlib>
#include <sstream>

using namespace std;

void PrintMatrix(vector<vector<int>>& matriz, int size )
{
    cout << "Matriz Inicial: " << endl;

    for ( int i = 0; i < size; ++i )
    {
        for (int j = 0; j < size; ++j )
        {
            if( i == j )
                matriz[i][j] = 0;

            cout << matriz[i][j] << " ";
        }
        cout << endl;
    }

    cout <<  endl;
}
vector<vector<int>> LerMatriz(vector<vector<int>>& matriz, ifstream& file, int tam)
{
    //matrix = AlocarMatrix( tam, tam );
    int value;

    matriz.resize(tam);
    for(int i = 0 ; i < tam ; ++i)
    {
        //Grow Columns by n
        matriz[i].resize(tam);
    }

    for(int i = 0; i < tam-1; i++){
        for(int j = i + 1; j < tam; j++){
            file >> value;
            matriz[i][j] = value;
            matriz[j][i] = value;
        }
    }

    cout << "Size: " << tam << endl;
    //PrintMatrix(matriz, tam);

    return matriz;
}
// Creating shortcut for an integer pair
typedef  pair<int, int> iPair;

// Estrutura que representa o Grafo
struct Graph
{
    int V, E;
    vector< pair<int, iPair> > edges; //Vetor de arestas

    // Construtor, seta tamanho de acordo com o tamanho da tabela
    Graph(int V, int E)
    {
        this->V = V;
        this->E = E;
    }

    // Adiciona o par ordenado da aresta com seu peso.
    void addEdge(int u, int v, int w)
    {
        edges.push_back({w, {u, v}});
    }

    //Função para encontrar o MST usando o Kruskal
    int kruskalMST();
};

// Verifica se eles são conjuntos disjuntos
struct DisjointSets
{
    //int *parent, *rnk;
    vector<int> parent, ranks;
    int n;

    // Constructor.
    DisjointSets(int n)
    {
        // Inicialmente, todos os vértices estão em
         // arvores diferentes e tem peso 0.
        for (int i = 0; i <= n; i++)
        {
                ranks.push_back(0);
                // cada elemento é pai de si mesmo
                parent.push_back(i);
        }
    }

    // Encontre o pai de um nó 'u'
     // Compressão de caminho
    int find(int u)
    {
        /* Torna o pai dos nós no caminho
            de u -> parent[u] aponta para o parent[u] */
        if (u != parent[u]) //Se for diferente procura o pai de U
            parent[u] = find(parent[u]);
        return parent[u];
    }

    // União dos ranks
    void merge(int x, int y)
    {
        x = find(x), y = find(y);

       /* Faça árvore com menor altura
            uma subárvore da outra árvore */
        if (ranks[x] > ranks[y])
            parent[y] = x;
        else // If rnk[x] <= rnk[y]
            parent[x] = y;

        if (ranks[x] == ranks[y])
            ranks[y]++;
    }
};

 /*Funções retornam peso*/
int Graph::kruskalMST()
{
    int mst_wt = 0; // Inicializa o resultado

    // classifica as arestas em ordem crescente com base no peso
    sort(edges.begin(), edges.end());

    // Cria os conjuntos disjuntos
    DisjointSets ds(V);

    // Iterar em todas as arestas classificadas
    vector< pair<int, iPair> >::iterator it;
    for (it=edges.begin(); it!=edges.end(); it++)
    {
        int u = it->second.first;
        int v = it->second.second;

        int set_u = ds.find(u);
        int set_v = ds.find(v);

        // Verifique se a aresta selecionada está criando um ciclo ou não (ciclo é criado se u e v pertencem ao mesmo conjunto)
        if (set_u != set_v)
        {
            // A aresta atual estará no MST então imprima
            cout << u << " - " << v << endl;

            // Atualiza o peso da arvore
            mst_wt += it->first;

            // Junta os dois conjuntos
            ds.merge(set_u, set_v);
        }
    }

    return mst_wt;//retorna o peso
}

int main(int argc, char* argv[])
{
    string url = argv[1];

    int n, value;

    vector<vector<int>> matriz;

    ifstream file(url);

    file >> n;

    matriz = LerMatriz(matriz, file, n);
    PrintMatrix(matriz,n);

    /* Criação do grafo*/
    Graph g(n, n);

    /*Cria o grafo de acordo com a tabela, par ordenado e peso*/
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            g.addEdge(i, j, matriz[i][j]);

    cout << "Arestas da Arvore são: \n";
    int mst_wt = g.kruskalMST();

    cout << "\nPeso da Arvoré é:  " << mst_wt;

    return 0;
}
