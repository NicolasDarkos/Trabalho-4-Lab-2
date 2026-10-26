#ifndef MESA_H
#define MESA_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct mesa
{
    int lugaresOcu;

    int numeroMesa;
    int comanda;
    bool livre;

} Mesa;

void ocuparMesa(Mesa *mesa, int pessoas, int comanda);

#endif