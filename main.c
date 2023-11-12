#include <stdio.h>
#include <stdlib.h>

typedef struct nodo
{
    struct nodo *proximo_nodo;
    int dado;
} nodo_t;

typedef struct 
{
    nodo_t *topo;
    int qtd_nodos;
} pilha_t;

nodo_t *criar_nodo(nodo_t *proximo_nodo, int dado)
{
    nodo_t *novo_nodo = malloc(sizeof(nodo_t));
    novo_nodo->proximo_nodo = proximo_nodo;
    novo_nodo->dado = dado;
    return novo_nodo;
}

pilha_t *criar_pilha(void)
{
    pilha_t *nova_pilha = malloc(sizeof(pilha_t));
    nova_pilha->topo = NULL;
    nova_pilha->qtd_nodos = 0;
    return nova_pilha;
}

void empilhar(pilha_t *pilha, nodo_t *nodo_inserido)
{
    nodo_inserido->proximo_nodo = pilha->topo;
    pilha->topo = nodo_inserido;
    ++pilha->qtd_nodos;
}

void *desempilhar(pilha_t *pilha)
{
    nodo_t *nodo_removido = pilha->topo;
    pilha->topo = pilha->topo->proximo_nodo;
    free(nodo_removido);
    --pilha->qtd_nodos;
}

nodo_t *consultar(pilha_t *pilha)
{
    return pilha->topo;
}

void destruir_nodos(nodo_t *nodo)
{
    if (nodo->proximo_nodo != NULL)
    {
        destruir_nodos(nodo->proximo_nodo);
    }
    free(nodo);
}

void destruir_pilha(pilha_t *pilha)
{
    destruir_nodos(pilha->topo);
    free(pilha);
}

enum opcoes
{
    EMPILHAR = 1,
    DESEMPILHAR,
    CONSULTAR,
    DESTRUIR,
    SAIR
};

int main(void)
{
    pilha_t *pilha = criar_pilha();
    int option;

    do {
    //exibir painel
        puts("selecione uma opção");
        puts("1. Empilhar");
        puts("2. desempilhar");
        puts("3. consultar");
        puts("4. destruir pilha");
        puts("5. sair");
        printf("> ");

    // ler opção
        scanf("%d", &option);

    //executar opção
        switch (option)
        {
        case EMPILHAR:
            int valor;
            puts("Digite o valor empilhado");
            scanf("%d", &valor);
            empilhar(pilha, criar_nodo(NULL, valor));
            break;
        case DESEMPILHAR:
            desempilhar(pilha);
            break;
        case CONSULTAR:
            printf("topo = %d\n", (int)consultar(pilha)->dado);
            break;
        case DESTRUIR:
            destruir_pilha(pilha);
            break;
        case SAIR:
            break;
        default:
            perror("opção invalida");
            break;
        }
    } while (option != 5);

}