#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "arvore.h"

void esperarenter()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
    getchar();
}

void limpartela()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}


int main()
{
    srand(time(NULL));
    arv *sistema = criararvore();
    int op;
    do{
        limpartela();
        printf("\n\tSistema de vendas, selecione a operacao:\n\t1 para inserir uma nova venda\n\t2 para listar todas as vendas\n\t3 para buscar as vendas de um determinado vendedor\n\t4 para listar as vendas acima ou abaixo de um valor definido\n\t5 para exibir estatisticas\n\t6 para remocao de uma venda\n\t7 para finalizar o sistema\n\t ");
        scanf("%d",&op);
        switch(op)
        {
            case 1:
                insere(sistema);
                printf("\n\tinsercao realizada com sucesso\n\t");
                break;

            case 2:
                listartodas(sistema);
                break;

            case 3:
                busca(sistema);
                break;

            case 4:
                listarporvalor(sistema);
                break;

            case 5:
                exibirestatisticas(sistema);
                break;

            case 6:
                removervenda(sistema);
                break;

            case 7:
                finalizar(sistema);
                break;

            default:
                printf("\n\tOperação inválida");
                break;
        }
        printf("\n\n\tDigite enter para continuar");
        esperarenter();


    }while(op != 7);

}

