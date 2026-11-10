#include "filaDeEspera.h"

Fila *criarFila(void)
{
    Fila *fila = (Fila *)malloc(sizeof(Fila));

    if (fila == NULL)
    {
        printf("[ERRO] Falha na alocacao de memoria para a fila de espera.\n");
        return NULL;
    }

    fila->inicio = NULL;
    fila->fim = NULL;
    fila->totalGrupos = 0;
    fila->totalPessoas = 0;

    return fila;
}

int filaVazia(Fila *fila)
{
    if (fila == NULL || fila->inicio == NULL)
    {
        return 1;
    }

    return 0;
}

int enfileirar(Fila *fila, int senha, int qtdPessoas)
{
    Grupo *novo;

    if (fila == NULL || qtdPessoas <= 0)
    {
        return 0;
    }

    novo = (Grupo *)malloc(sizeof(Grupo));

    if (novo == NULL)
    {
        printf("[ERRO] Falha na alocacao de memoria para o grupo da fila.\n");
        return 0;
    }

    novo->senha = senha;
    novo->qtdPessoas = qtdPessoas;
    novo->prox = NULL;

    if (filaVazia(fila))
    {
        fila->inicio = novo;
        fila->fim = novo;
    }
    else
    {
        fila->fim->prox = novo;
        fila->fim = novo;
    }

    fila->totalGrupos++;
    fila->totalPessoas += qtdPessoas;

    return 1;
}

int desenfileirar(Fila *fila, int *senha, int *qtdPessoas)
{
    Grupo *removido;

    if (filaVazia(fila))
    {
        return 0;
    }

    removido = fila->inicio;

    if (senha != NULL)
    {
        *senha = removido->senha;
    }
    if (qtdPessoas != NULL)
    {
        *qtdPessoas = removido->qtdPessoas;
    }

    fila->inicio = removido->prox;
    if (fila->inicio == NULL)
    {
        fila->fim = NULL;
    }

    fila->totalGrupos--;
    fila->totalPessoas -= removido->qtdPessoas;

    free(removido);

    return 1;
}

int atenderParcialmente(Fila *fila, int pessoasAtendidas)
{
    Grupo *primeiro;

    if (filaVazia(fila) || pessoasAtendidas <= 0)
    {
        return 0;
    }

    primeiro = fila->inicio;

    if (pessoasAtendidas < primeiro->qtdPessoas)
    {
        primeiro->qtdPessoas -= pessoasAtendidas;
        fila->totalPessoas -= pessoasAtendidas;
        return 1;
    }

    return desenfileirar(fila, NULL, NULL);
}

int consultarPrimeiro(Fila *fila, int *senha, int *qtdPessoas)
{
    if (filaVazia(fila))
    {
        return 0;
    }

    if (senha != NULL)
    {
        *senha = fila->inicio->senha;
    }
    if (qtdPessoas != NULL)
    {
        *qtdPessoas = fila->inicio->qtdPessoas;
    }

    return 1;
}

int removerPorSenha(Fila *fila, int senha)
{
    Grupo *atual;
    Grupo *anterior = NULL;

    if (filaVazia(fila))
    {
        return 0;
    }

    atual = fila->inicio;

    while (atual != NULL && atual->senha != senha)
    {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual == NULL)
    {
        return 0;
    }

    if (anterior == NULL)
    {
        fila->inicio = atual->prox;
        if (fila->inicio == NULL)
        {
            fila->fim = NULL;
        }
    }
    else
    {
        anterior->prox = atual->prox;
        if (atual == fila->fim)
        {
            fila->fim = anterior;
        }
    }

    fila->totalGrupos--;
    fila->totalPessoas -= atual->qtdPessoas;

    free(atual);

    return 1;
}

void obterEstatisticasFila(Fila *fila, int *totalGrupos, int *totalPessoas)
{
    int grupos = 0;
    int pessoas = 0;
    Grupo *atual;

    if (fila != NULL)
    {
        atual = fila->inicio;

        while (atual != NULL)
        {
            grupos++;
            pessoas += atual->qtdPessoas;
            atual = atual->prox;
        }
    }

    if (totalGrupos != NULL)
    {
        *totalGrupos = grupos;
    }
    if (totalPessoas != NULL)
    {
        *totalPessoas = pessoas;
    }
}

int tamanhoFila(Fila *fila)
{
    if (filaVazia(fila))
    {
        return 0;
    }

    return fila->totalGrupos;
}

void imprimirFila(Fila *fila)
{
    Grupo *atual;
    int posicao = 1;
    int grupos, pessoas;

    printf("\n+--------------------------------------+\n");
    printf("| %-36s |\n", "FILA DE ESPERA");

    if (filaVazia(fila))
    {
        printf("+--------------------------------------+\n");
    }
    else
    {
        printf("+---------+-------+--------------------+\n");
        printf("| POSICAO | SENHA | QUANTIDADE PESSOAS |\n");
        printf("+---------+-------+--------------------+\n");

        atual = fila->inicio;

        while (atual != NULL)
        {
            printf("| %-7d | %-5d | %-18d |\n", posicao, atual->senha, atual->qtdPessoas);
            atual = atual->prox;
            posicao++;
        }

        printf("+---------+-------+--------------------+\n");
    }

    obterEstatisticasFila(fila, &grupos, &pessoas);

    printf("| Grupos aguardando: %-17d |\n", grupos);
    printf("| Pessoas aguardando: %-16d |\n", pessoas);
    printf("+--------------------------------------+\n");
}

void liberarFila(Fila *fila)
{
    Grupo *atual;
    Grupo *proximo;

    if (fila == NULL)
    {
        return;
    }

    atual = fila->inicio;

    while (atual != NULL)
    {
        proximo = atual->prox;
        free(atual);
        atual = proximo;
    }

    free(fila);
}