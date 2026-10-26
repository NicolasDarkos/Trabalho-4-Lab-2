#include "mesa.h"
#include "restaurante.h"

struct restaurante {
    int nMesas, nLinhas, nColunas;

    int proximaComanda;
    int proximaSenha;
    
    Mesa **mesas;
    Pilha *pratos;
    Fila *espera;

} typedef Restaurante;


Restaurante * CriaRestaurante()
{
    int linhas, colunas, nMesa = 0;

    printf("Digite o numero de linhas: ");
    scanf("%d", &linhas);

    printf("Digite o numero de colunas: ");   
    scanf("%d", &colunas);

    mesa ** mesas = (mesa**) malloc(sizeof(mesa*)*linhas);

    for(int i = 0; i < linhas; i++)
    {
        mesas[i] = (mesa*) malloc(sizeof(mesa)*colunas);
    }

    for(int i = 0; i < linhas; i++)
    {
        for(int j = 0; j < colunas; j++)
        {
            nMesa++;
            mesas[i][j].numero = nMesa;
            mesas[i][j].lugaresOcu = 0;
            mesas[i][j].livre = true;            
        }
    }

    Restaurante * restauranteC = (Restaurante*) malloc(sizeof(Restaurante));
    
    restauranteC->mesas = mesas;

    restauranteC->nLinhas = linhas;
    restauranteC->nColunas = colunas;

    restauranteC->lugares = 4;

    restauranteC->nMesa = linhas * colunas;

    return restauranteC;
}