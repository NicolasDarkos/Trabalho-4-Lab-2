#include "restaurante.h"
#include "mesa.h"

struct Mesa
{
    int lugaresOcu;

    int numeroMesa;
    int comanda;
    bool livre;

} typedef mesa;

void ocuparMesa(Restaurante * restaurante)
{
    int nGrupo, grupoPorMesa;

    do
    {
    printf("Digite quantas pessoas estao no seu grupo: ");
    scanf("%d", &nGrupo);
    } while (nGrupo <= 0);
    
    grupoPorMesa = nGrupo;

    int linhaAtual = 0, colunaAtual = 0, comandaAtual = 0;

    do
    {
        if(restaurante->mesas[linhaAtual][colunaAtual].livre)
        {
            restaurante->mesas[linhaAtual][colunaAtual].comanda = comandaAtual+1;

            if(grupoPorMesa > restaurante->lugares)
            {
                restaurante->mesas[linhaAtual][colunaAtual].lugaresOcu = restaurante->lugares;
            }
            else
            {
                restaurante->mesas[linhaAtual][colunaAtual].lugaresOcu = grupoPorMesa;
            }

            restaurante->mesas[linhaAtual][colunaAtual].livre = false;

            /*tem que colocar os pratos tbm*/

            grupoPorMesa -= restaurante->lugares;        
        }

        comandaAtual = restaurante->mesas[linhaAtual][colunaAtual].comanda;
        
        colunaAtual++;

        if(colunaAtual >= restaurante->nColunas)
        {
            linhaAtual++;
            colunaAtual = 0;
        }

        if(linhaAtual >= restaurante->nLinhas)
        {
            break;
        }

    }while(grupoPorMesa > 0);

    if(grupoPorMesa > 0)
    {
        adicionarNaFila(grupoPorMesa);
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
    } while (linhaLibera >= restaurante->nLinhas && colunaLibera >= restaurante->nColunas);

    if(restaurante->mesas[linhaLibera][colunaLibera].livre)
    {
        printf("A mesa já esta livre");
        return;
    }

    restaurante->mesas[linhaLibera][colunaLibera].lugaresOcu = 0;

    /*tem que repor os pratos tbm*/

    restaurante->mesas[linhaLibera][colunaLibera].livre = true;    
}

void imprimeMesa(Restaurante * restaurante)
{
    int linhaDesejada, colunaDesejada;
    
    do
    {
        printf("Digite qual linha a mesa que desejada pertence: ");
        scanf("%d", &linhaDesejada);

        printf("Digite qual coluna a mesa que desejada pertence: ");
        scanf("%d", &colunaDesejada);
    } while (linhaDesejada >= restaurante->nLinhas && colunaDesejada >= restaurante->nColunas);

    printf("Mesa numero %d: ocupada por %d pessoas", 
            restaurante->mesas[linhaDesejada][colunaDesejada].numeroMesa, restaurante->mesas[linhaDesejada][colunaDesejada].lugaresOcu);
}

void imprimeTodasMesas(Restaurante * restaurante)
{
    for(int i = 0; i < restaurante->nLinhas; i++)
    {
        for(int j = 0; j < restaurante->nColunas; j++)
        {
            printf("\nMesa numero %d: ocupada por %d pessoas", 
                restaurante->mesas[i][j].numeroMesa, restaurante->mesas[i][j].lugaresOcu);
        }
    }
}