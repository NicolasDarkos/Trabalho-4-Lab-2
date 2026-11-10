#ifndef PRATO_H
#define PRATO_H

#include <stdio.h>
#include <stdlib.h>

typedef struct prato
{
    struct prato *prox;
} Prato;

typedef struct pilha
{
    int qtdPratos;
    Prato *topo;
} Pilha;

Pilha *criarPilha(void);

void empilharPrato(Pilha *pilha, int qtd);

int desempilharPrato(Pilha *pilha, int qtd);

int quantidadePratos(Pilha *pilha);

void imprimirPilha(Pilha *pilha);

void liberarPilha(Pilha *pilha);

#endif