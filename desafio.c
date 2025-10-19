#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 10

typedef struct Sala {
    char nome[50];
    struct Sala *esq;
    struct Sala *dir;
} Sala;

typedef struct Pista {
    char nome[50];
    struct Pista *esq;
    struct Pista *dir;
} Pista;

typedef struct ItemHash {
    char pista[50];
    char suspeito[50];
    struct ItemHash *prox;
} ItemHash;

ItemHash* tabela[TAM];

Sala* criarSala(char nome[]) {
    Sala* nova = (Sala*)malloc(sizeof(Sala));
    strcpy(nova->nome, nome);
    nova->esq = NULL;
    nova->dir = NULL;
    return nova;
}

unsigned int hash(char* chave) {
    unsigned int valor = 0;
    for (int i = 0; chave[i] != '\0'; i++) valor += chave[i];
    return valor % TAM;
}

void inserirNaHash(char* pista, char* suspeito) {
    unsigned int indice = hash(pista);
    ItemHash* novo = (ItemHash*)malloc(sizeof(ItemHash));
    strcpy(novo->pista, pista);
    strcpy(novo->suspeito, suspeito);
    novo->prox = tabela[indice];
    tabela[indice] = novo;
}

char* encontrarSuspeito(char* pista) {
    unsigned int indice = hash(pista);
    ItemHash* atual = tabela[indice];
    while (atual != NULL) {
        if (strcmp(atual->pista, pista) == 0)
            return atual->suspeito;
        atual = atual->prox;
    }
    return "Desconhecido";
}

Pista* inserirPista(Pista* raiz, char* nome) {
    if (raiz == NULL) {
        Pista* nova = (Pista*)malloc(sizeof(Pista));
        strcpy(nova->nome, nome);
        nova->esq = NULL;
        nova->dir = NULL;
        return nova;
    }
    if (strcmp(nome, raiz->nome) < 0)
        raiz->esq = inserirPista(raiz->esq, nome);
    else if (strcmp(nome, raiz->nome) > 0)
        raiz->dir = inserirPista(raiz->dir, nome);
    return raiz;
}

void listarPistas(Pista* raiz) {
    if (raiz != NULL) {
        listarPistas(raiz->esq);
        printf("- %s\n", raiz->nome);
        listarPistas(raiz->dir);
    }
}

int contarPistasPorSuspeito(Pista* raiz, char* suspeito) {
    if (raiz == NULL) return 0;
    int cont = 0;
    if (strcmp(encontrarSuspeito(raiz->nome), suspeito) == 0)
        cont = 1;
    return cont + contarPistasPorSuspeito(raiz->esq, suspeito) + contarPistasPorSuspeito(raiz->dir, suspeito);
}

char* gerarPistaPorSala(char* sala) {
    if (strcmp(sala, "Biblioteca") == 0) return "luva ensanguentada";
    if (strcmp(sala, "Cozinha") == 0) return "taca de veneno";
    if (strcmp(sala, "Sala de Jantar") == 0) return "colar quebrado";
    if (strcmp(sala, "Escritorio") == 0) return "documentos rasgados";
    if (strcmp(sala, "Jardim") == 0) return "pegadas misteriosas";
    if (strcmp(sala, "Porão") == 0) return "arma do crime";
    return "nenhuma pista";
}

Pista* explorarSalas(Sala* sala, Pista* bst) {
    if (sala == NULL) return bst;
    printf("\nVoce entrou em: %s\n", sala->nome);
    char* pista = gerarPistaPorSala(sala->nome);
    if (strcmp(pista, "nenhuma pista") != 0) {
        printf("Pista encontrada: %s\n", pista);
        bst = inserirPista(bst, pista);
    } else {
        printf("Nada foi encontrado aqui.\n");
    }
    char opcao;
    printf("Ir para esquerda (e), direita (d) ou sair (s): ");
    scanf(" %c", &opcao);
    if (opcao == 'e') bst = explorarSalas(sala->esq, bst);
    else if (opcao == 'd') bst = explorarSalas(sala->dir, bst);
    else if (opcao == 's') return bst;
    return bst;
}

void verificarSuspeitoFinal(Pista* bst) {
    printf("\n=== Suspeitos Disponiveis ===\n");
    printf("1. Sr. Black\n");
    printf("2. Sra. White\n");
    printf("3. Sr. Green\n");
    printf("==============================\n");

    char acusacao[50];
    printf("\nDigite o nome do suspeito que voce acredita ser o culpado: ");
    scanf(" %[^\n]", acusacao);

    int cont = contarPistasPorSuspeito(bst, acusacao);
    printf("\nPistas que apontam para %s: %d\n", acusacao, cont);

    if (cont >= 2)
        printf("Voce acertou! O suspeito %s e o verdadeiro culpado!\n", acusacao);
    else
        printf("Acusacao incorreta! Faltam evidencias suficientes contra %s.\n", acusacao);
}

int main() {
    for (int i = 0; i < TAM; i++) tabela[i] = NULL;

    inserirNaHash("luva ensanguentada", "Sr. Black");
    inserirNaHash("arma do crime", "Sr. Black");
    inserirNaHash("taca de veneno", "Sra. White");
    inserirNaHash("colar quebrado", "Sra. White");
    inserirNaHash("documentos rasgados", "Sr. Green");
    inserirNaHash("pegadas misteriosas", "Sr. Green");

    Sala* biblioteca = criarSala("Biblioteca");
    Sala* cozinha = criarSala("Cozinha");
    Sala* jantar = criarSala("Sala de Jantar");
    Sala* escritorio = criarSala("Escritorio");
    Sala* jardim = criarSala("Jardim");
    Sala* porao = criarSala("Porão");

    biblioteca->esq = cozinha;
    biblioteca->dir = jantar;
    cozinha->esq = escritorio;
    jantar->dir = jardim;
    escritorio->dir = porao;

    printf("Bem-vindo ao Detective Quest - Nivel Mestre!\n");
    printf("Explore a mansao e descubra o culpado.\n");

    Pista* pistas = NULL;
    pistas = explorarSalas(biblioteca, pistas);

    printf("\nPistas coletadas:\n");
    listarPistas(pistas);

    verificarSuspeitoFinal(pistas);

    return 0;
}
