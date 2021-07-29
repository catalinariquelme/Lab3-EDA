// PROFESOR DE LABORATORIO: VIOLETA CHANG
// SECCION: A-1
//
// AUTORA
// NOMBRE: Catalina Riquelme Zamora
// RUT: 20.642.812-0

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Grafo.h"

/*
Entradas: nombre (nombre archivo a leer),capacidadArr(int*), subsidio(int)
Salida: subsidio (int)
Objetivo: leer la capacidad y subsidio de los vértices
*/
int lecturaInsumos(char* nombre,int* capacidadArr,int subsidio){
    FILE* arch;
    arch = fopen(nombre,"r");
    if(arch == NULL){
        printf("No existe el archivo\n");
        exit(1);
    }
    int centroTotales;
    fscanf(arch,"%d %d",&centroTotales,&subsidio);

    while(feof(arch) == 0){
        int idCentro,capacidad;
        fscanf(arch,"%d %d",&idCentro,&capacidad);
        capacidadArr[idCentro]=capacidad;
    }
    fclose(arch);
    return subsidio;
}

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
        if(visitados[i] == 0){
            return 0;
        }
    }
    return 1;
}

/*
Entradas: distancia (int*),visitado(int*)
Salida: int
Objetivo: extaer distancia mínima
*/
int extraerMinimo(int* distancia,int* visitado, int largo){
    int minimo,idMinimo;
    minimo = 999999999;
    for(int i=0; i< largo;i++){
        if(distancia[i] < minimo && visitado[i] == 0){
            minimo = distancia[i];
            
            idMinimo = i;
            //printf("Id: %d\n",idMinimo);
        }
    }
    return idMinimo;
}

/*
Entradas: matriz(información grafo),inicio(vértice inicio)
Salida: -
Objetivo: calcular camino mínimo
*/
int* dijkstra(matrizGrafo* grafo,int inicio){
    //Se almacenan los vértices ya visitados
    int* visitado=(int*)malloc(sizeof(int)*grafo->vertices);
    int* padre=(int*)malloc(sizeof(int)*grafo->vertices);
    int* distancia=(int*)malloc(sizeof(int)*grafo->vertices); // o costo
    int* ruta=(int*)malloc(sizeof(int)*grafo->vertices);

    int** A = grafo->adyacencias;

    for(int i=0; i < grafo->vertices; i++){
        visitado[i] = 0; // 0 = no visitado
        padre[i] = -1; //NULL

        if(A[inicio][i] > 0){
            distancia[i] = A[inicio][i];
        }
        else{
            distancia[i] = 99999999; //infinito
        }
    }
    //La distancia mínima para el vértice inical es 0
    distancia[inicio] = 0;
    //Se marca el vertice inicial como alcanzado (1)
    visitado[inicio] = 1;
    int posicionRuta = 0;

    //Mientras queden vértices por visitar
    while(esVacioVisitados(visitado,grafo) == 0){
        int minimo;
        //Se escoge el vértice no visitado con distancia más baja
        minimo = extraerMinimo(distancia,visitado,grafo->vertices);
        //Se marca como visitado el vértice escogido
        visitado[minimo] = 1;
        listaAdyacencia* listaAdy = crearListaVacia();
        //Se obtienen los adyacentes de este
        listaAdy = obtenerAdyacentes(grafo,minimo);

        nodoListaAdyacencia* aux = listaAdy->inicio;
        //Para el vértice actual, se calcula la distancia para llegar a cada uno de sus vecinos
        while(aux != NULL){
            int peso;
            peso = A[minimo][aux->dato];
            
            if(distancia[aux->dato] > (distancia[minimo] + peso)){
                distancia[aux->dato] = distancia[minimo] + peso;
                padre[aux->dato] = minimo;
            }
            aux = aux->siguiente;
        }
        ruta[posicionRuta] = minimo;
        posicionRuta++;
    }
    free(visitado);
    free(padre);
    free(distancia);
    return ruta;
}

/*
Entradas: distancia(int), peso(int), subsidio(int)
Salida: costo (int)
Objetivo: calcular el costo
*/
int calculoCosto(int distancia,int peso,int subsidio){
    //printf("d: %d   peso: %d    subsidio: %d\n",distancia,peso,subsidio);
    int costo;
    costo = (distancia*peso)/subsidio;
    return costo;
}

/*
Entradas: capacidad(int*), vertices(int)
Salida: capacidadTotal (int)
Objetivo: calcular capacidad total, sumando cada una
*/
int calculoCapacidad(int*capacidad,int vertices){
    int capacidadTotal = 0;
    for(int i=0;i<vertices ;i++){
        capacidadTotal = capacidadTotal + capacidad[i];
    }
    return capacidadTotal;
}

/*
Entradas: ruta(int*),grafo(matrizGrafo*),inicio(int* vértice por el cual se comienza)
Salida: distancia (int)
Objetivo: calcular la distancia recorrida al seguir una determinada ruta
*/
int calculoDistancia(int*ruta,matrizGrafo* grafo,int inicio){
    int distancia = 0;
    int** matriz = grafo->adyacencias;
    for(int i=0;i<grafo->vertices-1;i++){
        distancia = distancia + matriz[inicio][ruta[i]];
        inicio = ruta[i];
    }
    return distancia;
}

/*
Entradas: capacidadTotal(int), subsidio(int),ruta(int* ruta mínima), grafo(matrizGrafo*)
Salida: -
Objetivo: escribir un archivo con la información requerida
*/
void salidaArchivo(int capacidadTotal,int subsidio,int* ruta,matrizGrafo *grafo,int costeMinimo){
  FILE* arch;
  arch = fopen("salida.out","w");

    fputs("Capacidad: ",arch);
    char buffer[20];
    itoa(capacidadTotal,buffer,10);
    fputs(buffer,arch);
    fputs(" ton\n",arch);

    fputs("Subsidio: ",arch);
    itoa(subsidio,buffer,10);
    fputs(buffer,arch);
    fputs(" um\n",arch);

    fputs("Coste minimo: ",arch);
    itoa(costeMinimo,buffer,10);
    fputs(buffer,arch);
    fputs(" um\n",arch);

    fputs("Ruta: Centro",arch);

    for(int i=0;i< grafo->vertices;i++){
        if (ruta[i] == 0){
            break;
        }
        fputs("->",arch);
        itoa(ruta[i],buffer,10);
        fputs(buffer,arch);
    }

  fclose(arch);
}

int main(){
    printf("LABORATORIO 3 EDA\n");
    //clock_t start, finish, duration;
    //start = clock();

    //Se lee el archivo conexiones con el fin de obtener la cantidad de vértices
    int vertices = lecturaVertices("conexiones.in");
    matrizGrafo* grafo = crearGrafoVacio(vertices);
    //Se lee el archivo con el fin de almacenas la información del grafo
    grafo = lecturaGrafo("conexiones.in");

    //Se define el vértice inicial
    int verticeInicial = 0;
    int* ruta=(int*)malloc(sizeof(int)*grafo->vertices);
    //Se llama la función Dijkstra con la finalidad de obtener el camino mínimo
    ruta = dijkstra(grafo,verticeInicial);
    int distanciaRecorrida;
    distanciaRecorrida = calculoDistancia(ruta,grafo,verticeInicial);

    //Se lee el archivo insumos con la finalidad de obtener la información respecto a esta
    int subsidio;
    int *capacidad = (int*)malloc(sizeof(int)*vertices);
    for(int i=0;i<vertices ;i++){
        capacidad[i] = 0;
    }
    subsidio = lecturaInsumos("insumos.in",capacidad,subsidio);

    //Se calcula la capacidad llamando a la función calculoCapacidad
    int capacidadTotal;
    capacidadTotal= calculoCapacidad(capacidad,vertices);

    // Se calcula el costo llamando a la función calculoCosto
    int costoTotal;
    costoTotal = calculoCosto(distanciaRecorrida,capacidadTotal,subsidio);

    //Se muestra por pantalla la información solicitada
    printf("------------------------\n");
    printf("Capacidad: %d ton\n",capacidadTotal);
    printf("Subsidio: %d um\n",subsidio);
    printf("Coste minimo: %d um\n",costoTotal);
    printf("Ruta: ");
    printf("Centro");
    for(int i=0;i<grafo->vertices ;i++){
        if (ruta[i]==0){
            break;
        }
        printf("->%d",ruta[i]);
    }
    printf("\n------------------------\n");
    //Se impime la información mostrada por pantalla
    salidaArchivo(capacidadTotal,subsidio,ruta,grafo,costoTotal);
    printf("Se escribio un archivo con la informacion mostrada");
    //finish = clock();
    //printf("process() took %f seconds to execute\n", ((double) (finish - start)) / CLOCKS_PER_SEC );
	free(ruta);
    free(capacidad);
    return 0;
}
