#include <stdio.h> 
#include <stdlib.h> 
#include "ordenacao.h"
  
// Imprime um vetor de inteiros
void imprimir(int *vetor) {
    int i;
    for (i = 0; i < 50; i++) {
        printf("%d ", vetor[i]);
    }
    printf("\n");
}

void bubble(int *vetor) {
  
    int j,i;
    int temp;

    for (i = 0; i < 49; i++){ //laço externo pra percorrer o vetor por fora quantas vezes precisar
       for(j = 0; j < 49 - i; j++){ 
        if (vetor[j] > vetor[j+1]){//^Um laço interno (digamos, com a variável j) que faz as comparações e trocas em uma passagem.
            temp = vetor[j];
            vetor[j] = vetor[j + 1];
            vetor[j+1] = temp;
        }
    }
    }

    imprimir(vetor);
    return;
}

void selection(int *vetor) {
    
    int i, temp, j;
    int indice_menor;

    for (i = 0; i < 50; i++){
        indice_menor = i;
      for (j = i + 1; j<50; j++){
        if (vetor[indice_menor]>vetor[j]){
            indice_menor = j;
        }
           
      }
            temp = vetor[i];
            vetor[i] = vetor[indice_menor];
            vetor[indice_menor] = temp;
    }

    imprimir(vetor);
    return;
}

void insertion(int *vetor) {
   
    int i, chave, j;

    for (i = 1; i < 50; i++){

        chave = vetor[i];
        for (j = i - 1; j >= 0 && vetor[j]>chave; j--){
        vetor[j + 1] = vetor[j];
        }
        vetor[j + 1] = chave;
    }

    imprimir(vetor);
    return;
}


// Função 'intercalar' (juntar). 

void intercalar(int *vetor, int esq, int meio, int dir) {
    int i, j, k;
    int n1 = meio - esq + 1;
    int n2 = dir - meio;

    int L[n1], R[n2]; // Vetores temporários

    for (i = 0; i < n1; i++)
        L[i] = vetor[esq + i];
    for (j = 0; j < n2; j++)
        R[j] = vetor[meio + 1 + j];

    // Laço 'for' principal para juntar os vetores L e R
    for (i = 0, j = 0, k = esq; i < n1 && j < n2; k++) {
        if (L[i] <= R[j]) {
            vetor[k] = L[i];
            i++;
        } else {
            vetor[k] = R[j];
            j++;
        }
    }

    // Laços 'for' para copiar o que sobrou de L
    for (; i < n1; i++, k++) {
        vetor[k] = L[i];
    }

    // Laços 'for' para copiar o que sobrou de R
    for (; j < n2; j++, k++) {
        vetor[k] = R[j];
    }
}

// A função recursiva principal do Merge Sort
void merge_sort_recursivo(int *vetor, int esq, int dir) {
    if (esq < dir) {
        int meio = esq + (dir - esq) / 2;
        merge_sort_recursivo(vetor, esq, meio);
        merge_sort_recursivo(vetor, meio + 1, dir);
        intercalar(vetor, esq, meio, dir);
    }
}

void merge(int *vetor) {
    merge_sort_recursivo(vetor, 0, 49);
    imprimir(vetor);
    return;
}

// Função auxiliar para trocar dois elementos
void trocar(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Função 'particionar' (usa 'for', como você pediu)
int particionar(int *vetor, int comeco, int fim) {
    int pivo = vetor[fim]; 
    int i = (comeco - 1);  

    for (int j = comeco; j <= fim - 1; j++) {
        if (vetor[j] < pivo) {
            i++; 
            trocar(&vetor[i], &vetor[j]);
        }
    }
    trocar(&vetor[i + 1], &vetor[fim]);
    return (i + 1); 
}

// A função recursiva principal
void quick_sort_recursivo(int *vetor, int comeco, int fim) {
    if (comeco < fim) {
        int indice_pivo = particionar(vetor, comeco, fim);
        quick_sort_recursivo(vetor, comeco, indice_pivo - 1);
        quick_sort_recursivo(vetor, indice_pivo + 1, fim);
    }
}   
void quick(int *vetor) {
   quick_sort_recursivo(vetor, 0, 49);
    imprimir(vetor);
    return;
}

int main() { 
  // Vetor aleatório de 50 posições
  
  int n;
  do {
    int vetor[50] = {40, 32, 24, 25,  1, 48, 38,  7, 17,  8, 42,  4, 44, 45, 27, 49, 30, 18,  6, 23,  5, 41, 33, 26, 28,  3, 37, 19, 11, 43, 39, 16, 36, 21,  9,  2, 47, 12, 50, 20, 14, 29, 35, 46, 13, 34, 31, 15, 10, 2};
    printf("\n\n\n******************** Escolha seu algoritmo *******************");
	printf("\n1.Bubble sort");
	 printf("\n2.Selection sort");
	 printf("\n3.Insertion sort");
     printf("\n3.Merge sort");
     printf("\n3.Quick sort");
     printf("\n0.Sair");
	 printf("\nEntre sua opção : ");
	 scanf("%d",&n);
	 switch(n) {
        case 1: bubble(vetor);
			    break;
		case 2: selection(vetor);
			    break;
		case 3: insertion(vetor);
			    break;
        case 4: merge(vetor);
			    break;
        case 5: quick(vetor);
			    break;
        case 0: exit(0);
		 	    break;
		default: printf("\n Opção errada!");
		 	    break;
		}
	} while(1);

  return 0; 
} 