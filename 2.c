#include <pthread.h>
#include <stdio.h>
#define N 4     
int a;
int b;
int contPrim = 0;
int maxDiv = 0;
int numDiv = 0;


void *getPrim(){  
    int i,j;  
    for(i=a;i<=b;i++){                    // Eu faço um ciclo dentro do outro, o ciclo mais interno começa em 1, e vai até o valor do i.
      for(j=1;j<i;j++){
        if(i%j == 0 && j != 1){           // Se o i for divisivel por algum j que n seja 1, entao ele nao é primo, e eu saio desse ciclo para n desperdiçar tempo
          break;}
      }
    if(j==i && i!=1){contPrim++;}         // Se o valor de j for igual ao de i, significa que depois de percorrer todo o ciclo, ele n encontrou nenhum divisor alem de 1, e ele mesmo, logo é primo, e assim eu somo no contPrim.  
    }
}

void *getDivs(){  

    int i,j, cont=0;
    for(i=a;i<=b;i++){                    // Eu façp um ciclo dentro do outro, o ciclo mais interno começa em 1 e vai até i.
      for(j=1;j<=i;j++){                  
        if(i%j == 0){                     // Eu verifico se o i é divisivel por j, se for, eu acrescento no cont.
          cont++;}
      }
    if(cont > maxDiv){                    // Se o cont for maior que o maxDiv ( Que inicialmente começa em zero),  entao o maxDiv recebe o valor de cont. 
      maxDiv = cont;}                       
      cont = 0;                           // Zero o cont para ele começar outro ciclo.
    }

}
void *getNumDivs(){  

    int i,j, cont=0, maxDiv2=0;
    for(i=a;i<=b;i++){
      for(j=1;j<=i;j++){
        if(i%j == 0){
          cont++;}
      }                           
    if(cont > maxDiv2){                  // Eu repito a mesma ideia da rotina getDivs, mas quando o cont for maior que o maxDiv2,  ele vai mudar tambem a variavel numDiv, e atribuir a ela o valor do i em questao.
      maxDiv2 = cont;
      numDiv = i;}  
      cont = 0;
    }
}

void *printResult(){  
    
      printf("%d %d %d\n", contPrim,maxDiv, numDiv);
}

int main (int argc, char *argv[]){   
  pthread_t threads[N];

  scanf("%d %d",&a,&b);   
  
  pthread_create(&threads[0], NULL, getPrim, NULL);   
                                                        // Crio as 3 primeiras threads, cada uma designada a realizar uma das rotinas definidas acima.
  pthread_create(&threads[1], NULL, getDivs, NULL);      
  
  pthread_create(&threads[2], NULL, getNumDivs, NULL);      
    

  pthread_join(threads[0], NULL);
  pthread_join(threads[1], NULL);
  pthread_join(threads[2], NULL);
                                                              // Eu espero as 3 primeiras threads terminarem para entao criar a quarta thread q será responsavel por printar o resultado.
  pthread_create(&threads[3], NULL, printResult, NULL);

  pthread_join(threads[3], NULL);

  pthread_exit(NULL);
}