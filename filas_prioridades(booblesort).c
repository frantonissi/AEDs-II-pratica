    #include <stdio.h>
    #include <stdlib.h>

    struct carac_Jogadores{
        char nome[100];
        char posicao[100];
        char naturalidade[100];
        char clube[50];
        int  idade;

    };


    void imprimir_Vetor(struct carac_Jogadores *vetor, int tamanho){

        for(int i = 0; i < tamanho; i++){
        printf("Nome: %s - Idade: %d\n", vetor[i].nome, vetor[i].idade);        
    }

        printf("\n");

    }

    void bubble_Sort(struct carac_Jogadores *vetor, int tamanho){

        int i,j;
        struct carac_Jogadores temp;

        for(i = 0; i < tamanho - 1; i++){
            for (j = 0; j < tamanho - 1 - i; j++){
                if ( vetor[j].idade > vetor[j+1].idade){
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

        if (f == NULL) {
        printf("ERRO CRITICO: O arquivo 'jogadores.txt' nao foi encontrado!\n");
        printf("Verifique se o arquivo esta na mesma pasta do executavel.\n");
        return 1;
    }

        int i = 0;

        char lixo[200]; // Uma variável temporária apenas para "deitar fora" o cabeçalho
        fgets(lixo, 200, f); // Lê a primeira linha inteira e guarda em 'lixo'

        while(fscanf(f, "%[^,],%[^,],%[^,],%[^,],%d\n", vetor[i].nome, vetor[i].posicao, vetor[i].naturalidade, vetor[i].clube, &vetor[i].idade) == 5){
                //fscanf le o arquivo .txt
            i++; //O fscanf tem uma funcionalidade útil: ele retorna o número de campos que conseguiu ler com sucesso. 
            if (i >= 1150) break;
        }

        printf("Foram lidos %d jogadores.\n", i);

        bubble_Sort(vetor, i);
        imprimir_Vetor(vetor, i);

        return 0;
    }