#include <stdio.h>

#include "restaurante.h"
#include "menu.h"

int main(void)
{
    Restaurante *restaurante = NULL;
    int opcao;

    do
    {
        exibirMenu();
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        if (restaurante == NULL && opcao >= 2 && opcao <= 6)
        {
            printf("\n[AVISO] Abra o restaurante primeiro (opcao 1).\n");
            continue;
        }

        switch (opcao)
        {
            case 1:
                restaurante = abrirRestaurante(restaurante);
                break;

            case 2:
                encontrarMesa(restaurante);
                break;

            case 3:
                liberarMesa(restaurante);
                break;

            case 4:
                desistirDeEsperar(restaurante);
                break;

            case 5:
                reporPratosMenu(restaurante);
                break;

            case 6:
                menuImprimir(restaurante);
                break;

            case 0:
                printf("\nEncerrando...\n");
                break;

            default:
                printf("\n[ERRO] Opcao invalida.\n");
                break;
        }
    } while (opcao != 0);

    liberarRestaurante(restaurante);

    return 0;
}