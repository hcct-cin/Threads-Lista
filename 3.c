
#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define N 2
#define P 10

double A[N][N] = {2, 1, 5, 7};
double B[N] = {11, 13};
double X[N][P];                                                     // o valor de X[i] sera refinado P vezes

int **aux;                                                          // isso serve pra guardar as incognitas associadas a cada thread
int numThreads;

pthread_barrier_t barrier;                                          // vamos usar barrier para sincronizar as threads

void *func(void *threadid){
    int id = *(int *)threadid;
    
    int k=0, j=0, cont=0;
    double sum = 0;
    while(k < P){                                                   // algoritmo de jacobi
        cont = 0;
        int val = aux[id][cont];                                    // pegamos o valor da primeira variavel
        while(1){
            for(j=0;j<N;j++){
                if(j!=val){                                         // so realizamos a soma se j!=i conforme a formula dada
                    sum += A[val][j] * X[j][k];
                }
            }
            X[val][k+1] = (B[val] - sum)/A[val][val];
            cont++;                                                 // somamos 1 a cont para pegar a proxima incognita da thread atual
            if(cont > N) break;                                     // se cont > N, para o loop pois o maior numero de incognitas de uma unica thread eh N
            val = aux[id][cont];                                    // atualiza val
            if(val == -1) break;                                    // se val==-1, significa que nao temos mais variaveis nessa thread
        }
        k++;
        pthread_barrier_wait(&barrier);
    }
}

int main(int argc, char *argv[]){
    
    int i, j;
    
    scanf("%d", &numThreads);
    if(numThreads > N) numThreads = N;                              // nao precisamos de mais de N threads, senao algumas delas ficariam sem variavel
    
    aux = (int **)malloc(numThreads*sizeof(int*));                  // alocando espaco para aux
    for(i=0;i<numThreads;i++){
        aux[i] = (int *)malloc(N*sizeof(int));
        for(j=0;j<N;j++) aux[i][j] = -1;                            // a thread i tem, no maximo, N incognitas. O valor de -1 ocorre quando nao existe uma incognita naquele lugar. Ou seja, o numero de incognitas associadas aquela thread eh o indice j antes do -1. Uma forma de evitar esse processo seria fazendo varias listas encadeadas, uma para cada thread.
    }   
    
    pthread_t thread[numThreads];
    int *ids[numThreads];

    pthread_barrier_init(&barrier,NULL,numThreads);
    
    for(i=0;i<numThreads;i++){                                      // criacao das threads
        ids[i] = (int *)malloc(sizeof(int));
        *ids[i] = i;
        pthread_create(&thread[i],NULL,func,(void*)ids[i]);
    }
    
    for(i=0;i<numThreads;i++) pthread_join(thread[i],NULL);
    
    for(i=0;i<N;i++) printf("%lf ", X[i][P-1]);                     // para printar o valor final
    
    pthread_barrier_destroy(&barrier);
    pthread_exit(NULL);
    
}
