#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
Estrutura que representa um grupo de clientes aguardando atendimento.
*/
typedef struct grupo {
    int senha;
    int qtd_pessoas;
    struct grupo *prox;
} Grupo, No;

/*
Estrutura de controle (descritor) da fila de espera.
*/
typedef struct fila {
    Grupo *inicio;
    Grupo *fim;
    int total_grupos;
    int total_pessoas;
} Fila;

/*
Prototipos das operacoes da Fila de Espera
*/

// Inicializa e aloca dinamicamente uma nova fila de espera vazia.
Fila* criar_fila(void);

// Verifica se a fila de espera esta vazia ou nao alocada.
int fila_vazia(Fila *f);

// Adiciona um novo grupo com sua senha e quantidade de pessoas ao final da fila.
int enfileirar(Fila *f, int senha, int qtd_pessoas);

// Remove o primeiro grupo da fila retornando seus dados (quando totalmente atendido).
int desenfileirar(Fila *f, int *senha, int *qtd_pessoas);

// Atualiza a quantidade de pessoas do primeiro grupo da fila em caso de atendimento parcial.
int atender_parcialmente(Fila *f, int pessoas_atendidas);

// Permite consultar os dados do primeiro grupo da fila sem desenfileira-lo.
int consultar_primeiro(Fila *f, int *senha, int *qtd_pessoas);

// Busca e remove um grupo arbitrario da fila a partir de sua senha (desistencia).
int remover_por_senha(Fila *f, int senha);

// Calcula e retorna por referencia o total de grupos e o somatorio de pessoas aguardando.
void obter_estatisticas_fila(Fila *f, int *total_grupos, int *total_pessoas);

// Retorna a quantidade de grupos atualmente na fila.
int tamanho_fila(Fila *f);

// Exibe no terminal o estado visual formatado da fila de espera.
void imprimir_fila(Fila *f);

// Libera toda a memoria dinamicamente alocada para os nos e a estrutura da fila.
void liberar_fila(Fila *f);