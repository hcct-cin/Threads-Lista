#include <pthread.h>
#include <stdio.h>

#define NUM_THREADS 2     
#define LINHAS 3
#define COLUNAS 3

typedef struct par{
    int indiceNzero;
    double elemento;
}Par;

Par MatrizEsparsa[4][4];


void *threadCode(void *tid){   
	
	int i,j, k;
  long  threadId = (*(long *)tid); 
	
	   for(i=threadId; i < LINHAS; i = i + NUM_THREADS) {
				   
	   		if(i >= LINHAS) { return;}
	   	      	
      	for (j=0;j<COLUNAS;j++) {
        	 resultado[i][j] = 0;
  
       		 for(k=0;k< COLUNAS;k++) {
           		 resultado[i][j] = resultado[i][j] + matriz1[i][k]* matriz2[k][j];
       		 }
      }
       
    }
  
}

void preencheMatrizEsparsa(){
    MatrizEsparsa[0] = (Par *) malloc(2*sizeof(Par));
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

int main (int argc, char *argv[]){   





	pthread_t threads[NUM_THREADS]; 
  long *taskids[NUM_THREADS];
	int i,j,u; long t;   
	
  for(t=0; t<NUM_THREADS; t++){
    printf("No main: criando thread %ld\n", t);    
    taskids[t] = (long *) malloc(sizeof(long)); *taskids[t] = t;
	 	pthread_create(&threads[t],NULL,threadCode, (void *)taskids[t]);         
  }
  
  for(u=0; u<NUM_THREADS;u++) {
    long *res;
    pthread_join(threads[u], NULL);
  }   
  
  for(i=0; i < LINHAS; i++) {
			 for (j=0;j<COLUNAS;j++) {
      		 printf("%d\t", resultado[i][j]);
  		 }
  		 
  		 printf("\n");
   }
        		
  
  pthread_exit(NULL);
}
