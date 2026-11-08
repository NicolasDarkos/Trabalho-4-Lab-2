#include "filaDeEspera.h"


// Inicializa e aloca dinamicamente uma nova fila de espera vazia.
Fila *criar_fila(void) {
    Fila *f = (Fila *)malloc(sizeof(Fila));
    if (f == NULL) {
        printf("\n| ERRO | Falha na alocacao de memoria para a fila de espera.\n");
        return NULL;
    }

    f->inicio = NULL;
    f->fim = NULL;
    f->total_grupos = 0;
    f->total_pessoas = 0;

    return f;
}


// Verifica se a fila de espera esta vazia ou nao alocada.
int fila_vazia(Fila *f) {
    if (f == NULL || f->inicio == NULL) {
        return 1;
    }
    return 0;
}


// Adiciona um novo grupo com sua senha e quantidade de pessoas ao final da fila.
int enfileirar(Fila *f, int senha, int qtd_pessoas) {
    if (f == NULL || qtd_pessoas <= 0) {
        return 0;
    }

    Grupo *novo = (Grupo *)malloc(sizeof(Grupo));
    if (novo == NULL) {
        printf("\n| ERRO | Falha na alocacao de memoria para o grupo da fila.\n");
        return 0;
    }

    novo->senha = senha;
    novo->qtd_pessoas = qtd_pessoas;
    novo->prox = NULL;

    if (fila_vazia(f)) {
        f->inicio = novo;
        f->fim = novo;
    } else {
        f->fim->prox = novo;
        f->fim = novo;
    }

    f->total_grupos++;
    f->total_pessoas += qtd_pessoas;

    return 1;
}


// Remove o primeiro grupo da fila retornando seus dados quando totalmente atendido.
int desenfileirar(Fila *f, int *senha, int *qtd_pessoas) {
    if (fila_vazia(f)) {
        return 0;
    }

    Grupo *removido = f->inicio;

    if (senha != NULL) {
        *senha = removido->senha;
    }
    if (qtd_pessoas != NULL) {
        *qtd_pessoas = removido->qtd_pessoas;
    }

    f->inicio = removido->prox;
    if (f->inicio == NULL) {
        f->fim = NULL;
    }

    f->total_grupos--;
    f->total_pessoas -= removido->qtd_pessoas;

    free(removido);

    return 1;
}


// Atualiza a quantidade de pessoas do primeiro grupo da fila em caso de atendimento parcial.
int atender_parcialmente(Fila *f, int pessoas_atendidas) {
    if (fila_vazia(f) || pessoas_atendidas <= 0) {
        return 0;
    }

    Grupo *primeiro = f->inicio;

    if (pessoas_atendidas < primeiro->qtd_pessoas) {
        primeiro->qtd_pessoas -= pessoas_atendidas;
        f->total_pessoas -= pessoas_atendidas;
        return 1;
    } else {
        return desenfileirar(f, NULL, NULL);
    }
}


// Permite consultar os dados do primeiro grupo da fila sem remove-lo.
int consultar_primeiro(Fila *f, int *senha, int *qtd_pessoas) {
    if (fila_vazia(f)) {
        return 0;
    }

    if (senha != NULL) {
        *senha = f->inicio->senha;
    }
    if (qtd_pessoas != NULL) {
        *qtd_pessoas = f->inicio->qtd_pessoas;
    }

    return 1;
}


// Busca e remove um grupo arbitrario da fila a partir de sua senha em caso de desistencia.
int remover_por_senha(Fila *f, int senha) {
    if (fila_vazia(f)) {
        return 0;
    }

    Grupo *atual = f->inicio;
    Grupo *ant = NULL;

    while (atual != NULL && atual->senha != senha) {
        ant = atual;
        atual = atual->prox;
    }

    if (atual == NULL) {
        return 0;
    }

    if (ant == NULL) {
        f->inicio = atual->prox;
        if (f->inicio == NULL) {
            f->fim = NULL;
        }
    } else {
        ant->prox = atual->prox;
        if (atual == f->fim) {
            f->fim = ant;
        }
    }

    f->total_grupos--;
    f->total_pessoas -= atual->qtd_pessoas;

    free(atual);

    return 1;
}


// Calcula e retorna por referencia o total de grupos e o somatorio de pessoas aguardando.
void obter_estatisticas_fila(Fila *f, int *total_grupos, int *total_pessoas) {
    int grupos = 0;
    int pessoas = 0;

    if (f != NULL) {
        Grupo *atual = f->inicio;
        while (atual != NULL) {
            grupos++;
            pessoas += atual->qtd_pessoas;
            atual = atual->prox;
        }
    }

    if (total_grupos != NULL) {
        *total_grupos = grupos;
    }
    if (total_pessoas != NULL) {
        *total_pessoas = pessoas;
    }
}


// Retorna a quantidade de grupos atualmente na fila.
int tamanho_fila(Fila *f) {
    if (fila_vazia(f)) {
        return 0;
    }
    return f->total_grupos;
}


// Exibe no terminal a visualizacao formatada de todos os grupos aguardando na fila de espera.
void imprimir_fila(Fila *f) {
    if (fila_vazia(f)) {
        printf("\n+-------------------------------------------------------------+");
        printf("\n|                FILA DE ESPERA ESTA VAZIA                    |");
        printf("\n+-------------------------------------------------------------+\n");
        return;
    }

    printf("\n+---------+-------+--------------------+");
    printf("\n| POSICAO | SENHA | QUANTIDADE PESSOAS |");
    printf("\n+---------+-------+--------------------+");

    Grupo *atual = f->inicio;
    int pos = 1;

    while (atual != NULL) {
        printf("\n| %-7d | %-5d | %-18d |", pos, atual->senha, atual->qtd_pessoas);
        atual = atual->prox;
        pos++;
    }

    printf("\n+---------+-------+--------------------+");
    printf("\n| Total: %d grupo(s) | %d pessoa(s) aguardando atendimento. |", f->total_grupos, f->total_pessoas);
    printf("\n+-------------------------------------------------------------+\n");
}


// Libera toda a memoria dinamicamente alocada para os nos e a estrutura da fila.
void liberar_fila(Fila *f) {
    if (f == NULL) {
        return;
    }

    Grupo *atual = f->inicio;
    while (atual != NULL) {
        Grupo *temp = atual;
        atual = atual->prox;
        free(temp);
    }

    f->inicio = NULL;
    f->fim = NULL;
    f->total_grupos = 0;
    f->total_pessoas = 0;

    free(f);
}
