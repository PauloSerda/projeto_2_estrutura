#ifndef ARVORE_H_INCLUDED
#define ARVORE_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

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

int idexistearv(arv *recebida, int id)
{
    if (recebida == NULL || recebida->raiz == NULL)
    {
        return 0;
    }

    return idexiste(recebida->raiz, id);
}

int idexiste(int id, noarv* no)
{
    if(no == NULL)
    {
        return 0;
    }
    if(no -> vendas.id == id)
    {
        return 1;
    }
    if(idexiste(no -> esq, id))
    {
        return 1;
    }
    if(idexiste(no -> dir, id))
    {
        return 1;
    }
    return 0;
}

int gerarIdUnico(arv *recebida)
{
    int id;
    do
    {
        id = 1000 + rand() %9000;
    }while(idexistearv(recebida, id));
    return id;
}

int idvendexistearv(arv* recebida, char idvend[5])
{
    if(recebida == NULL || recebida -> raiz == NULL)
    {
        return 0;
    }
    return idvendexiste(recebida -> raiz, idvend);
}

int idvendexiste(noarv *no, char idvend[5])
{
    if(no == NULL)
    {
        return 0;
    }
    if(strcmp(no -> vendas.idvend, idvend) == 0)
    {
        return 1;
    }
    if(idvendexiste(no -> esq, idvend))
    {
        return 1;
    }
    if(idvendexiste(no -> dir, idvend))
    {
        return 1;
    }
    return 0;
}

void gerarIdvendedor(arv *recebida, char idv[5])
{
    do
    {
        int numgerado = rand() % 900 + 100;
        char aux[4];
        idv[0] = 'v';
        itoa(numgerado, aux, 4);
        strcat(idv,aux);
    }while (idvendexistearv(recebida,idv));
}

void lerstring(char str[50])
{
    scanf(" %49[^\n]", str);
}



noarv* auxinsere(arv *arvore, noarv *no, float valor)
{
    int flag = 0;
    noarv *pai;
    noarv *novo;
    novo = (noarv*)malloc(sizeof(noarv));
    novo->vendas.id = gerarIdUnico(arvore);
    printf("\ndigite o nome do cliente:\t");
    lerstring(novo->vendas.nomecliente);
    printf("\ndigite o nome do vendedor:\t");
    lerstring(novo->vendas.nomevendedor);
    gerarIdvendedor(arvore, novo->vendas.idvend);
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
    arvore -> raiz = auxinsere(arvore,arvore -> raiz,num);
}

arv* criararvore()
{
    arv *aux;
    aux = (arv*)malloc(sizeof(arv));
    aux -> raiz = NULL;
    return aux;
}
int arvorevazia(arv *base)
{
    if(base == NULL || base -> raiz == NULL)
    {
        return 1;
    }
    return 0;
}

noarv* removerNo(noarv *no, int id, int *removido)
{
    if (no == NULL || *removido == 1)
    {
        return no;
    }
    no->esq = removerNo(no->esq, id, removido);
    if (*removido == 1)
    {
        return no;
    }
    no->dir = removerNo(no->dir, id, removido);
    if (*removido == 1)
    {
        return no;
    }
    if (no->vendas.id == id)
    {
        *removido = 1;
        if (no->esq == NULL && no->dir == NULL)
        {
            free(no);
            return NULL;
        }
        if (no->esq == NULL)
        {
            noarv *aux = no->dir;
            free(no);
            return aux;
        }
        if (no->dir == NULL)
        {
            noarv *aux = no->esq;
            free(no);
            return aux;
        }
        noarv *aux = no->esq;
        while (aux->dir != NULL)
        {
            aux = aux->dir;
        }
        no->vendas = aux->vendas;
        no->esq = removerNo(no->esq, aux->vendas.id, removido);

        return no;
    }
    return no;
}


void remover_venda(arv *arvore, int id)
{
    if (arvore == NULL || arvore->raiz == NULL)
    {
        printf("\narvore vazia\n");
        return;
    }
    int removido = 0;
    arvore->raiz = removerNo(arvore->raiz, id, &removido);
    if (!removido)
    {
        printf("\nvenda com ID %d nao encontrada.\n", id);
    }
    else
    {
        printf("\nvenda com ID %d removida com sucesso.\n", id);
    }
}


void buscamatricula_no(noarv *no, char idm[5], int *contador)
{
    if (no == NULL)
        return;

    buscamatricula_no(no->esq, idm, contador);

    if (strcmp(no->vendas.idvend, idm) == 0)
    {
        if (*contador == 0)
        {
            printf("\nID  | Vendedor             | Matrícula | Cliente                | Data         | Valor(R$)\n");
            printf("---------------------------------------------------------------------------------------------------\n");
        }

         printf("%-3d | %-20s | %-9s | %-20s | %02d/%02d/%04d | %.2f\n",
               no->vendas.id,
               no->vendas.nomevendedor,
               no->vendas.idvend,
               no->vendas.nomecliente,
               no->vendas.transacao.dia,
               no->vendas.transacao.mes,
               no->vendas.transacao.ano,
               no->vendas.valor);

        (*contador)++;
    }

    buscamatricula_no(no->dir, idm, contador);
}


void buscamatricula(arv* arvore, char idm[5])
{
    if (arvore == NULL || arvore->raiz == NULL)
    {
        printf("\narvore vazia\n");
        return;
    }

    int contador = 0;
    buscamatricula_no(arvore->raiz, idm, &contador);

    if (contador == 0)
    {
        printf("\nnenhuma venda encontrada para a matrícula %s.\n", idm);
    }
}
void buscanome_no(noarv *no, char nomevend[50], int *contador)
{
    if (no == NULL)
    {
        return;
    }
    buscanome_no(no -> esq, nomevend, contador);
    if (strcmp(no -> vendas.nomevendedor, nomevend) == 0)
    {
         if (*contador == 0)
        {
            printf("\nID  | Vendedor             | Matrícula | Cliente                | Data         | Valor(R$)\n");
            printf("---------------------------------------------------------------------------------------------------\n");
        }

        printf("%-3d | %-20s | %-9s | %-20s | %02d/%02d/%04d | %.2f\n",
               no->vendas.id,
               no->vendas.nomevendedor,
               no->vendas.idvend,
               no->vendas.nomecliente,
               no->vendas.transacao.dia,
               no->vendas.transacao.mes,
               no->vendas.transacao.ano,
               no->vendas.valor);

        (*contador)++;
    }
    buscanome_no(no -> dir, nomevend, contador);
}

void buscanome(arv* arvore, char nomevend[50])
{
    if(arvore == NULL || arvore -> raiz == NULL)
    {
        printf("\narvore vazia\n");
        return;
    }
    int contador = 0;
    buscanome_no(arvore -> raiz, nomevend, &contador);
    if (contador == 0)
    {
        printf("\nnenhuma venda encontrada para o vendedor %s.\n", nomevend);
    }

}

void busca(arv* recebida)
{
    int num;
    printf("\nescolha como buscar sua venda:\n1 - matricula\n2 - nome do vendedor\t");
    scanf("%d",&num);
    switch(num){
        case 1:
        {
            char matricula[5];
            printf("\ndigite o numero da matricula do vendedor:\t");
            scanf("%4s",matricula);
            buscamatricula(recebida, matricula);
            break;
        }
        case 2:
        {
            char nomevend[50];
            printf("\ndigite o nome do vendedor:\t");
            lerstring(nomevend);
            buscanome(recebida, nomevend);
            break;
        }
        default:
            return;
    }
}

int contarvendas(noarv *no)
{
    if (no == NULL)
    {
        return 0;
    }
    return 1 + contarvendas(no -> esq) + contarvendas(no -> dir);
}

float somarfaturamento(noarv *no)
{
    if (no == NULL)
    {
        return 0;
    }
    return no -> vendas.valor + somarfaturamento(no -> esq) + somarfaturamento(no -> dir);
}

void exibirestatisticas(arv *arvore)
{
    if(arvore == NULL || arvore -> raiz == NULL)
    {
        printf("\narvore vazia\n");
        return;
    }

    printf("\n====== ESTATÍSTICAS ======\n");
    printf("Total de vendas:\t%d\n",contarvendas(arvore -> raiz));
    printf("Faturamento total:\t%.2f\n", somarfaturamento(arvore -> raiz));

}




#endif
