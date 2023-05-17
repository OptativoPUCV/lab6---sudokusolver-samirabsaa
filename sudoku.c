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
//- No se repitan números en las filas
//- No se repitan números en las columnas
//- No se repitan números en las submatrices de 3x3

//Si el estado es válido la función retorna 1, si no lo es retorna 0.

   /*int k=4,p; 
    for(p=0;p<9;p++){
        int i=3*(k/3) + (p/3) ;
        int j=3*(k%3) + (p%3) ;
        printf("%d ",nodo->sudo[i][j]);
        if(p%3 == 2) printf("\n");
    }*/

  /*Para marcar los números que vayan apareciendo en una fila/columna/submatriz puede usar un arreglo de enteros de largo 10 inicializado con 0s. Cada vez que aparezca un número i, verifique que la casilla i del arreglo sea igual a 0, luego márquela con un '1'. Si la casilla es '1' quiere decir que el número ya estaba marcado por lo que la fla/columna/submatriz no es válida.
*/

  //FILAS SIN REPETIR 
  //recorrer matriz y verificar que num en las filas no se repitan 

  for(int i=0; i < 9; i++){
  
      int array[10] = {0};
      
    for(int j=0; j<9; j++){
    
      int casillax = n->sudo[i][j];
      
      if(casillax != 0){
        if(array[casillax] == 0){
          array[casillax] = 1; 
        }
        else return 0;  
      }
    }
  }

  //COLUMNAS SIN REPETIR 
  //recorrer matriz y verificar que los números en las columnas no se repitan 
    for(int i=0; i<9; i++){
      int array[10] = {0}; 
      for(int j=0; j<9; j++){
        int casi = n->sudo[j][i];
        if(casi != 0){
          if(array[casi] == 0) array[casi] = 1; 
          else return 0; 
        }
      }  
    }

  //SUBMATRICES SIN REPETIR
  //recorrer y verificar que los números dentro de la matriz 3x3 no se repitan y sean del 1 al 9

  /*for(int k = 0 ; k<3; k++ ){ //3 pq la matriz es de 3x3
    int array[10] = {0};  
    for(int p=0;p<9;p++){
        int i=3*(k/3) + (p/3) ;
        int j=3*(k%3) + (p%3) ;
        //printf("%d ",nodo->sudo[i][j]);
        //if(p%3 == 2) printf("\n");
    

      int mat = n->sudo[j][i]; 
      if(mat != 0){
        if(array[mat] == 0){
          array[mat] = 1;
        }
        else return 0;
      }    
    }
  }*/


    //squares
    for(int k=0;k<9;k++){
       int b[10]; for(ii=1;ii<10;ii++) b[ii]=0;
       for(l=0;l<9;l++){
           i=3*(k%3) + (l%3) ;
           j=3*(k/3) + (l/3) ;
         if( n->sudo[i][j]!= 0 && b[n->sudo[i][j]]==1) return 0;
         b[n->sudo[i][j]]=1;
       }
    }

    
    return 1;
}


List* get_adj_nodes(Node* n){
    List* list=createList();
    int i, j;
    for(i=0; i<9;i++){ 
      int num = 1;
      for( j=0; j<9;j++){
         if(n->sudo[i][j] == 0){
          for(num = 1; num< 10; num++){
            n->sudo[i][j] = num; 
            if(is_valid(n)){
              Node * ady = copy(n);
              pushBack(list, ady);
            }
          }
          n->sudo[i][j]=0;
        }
      }
    }
    return list;
}


int is_final(Node* n){
  //retorn 1 si el nodod corresponde a un nodo final (nros de la matriz distintos a 0)
  //retorna 0 en caso contrario 
  for(int i = 0; i<9; i++){
    for(int j=0; j<9; j++){
      if((n->sudo[i][j])==0)return 0; 
    }
  }
    return 1;
}

Node* DFS(Node* initial, int* cont){

  Stack *s = createStack();  
  if(s==NULL)return NULL; 
  *cont = 1; 
  push(s, initial); 

  while(get_size(s)!=0){
    Node* node = top(s); 
    pop(s); 
    *cont = *cont-1;
    (*cont)--; 
    if(is_final(node)==1)return node; 

    List* adyN = get_adj_nodes(node);
    //if(adyN == NULL)return NULL; 
    
    Node * aux = first(adyN); 
    //if(aux==NULL)return NULL; 

    while(aux!=NULL){
      push(s,aux);
      aux= next(adyN); 
      (*cont)++; 
      *cont = *cont +1; 
    }
    (*cont)++; 
    free(node); 
  }
  if(*cont == 0) return NULL;
  free(initial);
  
  //1crear stack S e insertar nodo 

  //Stack* s = createStack(); 
  //if(s == NULL)return NULL; 
  //(*cont) =1; 
  //if() 
  //push(s, initial); 

  //2while stack!=0
  //sacar y eliminar el primer nodo de S 
  //verificar if is_final -> retornar nodo
  //obtener la lista de get_adj_nodes
  //agregar los nodods de la lista 1 por 1 al stack 
  //liberar memoria usada por el nodo
  
  //while((get_size(s)) != 0){
    //Node* node = top(s); //sacar primer nodo
    //pop(s);  //eliminar primer nodo
    //(*cont)--;

    //if((is_final(node))==1)return node; 
    /*{
      free(s); 
      return node; 
    }*/

    //OBTENER LISTA NODOD ADY
    //List* adyNodes = get_adj_nodes(node); 
    /*if(adyNodes==NULL)
    {
      free(s);
      return NULL;
    }*/
   //Node* aux = first(adyNodes); 

    //while(aux != NULL){
      //push(s, aux); 
      //aux = next(adyNodes); 
      //(*cont)++;
    //}
    //(*cont)++;
    //free(node);  
  //}
  //3 si se termina de recorrer el grafo sin encontrar solución return NULL

  //en la variable cont almacenar iteraciones que realiz allgoritmo
  //free(initial);
  //return initial;
  return NULL; 
}


/*int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/