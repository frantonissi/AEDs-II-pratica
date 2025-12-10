#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>

/*
AEDS II (Prática)
Trabalho 3

Diego Vianna Leite Montemor
Francisco Toro Tonissi 
Pedro Ferreira Prado
*/

// Definição da Struct conforme o enunciado
typedef struct {
    char nome[100];
    char posicao[50];
    char naturalidade[50];
    char clube[50]; 
    int idade;
} Jogador;

// Estrutura para armazenar as métricas globalmente durante a execução
typedef struct {
    unsigned long long comparacoes;
    unsigned long long movimentacoes;
} Metricas;

Metricas metricasGlobais = {0, 0};



int lerArquivo(char *jogadores, Jogador **vetor) {
    FILE *file = fopen(jogadores, "r");
    if (!file) {
        printf("Erro ao abrir o arquivo %s\n", jogadores);
        exit(1);
    }

    char linha[1024];
    int count = 0;
    int capacidade = 10; // Capacidade inicial
    *vetor = (Jogador *)malloc(capacidade * sizeof(Jogador));

    // Pula o cabeçalho
    fgets(linha, 1024, file);

    while (fgets(linha, 1024, file)) {
        if (count >= capacidade) {
            capacidade *= 2;
            *vetor = (Jogador *)realloc(*vetor, capacidade * sizeof(Jogador));
        }

        // Lê os dados separados por vírgula
        char *token = strtok(linha, ",");
        if (token) strcpy((*vetor)[count].nome, token);

        token = strtok(NULL, ",");
        if (token) strcpy((*vetor)[count].posicao, token);

        token = strtok(NULL, ",");
        if (token) strcpy((*vetor)[count].naturalidade, token);

        token = strtok(NULL, ",");
        if (token) strcpy((*vetor)[count].clube, token);

        token = strtok(NULL, ",");
        if (token) (*vetor)[count].idade = atoi(token);

        count++;
    }

    fclose(file);
    return count;
}

void imprimirVet(Jogador v[], int n) {
    for (int i = 0; i < n; i++) {
        // Exibindo todos os campos como pedido
        printf("%s, %s, %s, %s, %d\n", 
            v[i].nome, v[i].posicao, v[i].naturalidade, v[i].clube, v[i].idade);
    }
}


void merge(Jogador v[], int inicio, int meio, int fim) {
    int n1 = meio - inicio + 1;
    int n2 = fim - meio;

    // Alocação dinâmica para evitar estouro de pilha com grandes datasets
    Jogador *E = (Jogador *)malloc(n1 * sizeof(Jogador));
    Jogador *D = (Jogador *)malloc(n2 * sizeof(Jogador));

    // Copia dados para arrays temporários
    for (int i = 0; i < n1; i++) {
        E[i] = v[inicio + i];
        metricasGlobais.movimentacoes++; // Cópia conta como movimentação
    }
    for (int j = 0; j < n2; j++) {
        D[j] = v[meio + 1 + j];
        metricasGlobais.movimentacoes++;
    }

    int i = 0;
    int j = 0;
    int k = inicio;

    while (i < n1 && j < n2) {
        metricasGlobais.comparacoes++; // Incrementa comparação
        
        // Comparação de Strings pelo NOME
        if (strcoll(E[i].nome, D[j].nome) <= 0) {
            v[k] = E[i];
            i++;
        } else {
            v[k] = D[j];
            j++;
        }
        metricasGlobais.movimentacoes++; 
        k++;
    }

    // Copia os elementos restantes
    while (i < n1) {
        v[k] = E[i];
        i++;
        k++;
        metricasGlobais.movimentacoes++;
    }

    while (j < n2) {
        v[k] = D[j];
        j++;
        k++;
        metricasGlobais.movimentacoes++;
    }

    free(E);
    free(D);
}

void mergeSort(int inicio, int fim, int v_temp[], Jogador v[]) {

    if (inicio < fim) {
        int meio = inicio + (fim - inicio) / 2; // Evita overflow
        mergeSort(inicio, meio, NULL, v);
        mergeSort(meio + 1, fim, NULL, v);
        merge(v, inicio, meio, fim);
    }
}

// --- Algoritmo de Ordenação Simples: Bubble Sort ---
void bubbleSort(Jogador v[], int n) {
    int i, j;
    Jogador temp;

    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - 1 - i; j++) {
            
            metricasGlobais.comparacoes++; 

            
            if (strcoll(v[j].nome, v[j+1].nome) > 0) {
                
                // Realiza a troca (Swap)
                temp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = temp;

                // Cada troca envolve 3 movimentações de dados na memória
                metricasGlobais.movimentacoes += 3; 
            }
        }
    }
}

// --- Algoritmo de Ordenação Linear: Radix Sort (LSD para Strings) ---

// Função auxiliar para pegar o tamanho da maior string no vetor
int obterMaxLen(Jogador v[], int n) {
    int maxLen = 0;
    for (int i = 0; i < n; i++) {
        int len = strlen(v[i].nome);
        if (len > maxLen) {
            maxLen = len;
        }
    }
    return maxLen;
}

// Counting Sort adaptado para ordenar com base no caractere na posição 'pos'
void countingSortNome(Jogador v[], char **chaves, int n, int pos) {
    // Alocação dos vetores auxiliares de saída
    Jogador *output = (Jogador *)malloc(n * sizeof(Jogador));
    char **outputChaves = (char **)malloc(n * sizeof(char *));
    
    if (!output || !outputChaves) {
        printf("Erro de alocacao no Counting Sort\n");
        exit(1);
    }

    int count[256] = {0};

    // 1. Contagem de frequências usando a CHAVE transformada
    for (int i = 0; i < n; i++) {
        int len = strlen(chaves[i]);
        // Se a posição for maior que a string, usa 0 (padding)
        int charIndex = (pos < len) ? (unsigned char)chaves[i][pos] : 0;
        count[charIndex]++;
    }

    // 2. Soma de prefixo
    for (int i = 1; i < 256; i++) {
        count[i] += count[i - 1];
    }

    // 3. Construção do array de saída (Estável: trás para frente)
    for (int i = n - 1; i >= 0; i--) {
        int len = strlen(chaves[i]);
        int charIndex = (pos < len) ? (unsigned char)chaves[i][pos] : 0;
        
        int destIndex = count[charIndex] - 1;

        // Movemos O JOGADOR e a CHAVE para manter sincronia
        output[destIndex] = v[i];
        outputChaves[destIndex] = chaves[i];
        
        count[charIndex]--;
        metricasGlobais.movimentacoes++; 
    }

    // 4. Copiar de volta para os vetores originais
    for (int i = 0; i < n; i++) {
        v[i] = output[i];
        chaves[i] = outputChaves[i]; // Atualiza a ordem das chaves também
        metricasGlobais.movimentacoes++;
    }

    free(output);
    free(outputChaves);
}

void radixSortNome(Jogador v[], int n) {
    // 1. Criar vetor de chaves transformadas (strxfrm)
    // Isso converte "Álvaro" em uma sequência de bytes que o Radix entende corretamente
    char **chaves = (char **)malloc(n * sizeof(char *));
    int maxLen = 0;

    for (int i = 0; i < n; i++) {
        // strxfrm retorna o tamanho necessário. Chamamos com NULL para descobrir o tamanho.
        size_t len = strxfrm(NULL, v[i].nome, 0) + 1; 
        chaves[i] = (char *)malloc(len * sizeof(char));
        
        // Realiza a transformação baseada no locale (LC_COLLATE)
        strxfrm(chaves[i], v[i].nome, len);

        if ((int)len > maxLen) {
            maxLen = (int)len;
        }
    }

    // 2. Aplica o Counting Sort nas posições das CHAVES
    // Note que usamos maxLen das chaves, não dos nomes originais
    for (int pos = maxLen - 1; pos >= 0; pos--) {
        countingSortNome(v, chaves, n, pos);
    }

    // 3. Liberar memória das chaves auxiliares
    for (int i = 0; i < n; i++) {
        free(chaves[i]);
    }
    free(chaves);
}


// --- Função Principal ---
int main(){
    setlocale(LC_ALL, "");
    int algoritmo;
    printf("-- Escolha um algoritimo de ordenação --\n");
    printf("1: Ordenacao Simples (Bobble)\n2: Ordenacao Otima (Merge)\n3: Ordenacao Linear (Radix)\nR: ");
    scanf("%d",&algoritmo);
    
    Jogador *jogadores = NULL;
    int n = lerArquivo("jogadores.csv", &jogadores);

    // Variáveis de tempo
    clock_t inicio_t, fim_t;
    double tempo_ms = 0.0;

    // Reseta métricas
    metricasGlobais.comparacoes = 0;
    metricasGlobais.movimentacoes = 0;

    inicio_t = clock();

    switch (algoritmo) {
        case 1:
            bubbleSort(jogadores, n);
            break;
        case 2:
            mergeSort(0, n - 1, NULL, jogadores);
            break;
        case 3:
            radixSortNome(jogadores, n);
            break;
        default:
            printf("Opcao invalida.\n");
            free(jogadores);
            return 1;
    }

    fim_t = clock();
    tempo_ms = ((double)(fim_t - inicio_t) / CLOCKS_PER_SEC) * 1000.0;

    imprimirVet(jogadores, n);


    // Cálculo de Memória (Estimativa)
    double memoriaBytes = (double)(n * sizeof(Jogador)); 

    // Merge Sort (2) e Radix Sort (3) usam vetor auxiliar, dobrando o uso
    if(algoritmo == 2 || algoritmo == 3) {
        memoriaBytes *= 2; 
    }

    printf("%.2f - Tempo em MS \n", tempo_ms);
    printf("%.0f - Comparacoes \n", (double)metricasGlobais.comparacoes);
    printf("%.0f - Movimentaçces \n", (double)metricasGlobais.movimentacoes);
    printf("%.2f - Memoria em Bytes ", memoriaBytes); // Memoria em Bytes

    free(jogadores);

    printf("\n\n FELIZ NATAL!!! :)\n");
    return 0;
}