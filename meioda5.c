#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define NUM_THREADS 2     
#define LINHAS 4
#define COLUNAS 4

typedef struct par{
    int indiceNzero;
    double elemento;
}Par;


float resultadoPorVetor[4][1];          // Variavel para armazenar o resultado da multplicaçao pelo vetor  
Par MatrizEsparsa[4][4];                // Variavel da matriz esparsa principal
double VetorDenso[4] = {1,2,3,4};       // Vetor denso
Par OutraMatrizEsparsa[4][4];           // Variavel que multiplica a matriz esparsa principal
double MatrizDensa[4][4];               // Matriz densa
double aux[4][4];                       // variavel para representar a matriz esparsa por uma matriz densa

                                //  Nessa função eu preencho a matriz esparsa
void preencheMatrizEsparsa(){
    // Linha 1
    MatrizEsparsa[0][0].indiceNzero = 0;
    MatrizEsparsa[0][0].elemento = 2.0;
    MatrizEsparsa[0][1].indiceNzero = 1;
    MatrizEsparsa[0][1].elemento = -1.0;
    // Linha 2
    MatrizEsparsa[1][0].indiceNzero = 0;
    MatrizEsparsa[1][0].elemento = -1.0;
    MatrizEsparsa[1][1].indiceNzero = 1;
    MatrizEsparsa[1][1].elemento = 2.0;
    MatrizEsparsa[1][2].indiceNzero = 2;
    MatrizEsparsa[1][2].elemento = -1.0;
    // Linha 3
    MatrizEsparsa[2][0].indiceNzero = 1;
    MatrizEsparsa[2][0].elemento = -1.0;
    MatrizEsparsa[2][1].indiceNzero = 2;
    MatrizEsparsa[2][1].elemento = 2.0;
    MatrizEsparsa[2][2].indiceNzero = 3;
    MatrizEsparsa[2][2].elemento = -1.0;
    // Linha 4
    MatrizEsparsa[3][0].indiceNzero = 2;
    MatrizEsparsa[3][0].elemento = -1.0;
    MatrizEsparsa[3][1].indiceNzero = 3;
    MatrizEsparsa[3][1].elemento = 2.0;
    
} 
                                // Fim

                                // Nessa função eu printo a matriz esparsa identada corretamente.
void printaMatrizEsparsa(){
    int i =0;
    int j = 0;
    printf("{");
    for(i=0;i<4;i++){
      printf("{");
      for(j=0;j<4;j++){
        if(i==0 && j ==2){
          break;
        }
        if(i==1 && j==3){
          break;
        }
        if(i==2 && j==3){
          break;
        }
        if(i==3 && j==2){
          break;
        }
        printf("(%d, %.1lf)", MatrizEsparsa[i][j].indiceNzero,MatrizEsparsa[i][j].elemento);
        if(i==0 && j !=1){
          printf(",");
        }
        if(i==1 && j !=2){
          printf(",");
        }
        if(i==2 && j !=2){
          printf(",");
        }
        if(i==3 && j !=1){
          printf(",");
        }
      }
      if(i==3){
         printf("}");
      }
      else{  
      printf("},\n");
      }
    }
    printf("}\n\n");
}
                                // Fim

                                // Nessa função eu armazeno a matriz esparsa em uma matriz auxiliar na sua forma densa.
void *transformaEsparsa(){  
    int i,j;
    
    for(i=0;i<4;i++){
      for(j=0;j<4;j++){
        if(MatrizEsparsa[i][j].indiceNzero != 0 || MatrizEsparsa[i][j].elemento != 0.0){
          aux[i][MatrizEsparsa[i][j].indiceNzero] = MatrizEsparsa[i][j].elemento;}
    
      }
    }
}
                                // Fim

void *threadCode(void *tid){   
	
	int i,j, k;
  long  threadId = (*(long *)tid); 
	
	   for(i=threadId; i < LINHAS; i = i + NUM_THREADS) {
				   
	   		if(i >= LINHAS) { return 0;}
	   	      	
      	for (j=0;j<COLUNAS;j++) {
        	 resultado[i][j] = 0;
  
       		 for(k=0;k< COLUNAS;k++) {
           		 resultado[i][j] = resultado[i][j] + aux[i][k]* VetorDenso[k];
       		 }
      }
       
    }
  
}

void multiplicaVetor(){

                     

  pthread_t threads[NUM_THREADS]; 
  long *taskids[NUM_THREADS];
	int i,j,u; long t;   


  printf("Dado a seguinte Matriz Esparsa : \n");      
  preencheMatrizEsparsa();                  // Preencho e printo a matriz esparsa que será usada
  printaMatrizEsparsa();

  transformaEsparsa();     // Armazeno a matriz esparsa principal na sua forma densa em aux

	
  for(t=0; t<NUM_THREADS; t++){

    printf("No main: criando thread %ld\n", t);                       // Crio as N threads
    taskids[t] = (long *) malloc(sizeof(long)); *taskids[t] = t;
	 	pthread_create(&threads[t],NULL,threadCode, (void *)taskids[t]);         
  }
  
  for(u=0; u<NUM_THREADS;u++){
    long *res;
    pthread_join(threads[u], NULL);
  }   

  

  
  for(i=0; i < LINHAS; i++) {
			 for (j=0;j<1;j++) {
      		 printf("%d\t", resultado[i][j]);
  		 }
  		 
  		 printf("\n");
   }
    		
   
}


int main (int argc, char *argv[]){   

  multiplicaVetor();                      // Chamo a funçao que multiplica a Matriz Esparsa por um vetor denso


	
  
  pthread_exit(NULL);
}
