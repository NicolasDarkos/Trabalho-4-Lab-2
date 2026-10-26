#ifndef RESTAURANTE_H
#define RESTAURANTE_H

#include "mesa.h"
#include "pilha.h"
#include "fila.h"

struct restaurante typedef Restaurante;

Restaurante *abrirRestaurante(int linhas, int colunas);

void chegarGrupo(Restaurante *r);
void liberarMesa(Restaurante *r);

void desistirFila(Restaurante *r);
void reporPratos(Restaurante *r);

void imprimirMesa(Restaurante *r);
void imprimirTodasMesas(Restaurante *r);

void imprimirFila(Restaurante *r);
void imprimirPilha(Restaurante *r);

void liberarRestaurante(Restaurante *r);

#endif