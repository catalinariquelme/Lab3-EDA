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

/*
Entradas: -
Salida: lista
Objetivo: crea una lista vácia
*/
listaAdyacencia* crearListaVacia(){
  listaAdyacencia * lista=(listaAdyacencia*)malloc(sizeof(listaAdyacencia));
  lista->inicio=NULL;
  return lista;
}

/*
Entradas: lista(cabeza de la lista)
Salida: 1|0 (Dependiendo si se encuentra vácia o no)
Objetivo: determina si una lista se encuentra vácia
*/
int esListaVacia(listaAdyacencia * lista){
  if (lista->inicio == NULL)
    return 1;
  else
    return 0;
}

/*
Entradas: lista(cabeza de la lista), dato (dato a agregar)
Salida:-
Objetivo: insertar un dato al inicio de la lista entregada
*/
void insertarInicio(listaAdyacencia* lista, int dato){
  nodoListaAdyacencia* nuevo=(nodoListaAdyacencia*)malloc(sizeof(nodoListaAdyacencia));
  nuevo->dato = dato;
  nuevo->siguiente = lista->inicio;
  lista->inicio=nuevo;
}

/*
Entradas: lista(cabeza de la lista)
Salida:-
Objetivo: recorrer una lista entregada
*/
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


