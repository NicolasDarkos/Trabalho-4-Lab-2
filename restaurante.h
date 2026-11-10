#ifndef RESTAURANTE_H
#define RESTAURANTE_H

#include "prato.h"
#include "mesa.h"
#include "filaDeEspera.h"

typedef struct restaurante
{
    int nMesas;
    int nLinhas;
    int nColunas;

    int lugares;

    int proxComanda;
    int proxSenha;

    Mesa **mesas;
    Pilha *pilha;
    Fila *fila;
} Restaurante;

Restaurante *criarRestaurante(void);

void liberarRestaurante(Restaurante *restaurante);

void encontrarMesa(Restaurante *restaurante);

void liberarMesa(Restaurante *restaurante);

void imprimirMesa(Restaurante *restaurante);

void imprimirTodasMesas(Restaurante *restaurante);

#endif