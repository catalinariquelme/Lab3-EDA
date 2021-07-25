// PROFESOR DE LABORATORIO: VIOLETA CHANG
// SECCION: A-1
//
// AUTORA
// NOMBRE: Catalina Riquelme Zamora
// RUT: 20.642.812-0

#include <stdio.h>
#include <stdlib.h>


#include "Grafo.h"

/*
Entradas: nombre (nombre archivo a leer)
Salida: vertices
Objetivo: leer la cantidad de vertices en un archivo
*/
int lecturaVertices(char* nombre){
    FILE* arch;
    arch = fopen(nombre,"r");
    if(arch == NULL){
        printf("No existe el archivo\n");
        exit(1);
    }
    int aux, vertices;
    fscanf(arch,"%d %d",&vertices,&aux);
    fclose(arch);
    return vertices;
}


/*
Entradas: visitados(int*), grafo
Salida: 1 (esta vácio) | 0 (no esta vácio)
Objetivo: verificar si visitados se encuentra vácio 
*/
int esVacioVisitados(int* visitados, matrizGrafo* grafo){
    for(int i=0;i<grafo->vertices;i++){
        if(visitados[i] == 1){
            return 0;
        }
    }
    return 1;
}

/*
Entradas: distancia (int*),visitado(int*)
Salida: int
Objetivo: 
*/
int extraerMinimo(int* distancia,int* visitado, int largo){
    int minimo,idMinimo;
    minimo = 99999999;

    for(int i=0; i< largo;i++){
        if(distancia[i] < minimo && visitado[i] == 0){
            minimo = distancia[i];
            idMinimo = i;
        }
    }
    return idMinimo;
}

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
        visitado[i] = 0; // 0 = no visitado
        padre[i] = -1; //NULL
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
    visitado[inicio] = 1; // 1 = visitado
    int posicionRuta = 0;

    while(esVacioVisitados(visitado,grafo) == 0){
        int minimo;
        minimo = extraerMinimo(distancia,visitado,grafo->vertices);
        visitado[minimo] = 1;
        listaAdyacencia* listaAdy = crearListaVacia();
        listaAdy = obtenerAdyacentes(grafo,minimo);
        listaAdyacencia* aux = listaAdy;

        while(aux != NULL){
            if(distancia[aux->inicio->dato] > distancia[minimo] + W[minimo,aux->inicio->dato]){
                distancia[aux->inicio->dato] = distancia[minimo] + W[minimo,aux->inicio->dato];
                padre[aux->inicio->dato] = minimo;
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
    printf("Lectura grafos\n\n");
    int vertices = lecturaVertices(archivo);
    printf("Vertices: %d\n",vertices);
    matrizGrafo* grafo = crearGrafoVacio(vertices);
    grafo = lecturaGrafo(archivo);
    printf("Matriz adyacencia\n");
    imprimirMatrizAdyacencia(grafo);


	return 0;
}




