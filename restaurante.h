#ifndef RESTAURANTE_H
#define RESTAURANTE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "mesa.h"

typedef struct restaurante {
    int nMesas, nLinhas, nColunas;

    int lugares;

    int proxComanda;
    int proxSenha;

    Mesa **mesas;

} Restaurante;

Restaurante *CriaRestaurante(void);

void liberaRestaurante(Restaurante *restaurante);

void encontrarMesa(Restaurante * restaurante);

void liberarMesa(Restaurante * restaurante);

void imprimeMesa(Restaurante * restaurante);

void imprimeTodasMesas(Restaurante * restaurante);

#endif