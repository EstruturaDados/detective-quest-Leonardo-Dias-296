#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Sala {
    char nome[50];
    struct Sala* esquerda;
    struct Sala* direita;
} Sala;

Sala* criarSala(char* nome) {
    Sala* nova = (Sala*)malloc(sizeof(Sala));
    strcpy(nova->nome, nome);
    nova->esquerda = NULL;
    nova->direita = NULL;
    return nova;
}

void explorarSalas(Sala* atual) {
    char escolha;
    while (atual != NULL) {
        printf("\nVoce esta em: %s\n", atual->nome);
        if (atual->esquerda == NULL && atual->direita == NULL) {
            printf("Nao ha mais caminhos. Fim da exploracao.\n");
            return;
        }
        printf("Escolha um caminho (e = esquerda, d = direita, s = sair): ");
        scanf(" %c", &escolha);

        if (escolha == 'e') {
            if (atual->esquerda != NULL) {
                atual = atual->esquerda;
            } else {
                printf("Nao ha sala a esquerda.\n");
            }
        } else if (escolha == 'd') {
            if (atual->direita != NULL) {
                atual = atual->direita;
            } else {
                printf("Nao ha sala a direita.\n");
            }
        } else if (escolha == 's') {
            printf("Exploracao encerrada pelo jogador.\n");
            return;
        } else {
            printf("Entrada invalida. Use apenas e, d ou s.\n");
        }
    }
}

int main() {
    Sala* hall = criarSala("Hall de entrada");
    Sala* salaEstar = criarSala("Sala de estar");
    Sala* cozinha = criarSala("Cozinha");
    Sala* biblioteca = criarSala("Biblioteca");
    Sala* jardim = criarSala("Jardim");
    Sala* porao = criarSala("Porao");
    Sala* quarto = criarSala("Quarto principal");

    hall->esquerda = salaEstar;
    hall->direita = cozinha;
    salaEstar->esquerda = biblioteca;
    salaEstar->direita = jardim;
    cozinha->esquerda = porao;
    cozinha->direita = quarto;

    printf("Bem-vindo ao Detective Quest!\n");
    explorarSalas(hall);

    free(hall);
    free(salaEstar);
    free(cozinha);
    free(biblioteca);
    free(jardim);
    free(porao);
    free(quarto);

    return 0;
}
