#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Sala {
    char nome[60];
    char pista[200];
    struct Sala* esquerda;
    struct Sala* direita;
} Sala;

typedef struct PistaNode {
    char pista[200];
    struct PistaNode* esquerda;
    struct PistaNode* direita;
} PistaNode;

Sala* criarSala(char* nome, char* pista) {
    Sala* nova = (Sala*)malloc(sizeof(Sala));
    strcpy(nova->nome, nome);
    if (pista != NULL) strcpy(nova->pista, pista);
    else nova->pista[0] = '\0';
    nova->esquerda = NULL;
    nova->direita = NULL;
    return nova;
}

PistaNode* criarPistaNode(char* texto) {
    PistaNode* node = (PistaNode*)malloc(sizeof(PistaNode));
    strcpy(node->pista, texto);
    node->esquerda = NULL;
    node->direita = NULL;
    return node;
}

PistaNode* inserirPista(PistaNode* raiz, char* texto) {
    if (texto == NULL || texto[0] == '\0') return raiz;
    if (raiz == NULL) return criarPistaNode(texto);
    int cmp = strcmp(texto, raiz->pista);
    if (cmp < 0) raiz->esquerda = inserirPista(raiz->esquerda, texto);
    else if (cmp > 0) raiz->direita = inserirPista(raiz->direita, texto);
    return raiz;
}

void exibirPistas(PistaNode* raiz) {
    if (raiz == NULL) return;
    exibirPistas(raiz->esquerda);
    printf("- %s\n", raiz->pista);
    exibirPistas(raiz->direita);
}

void liberarPistas(PistaNode* raiz) {
    if (raiz == NULL) return;
    liberarPistas(raiz->esquerda);
    liberarPistas(raiz->direita);
    free(raiz);
}

void liberarSalas(Sala* raiz) {
    if (raiz == NULL) return;
    liberarSalas(raiz->esquerda);
    liberarSalas(raiz->direita);
    free(raiz);
}

void explorarSalasComPistas(Sala* atual, PistaNode** arvorePistas) {
    char escolha;
    while (atual != NULL) {
        printf("\nVoce esta em: %s\n", atual->nome);
        if (atual->pista[0] != '\0') {
            printf("Pista encontrada: %s\n", atual->pista);
            *arvorePistas = inserirPista(*arvorePistas, atual->pista);
            atual->pista[0] = '\0';
        } else {
            printf("Nenhuma pista neste comodo.\n");
        }
        printf("Escolha um caminho (e = esquerda, d = direita, s = sair): ");
        scanf(" %c", &escolha);
        if (escolha == 'e') {
            if (atual->esquerda != NULL) atual = atual->esquerda;
            else printf("Nao ha comodo a esquerda.\n");
        } else if (escolha == 'd') {
            if (atual->direita != NULL) atual = atual->direita;
            else printf("Nao ha comodo a direita.\n");
        } else if (escolha == 's') {
            printf("Exploracao encerrada pelo jogador.\n");
            return;
        } else {
            printf("Entrada invalida. Use apenas e, d ou s.\n");
        }
    }
}

int main() {
    Sala* hall = criarSala("Hall de entrada", "Cartao com iniciais JR");
    Sala* salaEstar = criarSala("Sala de estar", "Pegada molhada no tapete");
    Sala* cozinha = criarSala("Cozinha", "Faca com pegadas de sangue");
    Sala* biblioteca = criarSala("Biblioteca", "Nota rasgada com nome do jardineiro");
    Sala* jardim = criarSala("Jardim", "");
    Sala* porao = criarSala("Porao", "Chave enferrujada");
    Sala* quarto = criarSala("Quarto principal", "Bilhete de despedida");

    hall->esquerda = salaEstar;
    hall->direita = cozinha;
    salaEstar->esquerda = biblioteca;
    salaEstar->direita = jardim;
    cozinha->esquerda = porao;
    cozinha->direita = quarto;

    PistaNode* arvorePistas = NULL;

    printf("Bem vindo ao Detective Quest - Coleta de Pistas\n");
    printf("Explore a mansao e encontre todas as pistas escondidas.\n");

    explorarSalasComPistas(hall, &arvorePistas);

    printf("\nPistas coletadas em ordem alfabetica:\n");
    if (arvorePistas == NULL) printf("Nenhuma pista coletada.\n");
    else exibirPistas(arvorePistas);

    liberarPistas(arvorePistas);
    liberarSalas(hall);

    return 0;
}
