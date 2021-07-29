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
		for(j = 0;j<vertices;j++){
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
		if(grafo->adyacencias[vertice][i]!=0){
			insertarInicio(lista,i);
		}
	}
	return lista;
}

/*
Entradas: grafo
Salida: -
Objetivo: imprime los elementos de matriz de adyacencia
*/
void imprimirMatrizAdyacencia(matrizGrafo* grafo) {
	int i, j;
	for (i = 0; i < grafo->vertices; i++) {
		for (j = 0; j < grafo->vertices; j++) {
			printf("%d ", grafo->adyacencias[i][j]);
		}
		printf("\n");
	}
}

/*
Entradas: nombreArchivo(char)
Salida: grafo
Objetivo: lectura de archivo que tiene información gráfo
*/
matrizGrafo* lecturaGrafo(char *nombreArchivo){
	FILE*arch;
	arch = fopen(nombreArchivo,"r");
	int vertices, aristas;
	int i,j,peso;
	fscanf(arch, "%d %d", &vertices,&aristas); //Cantidad de nodos y aristas
	matrizGrafo *grafo=crearGrafoVacio(vertices);;
	//dependiendo de las lineas de archivo , pone 1 para grafo no dirigido
	for(int k=0; k<aristas;k++){
		fscanf(arch,"%d %d %d",&i, &j, &peso);
		grafo->adyacencias[i][j] = peso;
		grafo->adyacencias[j][i] = peso;
	}
	fclose(arch);
	return  grafo;	
}



