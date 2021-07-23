#include <stdio.h>
#include <stdlib.h>

typedef struct nodoListaAdyacencia{
  int destino; // vertice de destino
  int peso; // costo del movimiento
  struct nodoListaAdyacencia* siguiente; //siguiente nodo
}nodoListaAdyacencia;

//Adyacentes a determinado vértice 
typedef struct listaAdyacencia{
  nodoListaAdyacencia* inicio; // inicio lista enlazada
}listaAdyacencia;


listaAdyacencia* crearListaVacia(){
  listaAdyacencia * lista=(listaAdyacencia*)malloc(sizeof(listaAdyacencia));
  lista->inicio=NULL;
  return lista;
}

int esListaVacia(listaAdyacencia * lista){
  if (lista->inicio == NULL)
    return 1;
  else
    return 0;
}

void recorrerLista(listaAdyacencia * lista){
  if (!esListaVacia(lista)){
    nodoListaAdyacencia * auxiliar=lista->inicio;
    while (auxiliar!=NULL){
      printf("%d ",auxiliar->destino);
      auxiliar=auxiliar->siguiente;
    }
    printf("\n");
  }
  else
    printf("La lista está vacía\n");
}

void insertarInicio(listaAdyacencia * lista, int destino){
  nodoListaAdyacencia * nuevo=(nodoListaAdyacencia*)malloc(sizeof(nodoListaAdyacencia));
  nuevo->destino=destino;
  nuevo->siguiente = lista->inicio;
  lista->inicio=nuevo;
}

