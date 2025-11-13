#include <stdio.h>
#include <stdlib.h>

struct carac_Jogadores{
    char nome[100];
    char posicao[100];
    char naturalidade[100];
    char clube[50];
    int  idade;

};


void imprimir_Vetor(struct carac_Jogadores *vetor){

    for(int i = 0; i < 1150; i++){
        printf("%d", vetor[i]);
    }

    printf("\n");

}

void bubble_Sort(struct carac_jogadores *vetor){

    int i,j;
    int temp;

    for(i = 0; i < 1149; i++){
        for (j = 0; j < 1149 - 1; j++){
            if (vetor[i].idade -> idade > vetor[j+1]){
             temp = vetor[j];
             vetor[j] = vetor[j + 1];
             vetor[j + 1] = temp;
         }
        }
    }

}

int main(){

    struct carac_Jogadores vetor[1150];
    FILE *f = fopen("jogadores.txt", "r"); // ponteiro = fopen("nome_do_arquivo", "modo");

    int i = 0;

    char lixo[200]; // Uma variável temporária apenas para "deitar fora" o cabeçalho
    fgets(lixo, 200, f); // Lê a primeira linha inteira e guarda em 'lixo'

    while(fscanf(f, "%[^,],%[^,],%[^,],%[^,],%d\n", vetor[i].nome, vetor[i].posicao, vetor[i].naturalidade, vetor[i].clube, &vetor[i].idade) == 5){
            //fscanf le o arquivo .txt
        i++; //O fscanf tem uma funcionalidade útil: ele retorna o número de campos que conseguiu ler com sucesso. 
    }


    return 0;
}