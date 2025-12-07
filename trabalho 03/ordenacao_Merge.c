#include <stdlib.h>
#include <stdio.h>




void merge(int v[], int inicio, int meio, int fim){

    int n1 = meio - inicio + 1;
    int n2 = fim - meio;

    int E[n1];
    int D[n2];

    for (int i = 0; i <= n1 - 1; i++){
        E[i] = v[inicio + i];
    }for (int j = 0; j <= n2 - 1; j++){
        D[j] = v[meio + 1 + j];
    }

    int i = 0;      // Índice para o vetor E
    int j = 0;      // Índice para o vetor D
    int k = inicio; // Índice para o vetor original v

    while(i < n1 && j < n2){
        if (E[i] < D[j]){
            v[k] = E[i];
            i++;

        }else{
            v[k] = D[j];
            j++;
        }
        k++;
    }

    if (i < n1){
        while( i < n1){
            v[k] = E[i];
            i++;
            k++;
        }
    }else if (j < n2){
        while(j < n2){
            v[k] = D[j];
            j++;
            k++;
        }

    }
}

void mergeSort(){
    
}



/*typedef struct lista{

    char nome[50];
    char posicao[50];
    char naturalidade[50];
    int idade;

}lista;*/