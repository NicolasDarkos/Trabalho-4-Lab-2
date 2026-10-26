#include "restaurante.h"
#include "mesa.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>    

void ocuparMesa(Mesa *mesa, int pessoas, int comanda)
{
    mesa->livre = false;
    mesa->lugaresOcu = pessoas;
    mesa->comanda = comanda;

    /*tem que verificar os pratos*/
}

void encontrarMesa(Restaurante * restaurante)
{
    int nGrupo = 0;

    do
    {
    printf("Digite quantas pessoas estao no seu grupo: ");
    scanf("%d", &nGrupo);
    } while (nGrupo <= 0);
    
    nGrupo = nGrupo;

    for (int i = 0; i < restaurante->nLinhas && nGrupo > 0; i++)
    {
        for (int j = 0; j < restaurante->nColunas && nGrupo > 0; j++)
        {
            Mesa *m = &restaurante->mesas[i][j];

            if (m->livre)
            {
                int sentam = (nGrupo > restaurante->lugares) ? restaurante->lugares : nGrupo;

                restaurante->proxComanda++;

                ocuparMesa(m, sentam, restaurante->proxComanda);
             
                nGrupo -= sentam;

                printf("%d pessoa(s) na mesa %d (comanda %d)\n",
                       sentam, m->numeroMesa, m->comanda);
            }
        }
    }

    if(nGrupo > 0)
    {
        adicionarNaFila(nGrupo);
    }
}

void liberarMesa(Restaurante * restaurante)
{
    int linhaLibera, colunaLibera;

    do
    {
        printf("Digite qual linha a mesa que sera liberada pertence: ");
        scanf("%d", &linhaLibera);

        printf("Digite qual coluna a mesa que sera liberada pertence: ");
        scanf("%d", &colunaLibera);
    } while (linhaLibera >= restaurante->nLinhas || linhaLibera < 0 || colunaLibera >= restaurante->nColunas || colunaLibera < 0);
    
    if(restaurante->mesas[linhaLibera][colunaLibera].livre)
    {
        printf("A mesa já esta livre\n");
        return;
    }

    restaurante->mesas[linhaLibera][colunaLibera].lugaresOcu = 0;
    restaurante->mesas[linhaLibera][colunaLibera].comanda = 0;

    /*tem que repor os pratos tbm*/

    restaurante->mesas[linhaLibera][colunaLibera].livre = true;    
}

void imprimeMesa(Restaurante * restaurante)
{
    int nMesa;

    Mesa * mesaPesquisa = NULL;

    printf("Digite o numero da mesa desejada: ");
    scanf("%d", &nMesa);

    for(int i = 0; i < restaurante->nLinhas; i++)
    {
        for(int j = 0; j < restaurante->nColunas; j++)
        {
            if(restaurante->mesas[i][j].numeroMesa == nMesa)
            {
                mesaPesquisa = &restaurante->mesas[i][j];
            }
        }
    }

    if(mesaPesquisa == NULL)
    {
        printf("\nMesa nao encontrada\n");
        return;
    }

    if(mesaPesquisa->livre)
    {
        printf("\nMesa numero %d: livre\n", mesaPesquisa->numeroMesa);
    }
    else
    {
        printf("\nMesa numero %d: ocupada por %d pessoas\n", mesaPesquisa->numeroMesa, mesaPesquisa->lugaresOcu);
    }
    
}

void imprimeTodasMesas(Restaurante * restaurante)
{
    for(int i = 0; i < restaurante->nLinhas; i++)
    {
        for(int j = 0; j < restaurante->nColunas; j++)
        {
            if(restaurante->mesas[i][j].livre)
            {
                printf("\nMesa numero %d: livre", restaurante->mesas[i][j].numeroMesa);
            }
            else
            {
                printf("\nMesa numero %d: ocupada por %d pessoas", 
                    restaurante->mesas[i][j].numeroMesa, restaurante->mesas[i][j].lugaresOcu);
            }
        }
    }
}