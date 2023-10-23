#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>

#define espaco 5

//--------------------------------------------------------------
//---------------------- STRUCTS -------------------------------
//--------------------------------------------------------------
//arvore binaria de busca
typedef struct no
{
    int dado;
    struct no* esq;
    struct no* dir;
} no;
//--------------------------------------------------------------
typedef struct no_fila
{
    int dado;
    struct no_fila* prox;
    struct no_fila* ant;
} no_fila;
//--------------------------------------------------------------
//---------------------- FUNÇÕES SOBRE A FILA ------------------
//--------------------------------------------------------------
void inserirFila(no_fila** fila, int valor)
{
    no_fila* novo = (no_fila*)malloc(sizeof(no_fila));
    novo->dado = valor;
    novo->prox = NULL;
    novo->ant = NULL;

    if (*fila == NULL)
    {
        *fila = novo;
    }
    else
    {
        no_fila* aux = *fila;
        while (aux->prox != NULL)
        {
            aux = aux->prox;
        }
        aux->prox = novo;
        novo->ant = aux;
    }
}
//----------------------------------------------------------------
void exibirFila(no_fila* fila)
{
    printf("\tFila: ");
    no_fila* atual = fila;
    while (atual != NULL)
    {
        printf("|%d| ", atual->dado);
        atual = atual->prox;
    }
    printf("\n");
}

//-----------------------------------------------------------------
void liberarFila(no_fila** fila)
{
    no_fila* atual = *fila;
    while (atual != NULL)
    {
        no_fila* proximo = atual->prox;
        free(atual);
        atual = proximo;
    }
    *fila = NULL;
}
//-----------------------------------------------------------------
void percorrerEmOrdem(no* raiz, int* vetor, int* indice)
{
    if (raiz != NULL)
    {
        percorrerEmOrdem(raiz->esq, vetor, indice);
        vetor[(*indice)++] = raiz->dado;
        percorrerEmOrdem(raiz->dir, vetor, indice);
    }
}

//-----------------------------------------------------------------
no_fila* removerOrdenarInserir(no* raiz)
{
    int vetor[20];
    int indice = 0;
    percorrerEmOrdem(raiz, vetor, &indice);

    // Ordenar o vetor
    int i, j, temp;
    for (i = 0; i < indice - 1; i++)
    {
        for (j = 0; j < indice - i - 1; j++)
        {
            if (vetor[j] > vetor[j + 1])
            {
                temp = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = temp;
            }
        }
    }

//-----------------------------------------------------------------------
    no_fila* fila = NULL;
    for (i = 0; i < indice; i++)
    {
        inserirFila(&fila, vetor[i]);
    }

    return fila;
}
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
//------------------------FUNÇÕES DA ARVORE-----------------------------
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------

no *inserir(no* raiz, int num)
{

    if(raiz == NULL)
    {

        no *novo = (no*)malloc(sizeof (no));
        novo->dado = num;
        novo->dir = NULL;
        novo->esq = NULL;
        raiz = novo;
    }
    else
    {
        if(num == raiz->dado)
        {
            printf("\n O numero ja foi inserido!");
            system("pause");
        }
        if(num > raiz->dado)
        {
            raiz->dir = inserir(raiz->dir, num);
        }
        if(num < raiz->dado)
        {
            raiz->esq = inserir(raiz->esq, num);
        }
    }
    return(raiz);
}
//-----------------------------------------------------------------------

void pre_ordem(no* raiz){

    if(raiz != NULL){
        printf("%d \n\t", raiz->dado);
        pre_ordem(raiz->esq);
        pre_ordem(raiz->dir);
    }else{
        printf("\n\t Arvore vazia!!!\n\t");
    }
}
//------------------------------------------------------------------------------
bool igual(no* a, no* b)
{
    if (a == NULL && b == NULL)
        return true;

    if (a == NULL || b == NULL)
        return false;

    return (a->dado == b->dado) && igual(a->esq, b->esq) && igual(a->dir, b->dir);
}
//--esq raiz dir-----------------------------------------------------------
void em_ordem(no* raiz)
{

    if(raiz != NULL)
    {
        em_ordem(raiz->esq);
        printf("%d \n", raiz->dado);
        em_ordem(raiz->dir);
    }else{
        printf("\n\t Arvore vazia!!!\n\t");
    }
}
//---------------------------------------------------------------------------
void pos_ordem(no* raiz)
{

    if(raiz != NULL)
    {
        pos_ordem(raiz->esq);
        pos_ordem(raiz->dir);
        printf("%d \n", raiz->dado);
    }else{
        printf("\n\t Arvore vazia!!!\n\t");
    }
}
//-----------------------------------------------------------------
void desenhar_raiz_horiz(no* raiz, int profundidade, char *mapa, int dir)
{

    int i, j;

    if(raiz == NULL)
        return;

    profundidade++;

    desenhar_raiz_horiz(raiz->dir, profundidade, mapa, 1);

    mapa[profundidade-2] = 0;

    if(dir)
        mapa[profundidade-2] = 1;

    if(raiz->esq)
        mapa[profundidade-1] = 1;

    printf("\n");

    for(i=0; i<profundidade-1; i++)
    {
        if(i == profundidade-2)
            printf("+");
        else if(mapa[i])
            printf("|");
        else
            printf(" ");

        for(j=1; j<espaco; j++)
            if(i < profundidade-2)
                printf(" ");
            else
                printf("-");
    }
    printf("%d\n", raiz->dado);

    for(i=0; i<profundidade; i++)
    {
        if(mapa[i])
            printf("|");
        else
            printf(" ");
        for(j=1; j<espaco; j++)
            printf(" ");
    }

    desenhar_raiz_horiz(raiz->esq, profundidade, mapa, 0);
}
//-----------------------------------------------------------------

void desenhar(no* raiz)
{
    char mapa[255] = {};
    desenhar_raiz_horiz(raiz, 0, mapa, 0);
}

//------------------------------------------------------------------

no* excluir(no* raiz, int num)
{

    if(raiz == NULL)
    {
        return NULL;
    }
    else if(raiz->dado > num)
    {
        raiz->esq = excluir(raiz->esq, num);//busca subarvore a esq
    }
    else if(raiz->dado < num)
    {
        raiz->dir = excluir(raiz->dir, num);
    }
    else  //achou o dado ---- dado == raiz
    {

        //elementos sem filhos - no folha
        if(raiz->esq == NULL && raiz->dir == NULL)
        {
            free(raiz);
            raiz = NULL;
        }
        else if(raiz->esq == NULL)  //só tem filho a dir
        {
            no* aux = raiz;
            raiz = raiz->dir;
            aux->dir = NULL;
            free(aux);
        }
        else if(raiz->dir == NULL)  //só tem filho a esq
        {
            no* aux = raiz;
            raiz = raiz->esq;
            aux->esq = NULL;
            free(aux);
        }
        else  //possui dois filhos
        {

            no* aux = raiz->esq; //aponta aux para subarvore da esq

            while(aux->dir != NULL) //busca o maior dado da dir
            {
                aux = aux->dir;
            }

            raiz->dado = aux->dado; //troca as informacoes
            aux->dado = num;
            raiz->esq = excluir(raiz->esq, num);
        }
    }

    return raiz;
}
//----------------------------------------------------------------

void veridiff(no* raiz, int valor, int *contador) {
    if (raiz != NULL) {
        if (raiz->dado < valor) {
            (*contador)++;
        }
        veridiff(raiz->esq, valor, contador);
        veridiff(raiz->dir, valor, contador);
    }
}

//----------------------------------------------------------------

void menu()
{
    no* raizA = (no*)malloc(sizeof(no));
    no* raizB = (no*)malloc(sizeof(no));
    no* raiz = (no*)malloc(sizeof(no));
    raiz = NULL;
    raizA = NULL;
    raizB = NULL;

    int opc = 0;
    char opc1 = ' ';



    do
    {
        system("cls");

        printf("\n\t ------ARVORE-------\n\t -------------------");
        desenhar(raiz);

        printf("\n\t [1] - Inserir Arvore");
        printf("\n\t [2] - Remover Arvore");
        printf("\n\t [3] - Mostrar Arvore pre_order");
        printf("\n\t [4] - Mostrar Arvore in_order");
        printf("\n\t [5] - Mostrar Arvore pos_order");
        printf("\n\t [6] - Buscar Numeros Impares");
        printf("\n\t [7] - Verificar se duas arvores sao iguais");
        printf("\n\t [8] - arvore para vetor dinamico, ordenacao e fila");

        printf("\n\t [0] - SAIR...");


        do
        {
            printf("\n\t Informe a opcao...>>  ");
            scanf("%d", &opc);
            if(opc<0 || opc>9)
                printf("\n\n\t OPCAO INVALIDA...");
        }
        while(opc<0 || opc>9);


        switch(opc){

            case 1:{

                int x;
                printf("\n\t Informe o dado...>> ");
                scanf("%d", &x);

                raiz = inserir(raiz, x);

                break;

            }

            case 2:{

                int x;
                printf("\n\t Informe o dado...>> ");
                scanf("%d", &x);

                raiz = excluir(raiz, x);

                if(!raiz)
                    printf("\n\t IMPOSSIVEL REMOVER... ARVORE VAZIA!!!\n\t");

                system("pause");

                break;

            }

            case 3:{

                printf("\n\t");

                pre_ordem(raiz);

                system("pause");

                break;
            }

            case 4:{

                printf("\n\t");

                em_ordem(raiz);

                system("pause");

                break;
            }

            case 5:{

                printf("\n\t");

                pos_ordem(raiz);

                system("pause");

                break;
            }

            case 6:{
                int valor;
                printf("\n\t Verificar numeros menores:\n\t");
                printf("\tDigite o numero que voce deseja saber se existe algum menor: ");
                fflush(stdin);
                scanf("%d", &valor);

                int contador = 0;
                veridiff(raiz, valor, &contador);

                printf("\n\t Quantidade de elementos menores que %d: %d\n\n", valor, contador);

                system("pause");
                break;
            }
            case 7:
            {
                do{
                    system("cls");
                    printf("Arvore A");

                    desenhar(raizA);

                    printf("\n\nArvore B");

                    desenhar(raizB);

                    printf("\n\nInforme qual Arvore voce deseja inserir 'A' ou 'B', digite 'Z' para verificar se as arvores sao iguais, ou 'X' para remover as arvores e voltar ao menu... : ");
                    fflush(stdin);
                    scanf("%c", &opc1);

                    if(opc1 == 'a' || opc1 == 'A')
                    {
                        int x;
                        printf("\n\t Informe o dado...>> ");
                        scanf("%d", &x);
                        raizA = inserir(raizA, x);
                    }
                    else if(opc1 == 'b' || opc1 == 'B')
                    {
                        int x;
                        printf("\n\t Informe o dado para inserir na arvore B...>> ");
                        scanf("%d", &x);
                        raizB = inserir(raizB, x);
                    }
                    else if(opc1 == 'z' || opc1 == 'Z')
                    {
                        bool saoIguais = igual(raizA, raizB);
                        if(saoIguais)
                            printf("\n\t As arvores A e B sao iguais.\n");
                        else
                            printf("\n\t As arvores A e B sao diferentes.\n");
                            printf("\n\n\tPressione qualquer tecla para continuar");
                            getch();
                    }
                    else if(opc1 == 'x')
                    {
                        opc1 = 'X';
                    }
                }while(opc1 != 'X');

                break;
            }

            case 8:
            {
                no_fila* filaOrdenada = removerOrdenarInserir(raiz);
                printf("\n\tItens removidos da arvore e inseridos na fila ordenada.\n");
                exibirFila(filaOrdenada);
                liberarFila(&filaOrdenada);
                printf("\n\tPressione qualquer tecla para continuar...");
                getch();
                break;
            }
        }

    }while(opc != 0);

}
//--------------------------------------------------------------
//--------------------- CODIGO PRINCIPAL -----------------------
//--------------------------------------------------------------
int main()
{
    menu();

    printf("\n\n\n\ -------------- FIM --------------");
}
