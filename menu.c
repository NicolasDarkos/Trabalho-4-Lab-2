#include "menu.h"

void exibirMenu(void)
{
    printf("\n+--------------------------------------+\n");
    printf("| %-36s |\n", "RESTAURANTE");
    printf("+--------------------------------------+\n");
    printf("| %-36s |\n", "1) Abrir restaurante");
    printf("| %-36s |\n", "2) Chegada de clientes");
    printf("| %-36s |\n", "3) Finalizar refeicao / liberar mesa");
    printf("| %-36s |\n", "4) Desistir de esperar");
    printf("| %-36s |\n", "5) Repor pratos");
    printf("| %-36s |\n", "6) Imprimir (mesas, fila, pratos)");
    printf("| %-36s |\n", "0) Sair");
    printf("+--------------------------------------+\n");
}

Restaurante *abrirRestaurante(Restaurante *restaurante)
{
    if (restaurante != NULL)
    {
        printf("\n[AVISO] O restaurante ja esta aberto.\n");
        return restaurante;
    }

    restaurante = criarRestaurante();

    if (restaurante == NULL)
    {
        printf("\n[ERRO] Nao foi possivel abrir o restaurante.\n");
    }
    else
    {
        printf("\n[OK] Restaurante aberto com %d mesas (%dx%d), todas arrumadas.\n",
               restaurante->nMesas, restaurante->nLinhas, restaurante->nColunas);
    }

    return restaurante;
}

void desistirDeEsperar(Restaurante *restaurante)
{
    int senha;

    if (filaVazia(restaurante->fila))
    {
        printf("\n[AVISO] A fila de espera esta vazia.\n");
        return;
    }

    imprimirFila(restaurante->fila);

    printf("Digite a senha do grupo que desistiu: ");
    scanf("%d", &senha);

    if (removerPorSenha(restaurante->fila, senha))
    {
        printf("\n[OK] O grupo da senha %d saiu da fila de espera.\n", senha);
    }
    else
    {
        printf("\n[ERRO] Senha %d nao encontrada na fila.\n", senha);
    }
}

void reporPratosMenu(Restaurante *restaurante)
{
    int qtd;

    printf("Quantos pratos deseja repor? ");
    scanf("%d", &qtd);

    if (qtd <= 0)
    {
        printf("\n[ERRO] Quantidade invalida.\n");
        return;
    }

    empilharPrato(restaurante->pilha, qtd);

    printf("\n[OK] %d prato(s) adicionado(s). Total na pilha: %d.\n",
           qtd, quantidadePratos(restaurante->pilha));
}

void menuImprimir(Restaurante *restaurante)
{
    int opcao;

    printf("\n+--------------------------------------+\n");
    printf("| %-36s |\n", "IMPRIMIR");
    printf("+--------------------------------------+\n");
    printf("| %-36s |\n", "1) Pesquisar mesa por numero");
    printf("| %-36s |\n", "2) Ocupacao de todas as mesas");
    printf("| %-36s |\n", "3) Fila de espera");
    printf("| %-36s |\n", "4) Pilha de pratos");
    printf("| %-36s |\n", "5) Tudo");
    printf("+--------------------------------------+\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &opcao);

    switch (opcao)
    {
        case 1:
            imprimirMesa(restaurante);
            break;

        case 2:
            imprimirTodasMesas(restaurante);
            break;

        case 3:
            imprimirFila(restaurante->fila);
            break;

        case 4:
            imprimirPilha(restaurante->pilha);
            break;

        case 5:
            imprimirTodasMesas(restaurante);
            imprimirFila(restaurante->fila);
            imprimirPilha(restaurante->pilha);
            break;

        default:
            printf("\n[ERRO] Opcao invalida.\n");
            break;
    }
}