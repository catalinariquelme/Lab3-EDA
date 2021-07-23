// PROFESOR DE LABORATORIO: VIOLETA CHANG
// SECCION: A-1
//
// AUTORA
// NOMBRE: Catalina Riquelme Zamora
// RUT: 20.642.812-0

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "Grafo.h"
#include "ListaAdyacencia.h"


/*
Entradas: matriz(información grafo),inicio(vértice inicio)
Salida: -
Objetivo: 
*/
int* dijkstra(matrizGrafo* grafo,int inicio){
    //Se almacenan los vértices ya visitados
    int* visitado=(int*)malloc(sizeof(int)*grafo->vertices);
    int* padre=(int*)malloc(sizeof(int)*grafo->vertices);
    int* distancia=(int*)malloc(sizeof(int)*grafo->vertices); // o costo
    int* ruta=(int*)malloc(sizeof(int)*grafo->vertices);

    int** A = grafo->adyacencias;
    int** W = grafo->adyacencias;
    for(int i=0; i < grafo->vertices; i++){
        visitado[i] = false;
        padre[i] = NULL;
        ruta[i] = 0;

        if(A[inicio][i] > 0){
            distancia[i] = W[inicio][i];
        }
        else{
            //inicialmente parte en infinito
            distancia[i] = -1; //infinito
        }
    }

    distancia[inicio] = -1; //infinito
    visitado[inicio] = true;
    int posicionRuta = 0;

    while(quedanSinVisitar(visitado[n]) == true){
        int minimo;
        minimo = extraerMinimo(distancia,visitado);
        visitado[minimo] = true;
        listaAdyacencia* listaAdy = crearListaVacia();
        listaAdy = obtenerAdyacentes(grafo,minimo);
        listaAdyacencia* aux = listaAdy;

        while(aux != NULL){
            if(distancia[aux->inicio->peso] > distancia[minimo] + W[minimo,aux->inicio->peso]){
                distancia[aux->inicio->peso] = distancia[minimo] + W[minimo,aux->inicio->peso];
                padre[aux->inicio->peso] = minimo;
            }
            aux = aux->inicio->siguiente;
        }
        ruta[posicionRuta] = minimo;
        posicionRuta++;
    }
    return ruta;
}
	
	
	


int main(){
	char* archivo= "conexiones.in";
	return 0;
}




