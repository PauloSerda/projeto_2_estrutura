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
    data data;
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

int idexiste(noarv* no, int id)
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
    int cont = 0;
    do
    {
        id = 1000 + rand() %9000;
        cont ++;
        if(cont > 9000)
        {
            printf("\n\tSistema cheio, nao foi possivel cadastrar a venda");
            exit(1);
        }
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

void lerstring(char str[50])
{
    scanf(" %49[^\n]", str);
}

int buscarIdVendPorNome_no(noarv *no, char nomevend[50], char out_idv[5])
{
    if (no == NULL)
    {
        return 0;
    }
    if (buscarIdVendPorNome_no(no->esq, nomevend, out_idv))
    {
        return 1;
    }
    if (strcmp(no->vendas.nomevendedor, nomevend) == 0)
    {
        strcpy(out_idv, no->vendas.idvend);
        return 1;
    }
    return buscarIdVendPorNome_no(no->dir, nomevend, out_idv);
}

int buscarIdVendPorNome(arv *arvore, char nomevend[50], char out_idv[5])
{
    if (arvore == NULL || arvore->raiz == NULL)
    {
        return 0;
    }
    return buscarIdVendPorNome_no(arvore->raiz, nomevend, out_idv);
}

void gerarIdvendedor(arv *recebida, char nomevend[50], char idv[5])
{
    if (buscarIdVendPorNome(recebida, nomevend, idv))
    {
        return;
    }
    do
    {
        int numgerado = rand() % 900 + 100;

        idv[0] = 'v';
        itoa(numgerado, &idv[1], 10);

    } while (idvendexistearv(recebida, idv));
}


noarv* auxinsere(arv *arvore, noarv *no)
{
    int flag = 0;
    noarv *pai;
    noarv *novo;
    novo = (noarv*)malloc(sizeof(noarv));
    novo->vendas.id = gerarIdUnico(arvore);
    printf("\n\tdigite o nome do cliente:\t");
    lerstring(novo->vendas.nomecliente);
    printf("\n\tdigite o nome do vendedor:\t");
    lerstring(novo->vendas.nomevendedor);
    gerarIdvendedor(arvore, novo->vendas.nomevendedor, novo->vendas.idvend);
    printf("\n\tdigite o valor:\t");
    scanf("%f",&novo -> vendas.valor);
    printf("\n\tdigite a data da venda (DD MM AAAA:)");
    scanf("%d %d %d",
          &novo -> vendas.data.dia,
          &novo -> vendas.data.mes,
          &novo -> vendas.data.ano);
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
            if(pai -> vendas.valor < novo -> vendas.valor)
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
            else if(pai -> vendas.valor > novo -> vendas.valor)
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


void insere(arv *arvore)
{
    arvore -> raiz = auxinsere(arvore,arvore -> raiz);
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

noarv* removerno(noarv *no, int id, int *removido)
{
    if (no == NULL)
    {
                return NULL;
    }
    no -> esq = removerno(no -> esq, id, removido);
    no -> dir = removerno(no -> dir, id, removido);
    if (no->vendas.id == id)
    {
        *removido = 1;

        if (no -> esq == NULL && no -> dir == NULL)
        {
            free(no);
            return NULL;
        }

        if (no -> esq == NULL)
        {
            noarv *aux = no -> dir;
            free(no);
            return aux;
        }

        if (no -> dir == NULL)
        {
            noarv *aux = no -> esq;
            free(no);
            return aux;
        }

        noarv *aux = no -> esq;
        while (aux -> dir != NULL)
        {
            aux = aux -> dir;
        }
        no -> vendas = aux -> vendas;
        no -> esq = removerno(no -> esq, aux -> vendas.id, removido);

        return no;
    }

    return no;
}

void removervenda(arv *arvore)
{
    if (arvore == NULL || arvore -> raiz == NULL)
    {
        printf("\n\tArvore vazia\n");
        return;
    }
    int id;
    printf("\n\tDigite o ID da venda que sera removida:\t");
    scanf("%d",&id);
    int removido = 0;
    arvore -> raiz = removerno(arvore -> raiz, id, &removido);
    if (!removido)
    {
        printf("\n\tVenda com ID %d nao encontrada.\n", id);
    }
    else
    {
        printf("\n\tVenda com ID %d removida com sucesso.\n", id);
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
            printf("\nID  | Vendedor             | Matricula | Cliente                | Data         | Valor(R$)\n");
            printf("---------------------------------------------------------------------------------------------------\n");
        }

         printf("%-3d | %-20s | %-9s | %-20s | %02d/%02d/%04d | %.2f\n",
               no->vendas.id,
               no->vendas.nomevendedor,
               no->vendas.idvend,
               no->vendas.nomecliente,
               no->vendas.data.dia,
               no->vendas.data.mes,
               no->vendas.data.ano,
               no->vendas.valor);

        (*contador)++;
    }

    buscamatricula_no(no->dir, idm, contador);
}


void buscamatricula(arv* arvore, char idm[5])
{
    if (arvore == NULL || arvore->raiz == NULL)
    {
        printf("\nArvore vazia\n");
        return;
    }

    int contador = 0;
    buscamatricula_no(arvore->raiz, idm, &contador);

    if (contador == 0)
    {
        printf("\nNenhuma venda encontrada para a matricula %s.\n", idm);
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
            printf("\nID  | Vendedor             | Matricula | Cliente                | Data         | Valor(R$)\n");
            printf("---------------------------------------------------------------------------------------------------\n");
        }

        printf("%-3d | %-20s | %-9s | %-20s | %02d/%02d/%04d | %.2f\n",
               no->vendas.id,
               no->vendas.nomevendedor,
               no->vendas.idvend,
               no->vendas.nomecliente,
               no->vendas.data.dia,
               no->vendas.data.mes,
               no->vendas.data.ano,
               no->vendas.valor);

        (*contador)++;
    }
    buscanome_no(no -> dir, nomevend, contador);
}

void buscanome(arv* arvore, char nomevend[50])
{
    if(arvore == NULL || arvore -> raiz == NULL)
    {
        printf("\nArvore vazia\n");
        return;
    }
    int contador = 0;
    buscanome_no(arvore -> raiz, nomevend, &contador);
    if (contador == 0)
    {
        printf("\nNenhuma venda encontrada para o vendedor %s.\n", nomevend);
    }

}

void busca(arv* recebida)
{
    int num;
    printf("\n\tEscolha como buscar sua venda:\n\t1 - Matricula\n\t2 - Nome do vendedor\n\t");
    scanf("%d",&num);
    switch(num){
        case 1:
        {
            char matricula[5];
            printf("\n\tDigite o numero da matricula do vendedor:\t");
            scanf("%4s",matricula);
            buscamatricula(recebida, matricula);
            break;
        }
        case 2:
        {
            char nomevend[50];
            printf("\nDigite o nome do vendedor:\t");
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
        printf("\nArvore vazia\n");
        return;
    }

    printf("\n\t====== ESTATISTICAS ======");
    printf("\n\n\tTotal de vendas:\t%d",contarvendas(arvore -> raiz));
    printf("\n\tFaturamento total:\t%.2f", somarfaturamento(arvore -> raiz));

}

void listarporvalor_no(noarv *no, float valor_ref, int op, int *buscavenda)
{
    if (no == NULL)
    {
        return;
    }
    listarporvalor_no(no->esq, valor_ref, op, buscavenda);
    if ((op == 1 && no -> vendas.valor > valor_ref) || (op == 2 && no->vendas.valor < valor_ref))
    {
        if (*buscavenda == 0)
        {
            printf("\nID  | Vendedor             | Matrícula | Cliente                | Data         | Valor(R$)\n");
            printf("---------------------------------------------------------------------------------------------------\n");
            *buscavenda = 1;
        }
        printf("%-3d | %-20s | %-9s | %-20s | %02d/%02d/%04d | %.2f\n",
               no->vendas.id,
               no->vendas.nomevendedor,
               no->vendas.idvend,
               no->vendas.nomecliente,
               no->vendas.data.dia,
               no->vendas.data.mes,
               no->vendas.data.ano,
               no->vendas.valor);
    }
    listarporvalor_no(no->dir, valor_ref, op, buscavenda);
}

void listarporvalor(arv *arvore)
{
    if (arvore == NULL || arvore->raiz == NULL)
    {
        printf("\nArvore vazia\n");
        return;
    }

    float valor;
    int op;
    int buscavenda = 0;

    printf("\n\tDigite o valor de referencia: ");
    scanf("%f", &valor);

    printf("\n\t1 - Listar vendas acima desse valor");
    printf("\n\t2 - Listar vendas abaixo desse valor\n\t");
    scanf("%d", &op);

    if(op != 1 && op != 2)
    {
        printf("\n\tOpcao invalida.\n");
        return;
    }

    listarporvalor_no(arvore->raiz, valor, op, &buscavenda);

    if (buscavenda == 0)
    {
        if (op == 1)
            printf("\n\tNenhuma venda com valor acima de %.2f.\n", valor);
        else
            printf("\n\tNenhuma venda com valor abaixo de %.2f.\n", valor);
    }
}

int contar_nos(noarv *no)
{
    if (no == NULL)
        return 0;

    return 1 + contar_nos(no -> esq) + contar_nos(no -> dir);
}

void preencher_vetor(noarv *no, vend vet[], int *i)
{
    if (no == NULL)
    {
        return;
    }
    preencher_vetor(no -> esq, vet, i);
    vet[*i] = no -> vendas;
    (*i)++;
    preencher_vetor(no -> dir, vet, i);
}

void ordenar_por_id_crescente(vend vet[], int n)
{
    int i, j;
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - 1 - i; j++)
        {
            if (vet[j].id > vet[j+1].id)
            {
                vend tmp = vet[j];
                vet[j] = vet[j+1];
                vet[j+1] = tmp;
            }
        }
    }
}

void listartodas(arv *arvore)
{
    if (arvore == NULL || arvore->raiz == NULL)
    {
        printf("\n\tArvore vazia\n");
        {
            return;
        }
    }
    int op;
    printf("\n\tEscolha a ordem que sera listada\n");
    printf("\n\t1 - Crescente por ID\n");
    printf("\n\t2 - Decrescente por ID\n\t");
    scanf("%d", &op);
    if (op != 1 && op != 2)
    {
        printf("\n\tOpcao invalida.\n");
        return;
    }
    int total = contar_nos(arvore->raiz);
    if (total <= 0)
    {
        printf("\n\tNenhuma venda cadastrada.\n");
        return;
    }
    vend *vet = (vend*) malloc(total * sizeof(vend));
    if (vet == NULL)
    {
        printf("\n\tArvore vazia\n");
        return;
    }
    int i = 0;
    preencher_vetor(arvore -> raiz, vet, &i);
    ordenar_por_id_crescente(vet, total);
    printf("\nID  | Vendedor             | Matrícula | Cliente                | Data         | Valor(R$)\n");
    printf("---------------------------------------------------------------------------------------------------\n");
    if (op == 1)
    {
        for (i = 0; i < total; i++)
        {
            printf("%-3d | %-20s | %-9s | %-20s | %02d/%02d/%04d | %.2f\n",
                   vet[i].id,
                   vet[i].nomevendedor,
                   vet[i].idvend,
                   vet[i].nomecliente,
                   vet[i].data.dia,
                   vet[i].data.mes,
                   vet[i].data.ano,
                   vet[i].valor);
        }
    }
    else
    {
        for (i = total - 1; i >= 0; i--)
        {
            printf("%-3d | %-20s | %-9s | %-20s | %02d/%02d/%04d | %.2f\n",
                   vet[i].id,
                   vet[i].nomevendedor,
                   vet[i].idvend,
                   vet[i].nomecliente,
                   vet[i].data.dia,
                   vet[i].data.mes,
                   vet[i].data.ano,
                   vet[i].valor);
        }
    }
    free(vet);
}


void liberar_no(noarv *no)
{
    if(no == NULL)
    {
        return;
    }
    liberar_no(no -> esq);
    liberar_no(no -> dir);
    free(no);
}

void finalizar(arv *arvore)
{
    if(arvore == NULL)
    {
        return;
    }
    liberar_no(arvore -> raiz);
    free(arvore);
    printf("\n\tSistema finalizado com sucesso");
}




#endif
