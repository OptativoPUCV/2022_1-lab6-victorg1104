#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n){
  Node* aux = copy(n);

  for (size_t i = 0; i < 9; i++)
  {
    int vectorAux [10] = {};
    for (size_t j = 0; j < 9; j++)
    {
      if (aux->sudo[i][j] != 0)
      {
        if(vectorAux[aux->sudo[i][j]] == 0)
        {
          vectorAux[aux->sudo[i][j]] = 1;
        }
        else return 0;
      }
    }
  }

  for (size_t i = 0; i < 9; i++)
  {
    int vectorAux [10] = {};
    for (size_t j = 0; j < 9; j++)
    {
      if (aux->sudo[j][i] != 0)
      {
        if(vectorAux[aux->sudo[j][i]] == 0)
        {
          vectorAux[aux->sudo[j][i]] = 1;
        }
        else return 0;
      }
    }
  }
  
  for (size_t k = 0; k < 9; k++)
  {
    int aux2 = k;
    int p;
    int vectorAux[10] = {};

    for(p=0;p<9;p++)
    {
      int i=3*(aux2/3) + (p/3) ;
      int j=3*(aux2%3) + (p%3) ;
        
      if (aux->sudo[i][j] != 0)
      {
        if(vectorAux[aux->sudo[i][j]] == 0)
        {
          vectorAux[aux->sudo[i][j]] = 1;
        }
        else return 0;
      }
    }
  }
  
    return 1;
}


List* get_adj_nodes(Node* n){
    List* list=createList();
    Node* aux = copy(n);

    for (size_t i = 0; i <9 ; i++)
    {
      for (size_t j = 0; j < 9; j++)
      {
        if (aux->sudo[i][j] == 0)
        {
          for (size_t k = 1; k <= 9; k++)
          {
            aux = copy(n);

            aux->sudo[i][j] = k;

            if(is_valid(aux))pushBack(list, aux);
          }
          return list;
        } 
      }      
    }
  return list;
}


int is_final(Node* n){

    for (size_t i = 0; i < 9; i++)
    {
      for (size_t j = 0; i < 9; i++)
      {
        if (n->sudo[i][j] == 0) return 0;
      }
    }
    return 1;
}

Node* DFS(Node* initial, int* cont){

  Stack* S = createStack();
  Node* aux;
  push(S, initial);

  while (get_size(S) != 0)
  {
    cont++;
    aux = top(S);
    pop(S);

    if(is_final(aux)) return aux;

    List* adj = get_adj_nodes(aux);
    aux = first(adj);

    while (aux)
    {
      push(S, aux);
      aux = next(adj);
    }

    free(aux);
  }
  return NULL;
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
*/
