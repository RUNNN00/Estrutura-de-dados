#include "fila.h"
#include <string.h>

#define TAM_INICIAL 8
/**************************************
 * DADOS
 **************************************/
struct fila
{
    TipoElemento *vetor;
    int tamVetor;
    int inicio;
    int fim;
    int qtdeElementos;
};

/**************************************
 * FUNÇÕES AUXILIARES
 **************************************/
bool filaValida(Fila *f)
{
    if (f == NULL)
        return false;
    if (f->vetor == NULL)
        return false;

    return true;
}

bool realoca(Fila *f, int tamNovo)
{
    if (!filaValida(f))
        return false;

    TipoElemento *vetorNovo = (int *)calloc(tamNovo, sizeof(int));

    if (vetorNovo == NULL)
        return false;

    int index = f->inicio;
    for (int i = 0; i < f->qtdeElementos; i++)
    {
        vetorNovo[i] = f->vetor[index];
        index = (index + 1) % f->tamVetor;
    }
    free(f->vetor);
    f->vetor = vetorNovo;
    f->inicio = 0;
    f->fim = f->qtdeElementos;
    f->tamVetor = tamNovo;
    return true;
}

/**************************************
 * IMPLEMENTAÇÃO
 **************************************/
Fila *fila_criar()
{
    Fila *f = (Fila *)malloc(sizeof(Fila));
    f->vetor = (int *)calloc(TAM_INICIAL, sizeof(int));
    f->inicio = f->vetor[0];
    f->fim = f->vetor[0];
    f->qtdeElementos = 0;
    f->tamVetor = TAM_INICIAL;
}

void fila_destruir(Fila **enderecoFila)
{
    if (!filaValida(*enderecoFila))
        return;

    Fila *f = *enderecoFila;
    free(f->vetor);
    free(f);
    *enderecoFila = NULL;
}

bool fila_inserir(Fila *f, TipoElemento elemento)
{
    if (!filaValida(f))
        return false;

    if (f->qtdeElementos >= f->tamVetor - 1)
    {
        int tam = f->tamVetor + TAM_INICIAL;
        if (!realoca(f, tam))
            return false;
    }

    f->vetor[f->fim] = elemento;
    f->fim = (f->fim + 1) % f->tamVetor;
    f->qtdeElementos++;

    return true;
}

bool fila_remover(Fila *f, TipoElemento *saida) // estratégia do scanf
{
    if (!filaValida(f))
        return false;
    if (fila_vazia(f))
        return false;

    *saida = f->vetor[f->inicio];
    f->inicio = (f->inicio + 1) % f->tamVetor;
    f->qtdeElementos--;

    if (f->tamVetor - f->qtdeElementos > TAM_INICIAL)
    {
        int tam = f->tamVetor - TAM_INICIAL;
        if (!realoca(f, tam))
            return false;
    }

    return true;
}

bool fila_primeiro(Fila *f, TipoElemento *saida) // estratégia do scanf
{
    if (!filaValida(f))
        return false;
    if (fila_vazia(f))
        return false;

    *saida = f->vetor[f->inicio];
    return true;
}

bool fila_vazia(Fila *f)
{
    return f->qtdeElementos <= 0;
}

int fila_tamanho(Fila *f)
{
    return f->tamVetor;
}

void fila_imprimir(Fila *f)
{
    if (!filaValida(f))
        return;

    printf("vetor: ");
    printf("[");
    int index = f->inicio;
    for (int i = 0; i < f->qtdeElementos; i++)
    {
        if (index >= f->tamVetor)
            index = 0;

        printf("%d", f->vetor[index]);
        if (i < f->qtdeElementos - 1)
            printf(",");

        index++;
    }
    printf("]\n");
}

Fila *fila_clone(Fila *f)
{
    if (!filaValida(f))
        return NULL;

    Fila *clone = fila_criar();

    int index = f->inicio;
    for (int i = 0; i < f->qtdeElementos; i++)
    {
        if (index >= f->tamVetor)
            index = 0;

        fila_inserir(clone, f->vetor[index]);
        index++;
    }

    return clone;
}

bool fila_toString(Fila *f, char *str)
{
    if (!filaValida(f))
        return false;
    if (fila_vazia(f))
        return false;

    str[0] = '\0';
    strcat(str, "[");
    char strAux[50];
    int index = f->inicio;
    for (int i = 0; i < f->qtdeElementos; i++)
    {
        if (index >= f->tamVetor)
            index = 0;

        sprintf(strAux, "%d", f->vetor[index]);
        strcat(str, strAux);
        index++;

        if (i < f->qtdeElementos - 1)
            strcat(str, ",");
    }
    strcat(str, "]");

    return true;
}

bool fila_inserirTodos(Fila *f, TipoElemento *vetor, int tamVetor)
{
    if (!filaValida(f))
        return false;
    if (tamVetor <= 0)
        return false;

    for (int i = 0; i < tamVetor; i++)
        fila_inserir(f, vetor[i]);

    return true;
}