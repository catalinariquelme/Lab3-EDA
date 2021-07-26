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
        if(distancia[i] < minimo && visitado[i] == 0 && distancia[i]!= -1){
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
    printf("\nVertice inicial: %d\n",inicio);
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
    //La distancia mínima para el vértice inical es 0
    distancia[inicio] = 0;
    //Se marca el vertice inicial como alcanzado (1)
    visitado[inicio] = 1;
    int posicionRuta = 0;

    printf("Visitados:");
    for(int i=0;i<grafo->vertices;i++){
        printf("%d,",visitado[i]);
    }
    printf("\n");

    printf("Distancia:");
    for(int i=0;i<grafo->vertices;i++){
        printf("%d,",distancia[i]);
    }
    printf("\n\n");

    //Mientras queden vértices por visitar
    while(esVacioVisitados(visitado,grafo) == 0){
        int minimo;
        //Se escoge el vértice no visitado con distancia más baja
        minimo = extraerMinimo(distancia,visitado,grafo->vertices);
        printf("Minimo extraido: %d\n",minimo);
        //Se marca como visitado el vértice escogido
        visitado[minimo] = 1;
        listaAdyacencia* listaAdy = crearListaVacia();
        //Se obtienen los adyacentes de este
        listaAdy = obtenerAdyacentes(grafo,minimo);
        printf("Adyacentes: ");
        recorrerLista(listaAdy);
        nodoListaAdyacencia* aux = listaAdy->inicio;

        //Para el vértice actual, se calcula la distancia para llegar a cada uno de sus vecinos
        while(aux != NULL){
            if(distancia[aux->dato] > distancia[minimo] + *W[minimo,aux->dato]){
                distancia[aux->dato] = distancia[minimo] + *W[minimo,aux->dato];
                padre[aux->dato] = minimo;
            }
            aux = aux->siguiente;
        }
        ruta[posicionRuta] = minimo;
        posicionRuta++;

        printf("Visitados:");
        for(int i=0;i<grafo->vertices;i++){
            printf("%d,",visitado[i]);
        }
        printf("\n");

        printf("Distancia:");
        for(int i=0;i<grafo->vertices;i++){
            printf("%d,",distancia[i]);
        }
        printf("\n\n");

    }
    printf("Tengo la ruta\n");
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

    int* ruta=(int*)malloc(sizeof(int)*grafo->vertices);

    ruta = dijkstra(grafo,0);
    
    printf("Sali Dijkstra\n");
	return 0;
}




