#include <stdio.h>
#include <stdlib.h>

typedef struct nodoListaAdyacencia{
  int dato; 
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

void insertarInicio(listaAdyacencia* lista, int dato){
  nodoListaAdyacencia* nuevo=(nodoListaAdyacencia*)malloc(sizeof(nodoListaAdyacencia));
  nuevo->dato = dato;
  nuevo->siguiente = lista->inicio;
  lista->inicio=nuevo;
}

void recorrerLista(listaAdyacencia * lista){
  if (!esListaVacia(lista)){
    nodoListaAdyacencia * auxiliar=lista->inicio;
    while (auxiliar!=NULL){
      printf("%d ",auxiliar->dato);
      auxiliar=auxiliar->siguiente;
    }
    printf("\n");
  }
  else
    printf("La lista está vacía\n");
}


