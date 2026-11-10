#ifndef MENU_H
#define MENU_H

#include "restaurante.h"

void exibirMenu(void);

Restaurante *abrirRestaurante(Restaurante *restaurante);

void desistirDeEsperar(Restaurante *restaurante);

void reporPratosMenu(Restaurante *restaurante);

void menuImprimir(Restaurante *restaurante);

#endif