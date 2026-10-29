#include "prato.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

Pilha *CriarPilha(maxPratos)
{
    Pilha *pilha = (Pilha *)malloc(sizeof(Pilha));
    if (pilha != NULL)
    {
        pilha->topo = NULL;
        pilha->qntd_pratos = 0;
        pilha->max = maxPratos;
    }
    return pilha;
}

void EmpilharPrato(Pilha *pilha, int qntd)
{
    for (int i = 0; i < qntd; i++)
    {
        Prato *novo;
        if (pilha == NULL)
        {
            printf("A pilha de pratos nao foi criada ainda");
            return;
        }

        novo = (Prato *)malloc(sizeof(Prato));

        if (novo == NULL)
            return;

        novo->prox = pilha->topo;
        pilha->topo = novo;
        pilha->qntd_pratos++;
    }
}

void DesempilharPrato(Pilha *pilha, int qntd)
{
    for (int i = 0; i < qntd; i++)
    {
        Prato *aux;
        if (pilha == NULL)
        {
            printf("A pilha de pratos nao foi criada ainda");
            return;
        }

        // mesma coisa aqui, nao sei se é so um de cada vez

        if (pilha->topo == NULL)
        {
            printf("A pilha esta vazia.");
            return;
        }
        aux = pilha->topo;
        pilha->topo = aux->prox;
        free(aux);
        pilha->qntd_pratos--;
    }
}

void QuantidadePratos(Pilha *pilha)
{
    printf("%d", pilha->qntd_pratos);
}

void ReporPratos(Pilha *pilha)
{
    EmpilharPrato(pilha, (pilha->max - pilha->qntd_pratos));
}

void LiberarPratos(Pilha *pilha)
{
    DesempilharPrato(pilha, pilha->qntd_pratos);
}

void LiberarPilha(Pilha *pilha)
{
    if (pilha->topo != NULL)
        LiberarPratos(pilha);

    free(pilha);
}
