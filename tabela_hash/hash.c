#include <stdio.h> 
#include <stdlib.h> 
#include "hash.h"

int M;

struct Hash* criar_hash(int tamanho) {
    M = tamanho;
    struct Hash* hash = (struct Hash*) malloc(sizeof(struct Hash));
    hash->items = (struct Item*) malloc(tamanho*sizeof(struct Item));
    return hash;
}

void hash_insere(struct Hash* hash, struct Item item) {
    hash->items[hashing(item.valor)] = item;
}

void hash_remove(struct Hash* hash, struct Item item) {
    struct Item newItem;
    newItem.valor = 0;
    hash->items[hashing(item.valor)] = newItem;
}

struct Item busca(struct Hash* hash, struct Item item) {
    return (hash->items[hashing(item.valor)]);
}

int hashing(int chave) {
    return (chave % M);
}

    void anti_Colisao(struct Hash* hash, struct Item item) {
    int idx = hashing(item.valor);
    if (hash->items[idx].valor == 0) {
        hash_insere(hash, item);
        printf("Item %d inserido na posicao %d\n", item.valor, idx);
        return;
    }
    if (hash->items[idx].valor == item.valor) {
        printf("Item %d ja existe na posicao %d\n", item.valor, idx);
        return;
    }
    // colisao detectada: resolver com probing linear
    printf("Colisao em posicao %d: contem %d, tentando inserir %d\n",
           idx, hash->items[idx].valor, item.valor);
    int i = (idx + 1) % M;
    while (i != idx && hash->items[i].valor != 0) {
        i = (i + 1) % M;
    }
    if (i == idx) {
        printf("Tabela cheia: nao foi possivel inserir %d\n", item.valor);
    } else {
        hash->items[i] = item;
        printf("Item %d inserido na posicao %d (linear probing)\n", item.valor, i);
    }
}

int main() { 
    int n;
    /* Cria hash com 20 posições */
    struct Hash* hash = criar_hash(10);
    struct Item item;
    do {
        printf("\n\n\n******************** Escolha a opção *******************");
        printf("\n1.Inserir item");
        printf("\n2.Remover item");
        printf("\n3.Obter item");
        printf("\n4.Checar colisao entre dois itens");
        printf("\n0.Sair");
        printf("\nEntre sua opção : ");
        scanf("%d",&n);
        switch(n) {
            case 1: printf("\nDigite o item ");
                    scanf("%d",&item.valor);
                    hash_insere(hash, item);
                    break;
            case 2: printf("\nDigite o item ");
                    scanf("%d",&item.valor);
                    hash_remove(hash, item);
                    break;
            case 3: printf("\nDigite o item ");
                    scanf("%d",&item.valor);
                    item = busca(hash, item);
                    break;
                case 4: {
                    struct Item b;
                    printf("\nDigite o item (tentando inserir): ");
                    scanf("%d", &b.valor);
                    anti_Colisao(hash, b);
                    break;
                }
            case 0: exit(0);
                    break;
            default: printf("\n Opção errada!");
                    break;
            }
        } while(1);
    
}