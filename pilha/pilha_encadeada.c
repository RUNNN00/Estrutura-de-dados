#include "pilha.h"
#include <string.h>

/**********************************************
 * Dados
 */
typedef struct no
{
    TipoElemento dado;
    struct no *prox;
} No;

struct pilha
{
    No *topo;
    int qtdeElemento;
};

/***********************************************
 * Implementação
 */
Pilha *pilha_criar()
{
    Pilha *p = (Pilha *)malloc(sizeof(Pilha));
    p->qtdeElemento = 0;
    p->topo = NULL;

    return p;
}

void pilha_destruir(Pilha **endereco)
{
    Pilha *p = *endereco;

    No *aux = p->topo;
    No *aux2 = NULL;
    while (aux != NULL)
    {
        aux2 = aux->prox;
        free(aux);
        aux = aux2;
    }
    free(p);
    *endereco = NULL;
}

bool pilha_empilhar(Pilha *p, TipoElemento elemento)
{
    No *new = (No *)malloc(sizeof(No));

    if (new == NULL)
        return false;

    new->dado = elemento;
    new->prox = p->topo;

    p->topo = new;
    p->qtdeElemento++;

    return true;
}

bool pilha_desempilhar(Pilha *p, TipoElemento *saida)
{
    No *old = p->topo;
    *saida = old->dado;
    p->topo = old->prox;
    free(old);
    p->qtdeElemento--;
}

void pilha_imprimir(Pilha *p)
{
    printf("[");
    No *aux = p->topo;
    while (aux != NULL)
    {
        printf("%d", aux->dado);
        if (aux->prox != NULL)
            printf(",");
        aux = aux->prox;
    }
    printf("]\n");
}

bool pilha_topo(Pilha *p, TipoElemento *saida)
{
    if (p->topo == NULL)
        return false;

    *saida = p->topo->dado;

    return true;
}

bool pilha_vazia(Pilha *p)
{
    if (p->qtdeElemento <= 0)
        return true;

    return false;
}

int pilha_tamanho(Pilha *p)
{
    return p->qtdeElemento;
}

Pilha *pilha_clone(Pilha *p)
{
    Pilha *clone = pilha_criar();
    No *aux = p->topo;
    while (aux != NULL)
    {
        pilha_empilhar(clone, aux->dado);
        aux = aux->prox;
    }
    pilha_inverter(clone);

    return clone;
}

void pilha_inverter(Pilha *p)
{
    Pilha *invertida = pilha_criar();
    No *aux = p->topo;
    while (aux != NULL)
    {
        pilha_empilhar(invertida, aux->dado);
        aux = aux->prox;
    }

    aux = p->topo;
    p->topo = invertida->topo;
    invertida->topo = aux;
    pilha_destruir(&invertida);
}

bool pilha_empilharTodos(Pilha *p, TipoElemento *vetor, int tamVetor)
{
    if (p == NULL)
        return false;

    for (int i = 0; i < tamVetor; i++)
    {
        if (!pilha_empilhar(p, vetor[i]))
            return false;
    }

    return true;
}

bool pilha_toString(Pilha* p, char* str)
{
    if (p == NULL)
        return false;

    str[0] = '\0';
    strcat(str, "[");
    No* aux = p->topo;
    char straux[50];
    while (aux != NULL)
    {
        sprintf(straux, "%d", aux->dado);
        strcat(str, straux);
        if (aux->prox != NULL)
            strcat(str, ",");
        aux = aux->prox;
    }
    strcat(str, "]");

    return true;
}