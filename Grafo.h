#include <stdio.h>
#include <stdlib.h>

#include "ListaAdyacencia.h"

typedef struct matrizGrafo{
	int vertices; //número total de vertices
	int** adyacencias; // vertices adyacentes a determinado
}matrizGrafo;

/*
Entradas: vertices(int)
Salida: grafo
Objetivo: crea grafo de n vértices y m aristas
*/
matrizGrafo* crearGrafoVacio(int vertices) {
	matrizGrafo* grafo = (matrizGrafo*)malloc(sizeof(matrizGrafo));
	grafo->vertices = vertices;
	grafo->adyacencias = (int**)malloc(vertices * sizeof(int*));
	int i,j;
	for (i = 0; i < vertices; i++){
		grafo->adyacencias[i] = (int*)malloc(vertices * sizeof(int));
		for(j = 0;j<vertices;i++){
			grafo->adyacencias[i][j]=0;
		}
	}
	return grafo;
}

/*
Entradas: grafo, vetA(int), vertB(int)
Salida: 1 (son adyacentes)| 0 (no son adyacentes)
Objetivo: verifica si dos vértices son adyacentes
*/
int adyacenciaNodos(matrizGrafo * grafo, int vertA, int vertB) {
	if (grafo->adyacencias[vertA - 1][vertB - 1] == 1){
		return 1;
	}
	return 0;
}

/*
Entradas: grafo, vértice
Salida: lista
Objetivo: obtener adyacentes de un vértice
*/
listaAdyacencia* obtenerAdyacentes(matrizGrafo* grafo, int vertice){
	listaAdyacencia* lista = crearListaVacia();
	for(int i=0;i < grafo->vertices;i++){
		if(adyacenciaNodos(grafo,vertice,i)){
			insertarInicio(lista,i+1);
		}
	}
	return lista;
}

