//============================================================================
// Name        : Prim.cpp
// Author      : Alex Cavalcante
// Version     :
// Copyright   : 2018.1
// Description : Arvore Geradora Minima - Prim
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

struct vertex{
   int numero;
   int peso;
};

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

//Função MinHeapify (struct, tamanho, valor)
void MinHeapFy( struct vertex vetor[], int size, int root)
{
   int pai = root; // inicializa o pai
	int filhoE = 2*root + 1; // filhoE = 2*i + 1
	int filhoD = 2*root + 2; // filhoD = 2*i + 2

	// Se filhoE for maior que a pai
	if (filhoE < size && (vetor[filhoE].peso < vetor[pai].peso))
		pai = filhoE;

	// Se filhoD é maior do que o maior até agora
	if (filhoD < size && (vetor[filhoD].peso < vetor[pai].peso))
		pai = filhoD;

	// Se pai não é a raiz
	if (pai != root)
	{
		swap(vetor[pai], vetor[root]);
		// Recursivo heapify a sub-arvore
		MinHeapFy(vetor, size, root);
	}
}

void CriaHeap(struct vertex arr[], int size)
{
   for( int i = (size)/2 - 1; i >= 0; i-- )
       MinHeapFy(arr, size-1, i);
}

struct vertex ExtrairMin( struct vertex arr[] , int* size )
{
   CriaHeap( arr, *size );

   struct vertex min = arr[0];

   arr[0] = arr[*size-1];

   *size -= 1;

   MinHeapFy(arr, *size, 0);

   return min;
}

/*Função (vetor, tamanho, id) */
bool PertenceGrafo(struct vertex arr[], int n, int id)
{
 for(int i=0;i<n;i++)
 {
   if(id == arr[i].numero)
       return true;
 }
 return false;
}

int Returnarpeso(struct vertex arr[], int size, int numero)
{
   for( int i = 0; i < size; ++i )
   {
       if(numero == arr[i].numero)
           return arr[i].peso;
   }
   return arr[numero].peso;
}

void Reduzir(struct vertex arr[] , int i, int key , int size )
{
   for( int j = 0; j < size; ++j )
   {
       if( i == arr[j].numero )
       {
           i=j;
           break;
       }
   }

   arr[i].peso = key;

   CriaHeap( arr, size );
}

void Prim(vector<vector<int>>& matriz, int size, int first )
{
   struct vertex adjvert[size]; //Array dos vertices adjacentes
   int dads[size] = {-1};

   for( int i = 0; i < size; ++i )
   {
       adjvert[i].numero = i;//Define a chave
       adjvert[i].peso = INT32_MAX; // Define o peso com o valor maximo
   }

   adjvert[first].peso = 0; // Define o primeiro com peso 0

   struct vertex Q[size];//Estrutura auxiliar

   for( int i = 0; i < size; ++i ) //Passa os valores do inicio para a auxiliar
       Q[i] = adjvert[i];

   CriaHeap( Q, size ); //Cria um Heap Minimo

   int sizeaux = size;

   while( size > 0 )
   {
       struct vertex u = ExtrairMin( Q, &size ); //Pega o vertice de menor valor

       adjvert[u.numero] = u;

       for( int i = 0; i < sizeaux; i++ )
       {
           if( matriz[u.numero][i] != 0 ) //Verifica na matriz se o valor é diferente de zero
           {
               if( ( PertenceGrafo(Q, size, i) ) && ( matriz[u.numero][i] < Returnarpeso(Q, size, i) ) ) //Verifica se pertence ao grafo e se é o menor
               {
                   dads[i] = u.numero; //Define o mesmo pai
                   Reduzir(Q , i , matriz[u.numero][i] , size); //Tira do heap
               }
           }
       }
   }

   int soma=0;

   for( int i = 0; i < sizeaux; ++i )
   {
       soma += adjvert[i].peso; //Calcula o valor do caminho.
   }

   cout << "\nSOMA: " << soma << endl;
}

void Dijkstra(vector<vector<int>>& matriz, int size, int primeiro )
{
   struct vertex adjvert[size];
   int pai[size] = {-1};

   for( int i = 0; i < size; ++i )
   {
       adjvert[i].numero = i;
       adjvert[i].peso = INT32_MAX;
   }

   adjvert[primeiro].peso = 0;

   struct vertex Q[size];

   for( int i = 0; i < size; ++i )
       Q[i] = adjvert[i];

   CriaHeap( Q, size );

   int sizeaux = size;

   while( size > 0 )
   {
       struct vertex u = ExtrairMin(Q, &size );

       adjvert[u.numero] = u;

       for( int i = 0; i < sizeaux; i++ )
       {
           if( matriz[u.numero][i] != 0 )
           {
               if( ( PertenceGrafo(Q , size, i) ) && ( matriz[u.numero][i] + u.peso < Returnarpeso(Q , size, i) ) )
               {
                   pai[i] = u.numero;
                   Reduzir(Q , i , matriz[u.numero][i] + u.peso , size);
               }
           }
       }
   }

   int soma=0;
   cout << "\nVertice   Distancia da Origem\n";
   for ( int i = 1; i < sizeaux; i++ )
   {
       for ( int j = i; j != 0; )
       {
           soma += matriz[j][pai[j]];
           j = pai[j];
       }

       cout << i << ": " << soma << "\n";
       soma = 0;
   }
}

int main(int argc, char* argv[])
{
       string url = argv[1];

       int n, value;

       vector<vector<int>> matriz;

       ifstream file(url);

       file >> n;

       matriz = LerMatriz(matriz, file, n);

       Prim( matriz, n, 0);


   return 0;
}
