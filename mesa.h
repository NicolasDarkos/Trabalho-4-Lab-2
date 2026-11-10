#ifndef MESA_H
#define MESA_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define LUGARES_MESA 4

typedef struct mesa
{
    int numeroMesa;
    bool livre;
    int lugaresOcu;   
    int comanda;      
    int qtdPratos;   
} Mesa;

#endif