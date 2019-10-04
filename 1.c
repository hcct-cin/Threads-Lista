#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define N 5                                                   // N quantidade de Threads

pthread_mutex_t mymutex = PTHREAD_MUTEX_INITIALIZER;
int Cont = 0;

void *inc(void *threadid){   
  int i=0;
  int *id;
  id = (int*)threadid;                                              // Pego a variavel ID

  while(Cont <= 1000000){
      pthread_mutex_lock(&mymutex);                                 // Uso o lock no mutex como tecnica de exclusao mutua.
  
    if(Cont <1000000){                                              // Esse if é quem verifica se as Threads precisam ser ou não finalizadas.
    Cont++;                                                         // Se o contador passar na condiçao, a thread vai incrementar.
        if(Cont == 1000000){                                        // Se o contador chegar à 10000000, eu mostro qual Thread chegou a esse valor.
        printf("Valor Alcancado pela Thread %d!\n" , *id);}
    }
    pthread_mutex_unlock(&mymutex);                                  // Uso o unlock no mutex para liberar a regiao critica para as outras Threads.

    if(Cont >= 1000000){
      pthread_exit(NULL);
    }
  }

}

int main (int argc, char *argv[]){   
  pthread_t threads[N];                                           // Declaro N variaveis Threads usando um array de Threads.
  int*taskids[N];                                                 // Variavel de uso pra identificação de Threads.

  int rc;   int t;   

  for(t=0; t<N; t++){      
   taskids[t] = (int *) malloc(sizeof(int));                    
   *taskids[t] = t;
   printf("No main: criando thread %d\n", t);      
   rc = pthread_create(&threads[t], NULL, inc, (void *) taskids[t]);  // Crio a Thread, e passo seu ID como parametro pra rotina que ela vai executar.     
    if (rc){         
      printf("ERRO; código de retorno é %d\n", rc);         
      exit(-1);      
    }   
  
  }   

  pthread_exit(NULL);
}
