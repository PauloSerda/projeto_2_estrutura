#ifndef ARVORE_H_INCLUDED
#define ARVORE_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct data
{
    int dia;
    int mes;
    int ano;
}data;

typedef struct v
 {
    int id;
    char nomecliente[50];
    char nomevendedor[50];
    char idvend[5];
    data transacao;
    float valor;
}vend;

 typedef struct noarvore
{
    vend vendas;
    struct noarvore *esq;
    struct noarvore *dir;
}noarv;


typedef struct arvore
{
    noarv *raiz;
}arv;

int gerarIdCliente()
{
    return 1000 + rand() % 9000;
}

void gerarIdvendedor(char idv[5])
{
    int numgerado = rand() % 900 + 100;
    char aux[4];
    idv[0] = 'v';
    itoa(numgerado, aux, 4);
    strcat(idv,aux);
}

void lerstring(char str[50])
{
    scanf(" %49[^\n]", str);
}



noarv* auxinsere(noarv *no, float valor)
{
    int flag = 0;
    noarv *pai;
    noarv *novo;
    novo = (noarv*)malloc(sizeof(noarv));
    novo->vendas.id = gerarIdCliente();
    printf("\ndigite o nome do cliente:\t");
    lerstring(novo->vendas.nomecliente);
    printf("\ndigite o nome do vendedor:\t");
    lerstring(novo->vendas.nomevendedor);
    gerarIdVendedor(novo->vendas.idvend);
    printf("\ndigite o valor:\t");
    scanf("%f",&valor);
    novo -> vendas.valor = valor;
    novo -> esq = NULL;
    novo -> dir = NULL;
    if(no == NULL)
    {
        return novo;
    }
    else
    {
        pai = no;
        while(flag == 0)
        {
            if(pai -> vendas.valor < valor)
            {
                if(pai -> dir == NULL)
                {
                    pai -> dir = novo;
                    flag = 1;
                }
                else
                {
                    pai = pai -> dir;
                }
            }
            else if(pai -> vendas.valor > valor)
            {
                if(pai -> esq == NULL)
                {
                    pai -> esq = novo;
                    flag = 1;
                }
                else
                {
                    pai = pai -> esq;
                }
            }
        }
    }
    return no;
}


void insere(arv *arvore, int num)
{
    arvore -> raiz = auxinsere(arvore -> raiz,num);
}

arv* criararvore()
{
    arv *aux;
    noarv *aux;
    aux = (arv*)malloc(sizeof(arv));
    aux -> raiz = NULL;
    return aux;
}
int arvorevazia(arv *base)
{
    if(base -> raiz == NULL)
    {
        return 1;
    }
    return 0;
}
arv* remover_venda(arv *recebida, int num)
{
    if (recebida == NULL || recebida -> raiz == NULL)
    {
        return recebida;
    }

    recebida -> raiz = remover_aux(recebida -> raiz, num);
    return recebida;
}

noarv* remover_aux(noarv *pai, int num)
{
    if (pai == NULL)
    {
        printf("\n\nvenda nao encontrada");
        return NULL;
    }

    if (num > pai -> vendas.id)
    {
        pai -> dir = remover_aux(pai -> dir, num);
    }
    else if (num < pai -> vendas.id)
    {
        pai->esq = remover_aux(pai -> esq, num);
    }
    else{
        if (pai -> dir == NULL && pai -> esq == NULL)
    {
        free(pai);
        pai = NULL;
    }

    else if (pai -> esq == NULL)
    {
        noarv *aux = pai;
        pai = pai -> dir;
        free(aux);
    }

    else if (pai -> dir == NULL)
    {
        noarv *aux = pai;
        pai = pai -> esq;
        free(aux);
    }

    else
    {
        noarv *aux = pai -> esq;

        while (aux -> dir != NULL)
        {
            aux = aux -> dir;
        }
            pai -> vendas = aux -> vendas;
            pai->esq = remover_aux(pai->esq, aux->vendas.id);
        }
    }

    return pai;
}

void busca(arv* recebida)
{
    int num;
    printf("\nescolha como buscar sua venda:\n1 - matricula\n2 - nome do vendedor\t");
    scanf("%d",&num);
    switch(num){
        case 1:
            buscamatricula(recebida);
            break;
        case 2:
            buscanome(recebida);
            break;
        default:
            return NULL;
    }
}
void buscamatricula(arv* pai)
{
    char matricula[4];
    printf("\ndigite o numero da matricula do vendedor:\t");
    scanf("%c",matricula);

    if(pai->dir!=NULL)
    {
        if(matricula != pai -> vendas.idvend)
        {
            buscamatricula(pai->dir);
            else
            {

            }

        }
        if(pai->esq!=NULL)
        {
            if()
            buscamatricula(pai->esq);
        }
}
















#endif
