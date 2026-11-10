#include "prato.h"

Pilha *criarPilha(void)
{
    Pilha *pilha = (Pilha *)malloc(sizeof(Pilha));

    if (pilha == NULL)
    {
        printf("[ERRO] Falha na alocacao de memoria para a pilha de pratos.\n");
        return NULL;
    }

    pilha->topo = NULL;
    pilha->qtdPratos = 0;

    return pilha;
}

void empilharPrato(Pilha *pilha, int qtd)
{
    int i;
    Prato *novo;

    if (pilha == NULL)
    {
        printf("[ERRO] A pilha de pratos nao foi criada.\n");
        return;
    }

    for (i = 0; i < qtd; i++)
    {
        novo = (Prato *)malloc(sizeof(Prato));

        if (novo == NULL)
        {
            printf("[ERRO] Falha na alocacao de memoria para um prato.\n");
            return;
        }

        novo->prox = pilha->topo;
        pilha->topo = novo;
        pilha->qtdPratos++;
    }
}

int desempilharPrato(Pilha *pilha, int qtd)
{
    int removidos = 0;
    Prato *aux;

    if (pilha == NULL)
    {
        printf("[ERRO] A pilha de pratos nao foi criada.\n");
        return 0;
    }

    while (removidos < qtd && pilha->topo != NULL)
    {
        aux = pilha->topo;
        pilha->topo = aux->prox;
        free(aux);

        pilha->qtdPratos--;
        removidos++;
    }

    return removidos;
}

int quantidadePratos(Pilha *pilha)
{
    if (pilha == NULL)
    {
        return 0;
    }

    return pilha->qtdPratos;
}

void imprimirPilha(Pilha *pilha)
{
    printf("\n+--------------------------------------+\n");
    printf("| %-36s |\n", "PILHA DE PRATOS");
    printf("+--------------------------------------+\n");
    printf("| Pratos disponiveis: %-16d |\n", quantidadePratos(pilha));
    printf("+--------------------------------------+\n");
}

void liberarPilha(Pilha *pilha)
{
    if (pilha == NULL)
    {
        return;
    }

    desempilharPrato(pilha, pilha->qtdPratos);
    free(pilha);
}