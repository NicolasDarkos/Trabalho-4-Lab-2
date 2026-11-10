#include "restaurante.h"
#include "mesa.h"

static Mesa *buscarMesa(Restaurante *restaurante, int nMesa)
{
    int linha, coluna;

    if (nMesa < 1 || nMesa > restaurante->nMesas)
    {
        return NULL;
    }

    linha = (nMesa - 1) / restaurante->nColunas;
    coluna = (nMesa - 1) % restaurante->nColunas;

    return &restaurante->mesas[linha][coluna];
}

static void ocuparMesa(Restaurante *restaurante, Mesa *mesa, int pessoas, int comanda)
{
    mesa->livre = false;
    mesa->lugaresOcu = pessoas;
    mesa->comanda = comanda;

    if (mesa->qtdPratos > pessoas)
    {
        empilharPrato(restaurante->pilha, mesa->qtdPratos - pessoas);
        mesa->qtdPratos = pessoas;
    }
    else if (mesa->qtdPratos < pessoas)
    {
        mesa->qtdPratos += desempilharPrato(restaurante->pilha, pessoas - mesa->qtdPratos);

        if (mesa->qtdPratos < pessoas)
        {
            printf("[AVISO] Faltam %d prato(s) na mesa %d (pilha de pratos vazia).\n",
                   pessoas - mesa->qtdPratos, mesa->numeroMesa);
        }
    }
}

static void sentarGrupo(Restaurante *restaurante, Mesa *mesa, int pessoas)
{
    restaurante->proxComanda++;

    ocuparMesa(restaurante, mesa, pessoas, restaurante->proxComanda);

    printf("[OK] %d pessoa(s) na mesa %d (comanda %d).\n",
           pessoas, mesa->numeroMesa, mesa->comanda);
}

// Chama os grupos da fila de espera enquanto houver mesas livres.
static void chamarFila(Restaurante *restaurante)
{
    int i, j;
    int senha, qtdPessoas, sentam;
    Mesa *mesa;

    for (i = 0; i < restaurante->nLinhas && !filaVazia(restaurante->fila); i++)
    {
        for (j = 0; j < restaurante->nColunas && !filaVazia(restaurante->fila); j++)
        {
            mesa = &restaurante->mesas[i][j];

            if (mesa->livre)
            {
                consultarPrimeiro(restaurante->fila, &senha, &qtdPessoas);

                sentam = (qtdPessoas > restaurante->lugares) ? restaurante->lugares : qtdPessoas;

                printf("[FILA] Senha %d chamada.\n", senha);
                sentarGrupo(restaurante, mesa, sentam);

                // se sobrarem pessoas, o grupo continua na fila com a mesma senha
                atenderParcialmente(restaurante->fila, sentam);

                if (sentam < qtdPessoas)
                {
                    printf("[FILA] Senha %d continua aguardando por %d lugar(es).\n",
                           senha, qtdPessoas - sentam);
                }
            }
        }
    }
}

// Cabecalho da tabela de mesas.
static void imprimirCabecalhoMesas(const char *titulo)
{
    printf("\n+---------------------------------------------+\n");
    printf("| %-43s |\n", titulo);
    printf("+------+---------+---------+---------+--------+\n");
    printf("| MESA | STATUS  | PESSOAS | COMANDA | PRATOS |\n");
    printf("+------+---------+---------+---------+--------+\n");
}

// Linha da tabela correspondente a uma mesa.
static void imprimirLinhaMesa(Mesa *mesa)
{
    if (mesa->livre)
    {
        printf("| %-4d | %-7s | %-7s | %-7s | %-6d |\n",
               mesa->numeroMesa, "LIVRE", "-", "-", mesa->qtdPratos);
    }
    else
    {
        printf("| %-4d | %-7s | %-7d | %-7d | %-6d |\n",
               mesa->numeroMesa, "OCUPADA", mesa->lugaresOcu, mesa->comanda, mesa->qtdPratos);
    }
}

void encontrarMesa(Restaurante *restaurante)
{
    int nGrupo = 0;
    int i, j;
    int sentam, senha;
    Mesa *mesa;

    do
    {
        printf("Digite quantas pessoas estao no seu grupo: ");
        scanf("%d", &nGrupo);
    } while (nGrupo <= 0);

    printf("\n");

    for (i = 0; i < restaurante->nLinhas && nGrupo > 0; i++)
    {
        for (j = 0; j < restaurante->nColunas && nGrupo > 0; j++)
        {
            mesa = &restaurante->mesas[i][j];

            if (mesa->livre)
            {
                sentam = (nGrupo > restaurante->lugares) ? restaurante->lugares : nGrupo;

                sentarGrupo(restaurante, mesa, sentam);

                nGrupo -= sentam;
            }
        }
    }

    if (nGrupo > 0)
    {
        senha = restaurante->proxSenha + 1;

        if (enfileirar(restaurante->fila, senha, nGrupo))
        {
            restaurante->proxSenha = senha;
            printf("[FILA] %d pessoa(s) aguardam por mesa. Senha do grupo: %d.\n", nGrupo, senha);
        }
        else
        {
            printf("[ERRO] Nao foi possivel colocar o grupo na fila de espera.\n");
        }
    }
}

void liberarMesa(Restaurante *restaurante)
{
    int nMesa;
    Mesa *mesa;

    do
    {
        printf("Digite o numero da mesa que sera liberada: ");
        scanf("%d", &nMesa);

        mesa = buscarMesa(restaurante, nMesa);

        if (mesa == NULL)
        {
            printf("[ERRO] Mesa %d nao existe.\n", nMesa);
        }
    } while (mesa == NULL);

    if (mesa->livre)
    {
        printf("\n[AVISO] A mesa %d ja esta livre.\n", mesa->numeroMesa);
        return;
    }

    empilharPrato(restaurante->pilha, mesa->qtdPratos);

    mesa->livre = true;
    mesa->lugaresOcu = 0;
    mesa->comanda = 0;

    mesa->qtdPratos = desempilharPrato(restaurante->pilha, restaurante->lugares);

    printf("\n[OK] Mesa %d liberada e arrumada com %d prato(s).\n", mesa->numeroMesa, mesa->qtdPratos);

    if (mesa->qtdPratos < restaurante->lugares)
    {
        printf("[AVISO] Faltam %d prato(s) na mesa %d (pilha de pratos insuficiente).\n",
               restaurante->lugares - mesa->qtdPratos, mesa->numeroMesa);
    }

    chamarFila(restaurante);
}

void imprimirMesa(Restaurante *restaurante)
{
    int nMesa;
    Mesa *mesa;

    printf("Digite o numero da mesa desejada: ");
    scanf("%d", &nMesa);

    mesa = buscarMesa(restaurante, nMesa);

    if (mesa == NULL)
    {
        printf("\n[ERRO] Mesa %d nao encontrada.\n", nMesa);
        return;
    }

    imprimirCabecalhoMesas("CONSULTA DE MESA");
    imprimirLinhaMesa(mesa);
    printf("+------+---------+---------+---------+--------+\n");
}

void imprimirTodasMesas(Restaurante *restaurante)
{
    int i, j;

    imprimirCabecalhoMesas("OCUPACAO DAS MESAS");

    for (i = 0; i < restaurante->nLinhas; i++)
    {
        for (j = 0; j < restaurante->nColunas; j++)
        {
            imprimirLinhaMesa(&restaurante->mesas[i][j]);
        }
    }

    printf("+------+---------+---------+---------+--------+\n");
}