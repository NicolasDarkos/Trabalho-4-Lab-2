#ifndef FILADEESPERA_H
#define FILADEESPERA_H

#include <stdio.h>
#include <stdlib.h>

typedef struct grupo
{
    int senha;
    int qtdPessoas;
    struct grupo *prox;
} Grupo;

typedef struct fila
{
    Grupo *inicio;
    Grupo *fim;
    int totalGrupos;
    int totalPessoas;
} Fila;

Fila *criarFila(void);

int filaVazia(Fila *fila);

int enfileirar(Fila *fila, int senha, int qtdPessoas);

int desenfileirar(Fila *fila, int *senha, int *qtdPessoas);

int atenderParcialmente(Fila *fila, int pessoasAtendidas);

int consultarPrimeiro(Fila *fila, int *senha, int *qtdPessoas);

int removerPorSenha(Fila *fila, int senha);

void obterEstatisticasFila(Fila *fila, int *totalGrupos, int *totalPessoas);

int tamanhoFila(Fila *fila);

void imprimirFila(Fila *fila);

void liberarFila(Fila *fila);

#endif