#ifndef PRATO_H
#define PRATO_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Prato
{
    struct Prato *prox;
} Prato;

typedef struct
{
    int max;
    int qntd_pratos;
    Prato *topo;
} Pilha;

Pilha *CriarPilha(int maxPratos); // precisa definir na main com 4*nMesas

void EmpilharPrato(Pilha *pilha, int qntd);
void DesempilharPrato(Pilha *pilha, int qntd);
void ReporPratos(Pilha *pilha);

void QuantidadePratos(Pilha *pilha);

void LiberarPratos(Pilha *pilha);
void LiberarPilha(Pilha *pilha);

#endif
