#include <stdio.h>
#include <stdlib.h>

#include "ListaAdyacencia.h"

typedef struct matrizGrafo{
	int vertices; //número total de vertices
	int** adyacencias; // vertices adyacentes a determinado
}matrizGrafo;

/*
Entradas: vertices(número de vertices del grafo)
Salida: grafo
Objetivo: crea un grafo vacío con n vertices
*/
matrizGrafo* crearGrafoVacio(int vertices) {
	matrizGrafo* grafo = (matrizGrafo*)malloc(sizeof(matrizGrafo));
	grafo->vertices = vertices;
	grafo->adyacencias = (int**)malloc(vertices * sizeof(int*));
	int i,j;
	for (i = 0; i < vertices; i++) {
		grafo->adyacencias[i] = (int*)malloc(vertices * sizeof(int));
		for(j=0;j<vertices;j++){
			grafo->adyacencias[i][j] = 0;
		}	
	}
	return grafo;
}

void imprimirMatrizAdyacencia(matrizGrafo* grafo){
	int i, j;
	
	for (i = 0; i < grafo->vertices; i++) {
		for (j = 0; j < grafo->vertices; j++){
			printf("%d ", grafo->adyacencias[i][j]);
		}
		printf("\n");
	}
}

int adyacenciaNodos(matrizGrafo * grafo, int vertA, int vertB) {
	if (grafo->adyacencias[vertA - 1][vertB - 1] == 1){
		return 1;
	}
	return 0;
}

matrizGrafo* leerGrafo(char * nombreArchivo){
    FILE* arch;
    arch = fopen(nombreArchivo,"r");
    int n, aristas;
    int i,j,k;
    fscanf(arch,"%d %d",&n,&aristas);
    matrizGrafo * graph = crearGrafoVacio(n);
    for(k=0;k<aristas;k++){
        fscanf(arch,"%d %d", &i, &j);
        graph->adyacencias[i-1][j-1] = 1;
        graph->adyacencias[j-1][i-1] = 1;
    }
    fclose(arch);
    return graph;
}



