
#include "prato.h"
#include "mesa.h"
#include "restaurante.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

Restaurante *CriaRestaurante(void)
{
    int linhas, colunas, nMesa = 0;

    do
    {
        printf("Digite o numero de linhas: ");
        scanf("%d", &linhas);
    } while (linhas <= 0);

    do
    {
        printf("Digite o numero de colunas: ");
        scanf("%d", &colunas);
    } while (colunas <= 0);

    Mesa **mesas = (Mesa **)malloc(sizeof(Mesa *) * linhas);

    if (mesas == NULL)
    {
        return NULL;
    }

    for (int i = 0; i < linhas; i++)
    {
        mesas[i] = (Mesa *)malloc(sizeof(Mesa) * colunas);

        if (mesas[i] == NULL)
        {
            for (int k = 0; k < i; k++)
            {
                free(mesas[k]);
            }
            free(mesas);
            return NULL;
        }
    }

    for (int i = 0; i < linhas; i++)
    {
        for (int j = 0; j < colunas; j++)
        {
            nMesa++;
            mesas[i][j].numeroMesa = nMesa;
            mesas[i][j].lugaresOcu = 0;
            mesas[i][j].livre = true;
            mesas[i][j].comanda = 0;
        }
    }

    Restaurante *restauranteC = (Restaurante *)malloc(sizeof(Restaurante));

    if (restauranteC == NULL)
    {
        for (int i = 0; i < linhas; i++)
        {
            free(mesas[i]);
        }
        free(mesas);
        return NULL;
    }

    restauranteC->mesas = mesas;

    restauranteC->nLinhas = linhas;
    restauranteC->nColunas = colunas;

    restauranteC->lugares = 4;

    restauranteC->nMesas = linhas * colunas;

    restauranteC->proxSenha = 0;
    restauranteC->proxComanda = 0;

    int max = nMesa * 4;
    restauranteC->pilha = CriarPilha(max);

    return restauranteC;
}

void liberaRestaurante(Restaurante *restaurante)
{
    if (restaurante == NULL)
    {
        return;
    }

    for (int i = 0; i < restaurante->nLinhas; i++)
    {
        free(restaurante->mesas[i]);
    }

    free(restaurante->mesas);
    free(restaurante);
}