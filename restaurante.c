#include "restaurante.h"

static void liberarMatrizMesas(Mesa **mesas, int linhas)
{
    int i;

    for (i = 0; i < linhas; i++)
    {
        free(mesas[i]);
    }

    free(mesas);
}

Restaurante *criarRestaurante(void)
{
    Restaurante *restaurante;
    Mesa **mesas;
    int linhas, colunas, nMesa = 0;
    int i, j;

    int lugares = 4;

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

    mesas = (Mesa **)malloc(sizeof(Mesa *) * linhas);

    if (mesas == NULL)
    {
        printf("[ERRO] Falha na alocacao de memoria para as mesas.\n");
        return NULL;
    }

    for (i = 0; i < linhas; i++)
    {
        mesas[i] = (Mesa *)malloc(sizeof(Mesa) * colunas);

        if (mesas[i] == NULL)
        {
            printf("[ERRO] Falha na alocacao de memoria para as mesas.\n");
            liberarMatrizMesas(mesas, i);
            return NULL;
        }
    }

    for (i = 0; i < linhas; i++)
    {
        for (j = 0; j < colunas; j++)
        {
            nMesa++;
            mesas[i][j].numeroMesa = nMesa;
            mesas[i][j].livre = true;
            mesas[i][j].lugaresOcu = 0;
            mesas[i][j].comanda = 0;
            mesas[i][j].qtdPratos = lugares;
        }
    }

    restaurante = (Restaurante *)malloc(sizeof(Restaurante));

    if (restaurante == NULL)
    {
        printf("[ERRO] Falha na alocacao de memoria para o restaurante.\n");
        liberarMatrizMesas(mesas, linhas);
        return NULL;
    }

    restaurante->mesas = mesas;
    restaurante->nLinhas = linhas;
    restaurante->nColunas = colunas;
    restaurante->nMesas = linhas * colunas;
    restaurante->lugares = lugares;
    restaurante->proxSenha = 0;
    restaurante->proxComanda = 0;
    restaurante->pilha = NULL;
    restaurante->fila = NULL;

    restaurante->pilha = criarPilha();
    restaurante->fila = criarFila();

    if (restaurante->pilha == NULL || restaurante->fila == NULL)
    {
        liberarRestaurante(restaurante);
        return NULL;
    }

    empilharPrato(restaurante->pilha, restaurante->nMesas * lugares);

    return restaurante;
}

void liberarRestaurante(Restaurante *restaurante)
{
    if (restaurante == NULL)
    {
        return;
    }

    liberarMatrizMesas(restaurante->mesas, restaurante->nLinhas);
    liberarPilha(restaurante->pilha);
    liberarFila(restaurante->fila);

    free(restaurante);
}