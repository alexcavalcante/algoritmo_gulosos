////============================================================================
//// Name        : dijkstra.cpp
//// Author      : Alex Cavalcante
//// Version     :
//// Copyright   : 2018.1
//// Description : Caminho Minimo - Dijkstra
////============================================================================

#include<bits/stdc++.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <stdio.h>
#include <limits.h>

using namespace std;


/* Função para encontrar o vértice com valor mínimo de distância, de
 conjunto de vértices ainda não incluídos na árvore de caminho minimo */
int minDistance(vector<int>& dist,int V, vector<bool> sptSet)
{
   //inicializa valor minimo com um valor alto.
   int min = INT_MAX, min_index;

   for (int v = 0; v < V; v++)
     if (sptSet[v] == false && dist[v] <= min)
         min = dist[v], min_index = v;

   return min_index;
}

//Função para imprimir a matriz de distância construída
int printSolution(vector<int>& dist, int n)
{
   printf("Vertex   Distance from Source\n");
   for (int i = 0; i < n; i++)
      printf("%d tt %d\n", i, dist[i]);
}

// Função que implementa o algoritmo de Dijkstra de Caminho minimo
// usando representação de Matrix de Adjacencia.
void dijkstra(vector<vector<int>>& graph, int V, int src)
{

     vector<int> dist(V);   //dist [i] manterá a menor distância do vertice de origem para o destino

     vector<bool> sptSet(V);    // variavel para saber se o vértice de destino foi incluído no menor caminho da árvore
                                // ou menor distância da origem para destino é finalizado

     // inicializa todas as distancias com INFINITO e stpSet[] com false
     for (int i = 0; i < V; i++)
        dist[i] = INT_MAX, sptSet[i] = false;

     // A distância do vértice origem para si mesmo é sempre 0
     dist[src] = 0;

     // Encontre o caminho mais curto para todos os vértices
     for (int count = 0; count < V-1; count++)
     {
       // Escolha o vértice de distância mínima do conjunto de vértices ainda não processados.
       //U é sempre igual a src na primeira iteração.
       int u = minDistance(dist,V, sptSet);

       // Marcar o vértice escolhido como processado
       sptSet[u] = true;

       // Atualiza o valor de dist dos vértices adjacentes do vértice escolhido.
       for (int v = 0; v < V; v++)

         // Atualiza dist[v] somente se não estiver em sptSet,
         // existe uma aresta de u para v e o peso total do caminho de src para v até u é menor que o valor atual de dist [v]
         if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX
                                       && dist[u]+graph[u][v] < dist[v])
            dist[v] = dist[u] + graph[u][v];
     }

    // imprime a matriz de distância construída
     printSolution(dist, V);
}

vector<vector<int>> LerMatriz(vector<vector<int>>& matriz, ifstream& file, int tam)
{
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

int main(int argc, char* argv[])
{
    string url = argv[1];

    int n, value;

    vector<vector<int>> matriz;

    ifstream file(url);

    file >> n;

    matriz = LerMatriz(matriz, file, n);

    dijkstra(matriz,n, 0);

    return 0;
}
