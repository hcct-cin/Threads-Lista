#include <stdio.h>
#include <pthread.h> 
#include <stdlib.h>
#define BUFFER_SIZE 10
#define NUM_ITEMS 200
#define N 3


int buff[BUFFER_SIZE];  
int items = 0; 
int first = 0;
int last = 0; 

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t empty = PTHREAD_COND_INITIALIZER;
pthread_cond_t fill = PTHREAD_COND_INITIALIZER;
 
void *producer();
void *consumer();
void agendarExecucao();
void funexec();
void despachante();
int main() {
    int funcao;                                                           // Variavel a ser usada como parametro para decidir o que vai ser executado
    printf("\t-----------------------------------------\n");              // Na main, eu recebo em uma variavel funçao, que dependendo do seu valor vai passar como parametro para a função agendarExecução
    printf("\tDigite o numero do comando a ser executado:\n");
    printf("1- Funexec.\n");                    
    printf("2- Despachante.\n");
    printf("3- Fechar programa\n");
    printf("->");
    scanf("%d", &funcao);                                                 // Recebo do Usúario
    if(funcao == 1 || funcao == 2){
      agendarExecucao(funcao);                                            // chamo a funcao e passo a variavel "funcao" como parametro.
    }
    if(funcao == 3){
     exit(0);
    }
}

void agendarExecucao(int funcao){  
    while(1){
    if(funcao == 1){
    funexec();}                                                           // Baseado no valor da variavel eu chamo a funexec ou despachante.                          
    else{
    despachante();
    }}
}

void funexec(){
    pthread_t producer_thread;
    int *ids[N]; 
    
    pthread_create(&producer_thread,NULL,producer,NULL);                // Criação da thread responsavel por produzir

    main();                                                             // Chamo a main novamente
    
    pthread_exit(NULL);
}

void despachante(){
    pthread_t producer_thread;
    pthread_t consumer_thread[N]; 
    int *ids[N]; 
    
    
    
    int i = 0;
    for(i = 0; i < N; i++) {
      ids[i] =(int *) malloc(sizeof(int)); 
      *ids[i] = i;
      pthread_create(&consumer_thread[i],NULL,consumer,(void *) ids[i]);    // Threads consumidoras
    }

      main();                                                                // Chamo a main
    pthread_exit(NULL);
}

void put(int i){
  pthread_mutex_lock(&mutex);
  
  while(items == BUFFER_SIZE) {
    pthread_cond_wait(&empty, &mutex);
  
  }
  
  buff[last] = i;
  //printf("pos %d: ", last);
  items++; last++;
  
  if(last==BUFFER_SIZE) { last = 0; } 
  
  if(items == 1) { pthread_cond_broadcast(&fill); }
    
  pthread_mutex_unlock(&mutex); 
}
void *producer() {
  int i = 0;
  printf("Produtor\n");
  int amount = NUM_ITEMS * N;
  printf("Produtor iniciou\n");
  for(i=0;i<amount; i++) {
    put(i);
    printf("Produzi %d \n",i);
  }
  printf("Produtor terminou\n");
  pthread_exit(NULL);
}


int get() {
  int result;
  pthread_mutex_lock(&mutex);
	
	 while(items == 0){  pthread_cond_wait(&fill, &mutex); }
  
  result = buff[first];
  
//  printf("pos %d: ", first);
  
  items--;  first++;
  
  if(first==BUFFER_SIZE) {first = 0; }
  
   if(items == BUFFER_SIZE - 1){ pthread_cond_signal(&empty); }
  
   pthread_mutex_unlock(&mutex);
  
   return result;
}

void *consumer(void *threadid) {
  int i,v;
  printf("Consumidor %d iniciou \n", *((int*) threadid));
  for (i=0;i<NUM_ITEMS;i++) {
  	
    v = get();
    printf("Consumidor %d consumiu %d \n", *((int*) threadid),v);
  }
  
  printf("Consumidor %d terminou \n", *((int*) threadid));
  pthread_exit(NULL);
}
