#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h> // Necessário para configurar o console no Windows
#include <locale.h>

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

// Variáveis globais para métricas (para facilitar a contagem na recursão)
Metricas metricasGlobais = {0, 0};

// --- Funções Auxiliares ---


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
        // Ajuste aqui se o seu CSV usar ponto e vírgula (;)
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

// Função para imprimir os dados (conforme pedido na saída esperada)
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
        metricasGlobais.movimentacoes++; // Atribuição ao vetor original conta como troca/movimento
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

// --- Função Principal ---

int main(int argc, char *argv[]) {
    SetConsoleOutputCP(65001);
    setlocale(LC_COLLATE, "");
    if (argc < 2) {
        printf("Uso: %s <algoritmo_id>\n", argv[0]);
        printf("1: Ordenacao Simples\n2: Ordenacao Otima (Merge)\n3: Ordenacao Linear\n");
        return 1;
    }

    int algoritmo = atoi(argv[1]);
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
            // TODO: Implementar Algoritmo Simples (ex: Bubble ou Selection)
            printf("Algoritmo Simples nao implementado ainda.\n");
            break;
        case 2:
            mergeSort(0, n - 1, NULL, jogadores);
            break;
        case 3:
            // TODO: Implementar Algoritmo Linear (ex: Radix ou Counting)
            printf("Algoritmo Linear nao implementado ainda.\n");
            break;
        default:
            printf("Opcao invalida.\n");
            free(jogadores);
            return 1;
    }

    fim_t = clock();
    tempo_ms = ((double)(fim_t - inicio_t) / CLOCKS_PER_SEC) * 1000.0;

    // Saída Esperada: Lista Ordenada
    imprimirVet(jogadores, n);

    // Saída Esperada: Métricas (4 números em ponto flutuante)
    // 1. Tempo (ms)
    // 2. Comparações
    // 3. Movimentações
    // 4. Memória Gasta (Bytes)
    
    // Cálculo de Memória:
    // O Merge Sort gasta O(N) de memória auxiliar. 
    // Total = Vetor Original + Vetor Auxiliar (na soma das chamadas recursivas chega a N)
    double memoriaBytes = (double)(n * sizeof(Jogador)); 
    if(algoritmo == 2) {
        memoriaBytes *= 2; // Merge sort usa o dobro de memória (array original + aux)
    }

    printf("%.2f - Tempo em MS \n ", tempo_ms);
    printf("%.0f - Comparacoes \n", (double)metricasGlobais.comparacoes);
    printf("%.0f - Movimentaçces \n", (double)metricasGlobais.movimentacoes);
    printf("%.2f - Memoria em Bytes ", memoriaBytes); // Memoria em Bytes

    free(jogadores);
    return 0;
}