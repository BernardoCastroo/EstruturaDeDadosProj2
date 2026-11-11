#ifndef BIBLIOTECAARVORE_H_INCLUDED
#define BIBLIOTECAARVORE_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

typedef struct Incidentes
{
    int N_U_Id;
    int id_equip;
    int gravidade;
} Inci;
typedef struct Equipamento
{
    int C_U_Id;
    char nome[10];

}Equip;
typedef struct NoArvore
{
    Inci info;
    struct NoArvore *esq;
    struct NoArvore *dir;
}NoArv;

typedef struct Arvore
{
    NoArv *raiz;
}Arv;

Arv* criaArvore()
{
    Arv *arvore = (Arv*) malloc(sizeof(Arv));
    if (arvore != NULL) {
        arvore->raiz = NULL;
    }
    return arvore;
}

int ArvVazia(Arv* A) {
    if (A->raiz == NULL) {
        return 1;
    }
    return 0;
}

void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

NoArv* inserirIncidente(NoArv* raiz, Inci novoIncidente)
{
    if (raiz == NULL) {
        NoArv* aux = (NoArv*) malloc(sizeof(NoArv));
        aux->info = novoIncidente;
        aux->esq = NULL;
        aux->dir = NULL;
        return aux;
    }
    if(novoIncidente.N_U_Id < raiz->info.N_U_Id)
    {
        raiz->esq = inserirIncidente(raiz->esq, novoIncidente);
    }
    if(novoIncidente.N_U_Id > raiz->info.N_U_Id)
    {
        raiz->dir=inserirIncidente(raiz->dir, novoIncidente);
    }
    if(novoIncidente.N_U_Id == raiz->info.N_U_Id)
    {
        printf("Erro!!! :( O Incidente com ID %d ja existe!\n", novoIncidente.N_U_Id);
    }

    return raiz;
}

void adicionarIncidente(Arv* arvore)
{
    system("cls");
    printf("\n\t==================================================\n");
    printf("\t               REGISTRAR INCIDENTE                \n");
    printf("\t==================================================\n");

    Inci novo;

    printf("\n\tDigite o ID do Incidente (2 digitos): ");
    scanf("%d", &novo.N_U_Id);

    printf("\tDigite o Codigo do Equipamento (4 digitos): ");
    scanf("%d", &novo.id_equip);

    printf("\tDigite a Gravidade (1-Baixa, 2-Media, 3-Alta): ");
    scanf("%d", &novo.gravidade);
    limpar_buffer();

    arvore->raiz=inserirIncidente(arvore->raiz, novo);

    printf("\n\tIncidente enviado para a arvore!\n");

    printf("\n\t\t---APERTE ENTER PARA CONTINUAR---\n");
}

NoArv* BuscaIncidente(NoArv* raiz,int Incidente)
{
    if(raiz!=NULL)
    {
        if(Incidente <= raiz->info.N_U_Id)
        {
            if(Incidente==raiz->info.N_U_Id)
            {
                return raiz;
            }
            return BuscaIncidente(raiz->esq, Incidente);
        }
        if(Incidente >= raiz->info.N_U_Id)
        {
            if(Incidente==raiz->info.N_U_Id)
            {
                return raiz;
            }
            return BuscaIncidente(raiz->dir, Incidente);
        }
    }
    return NULL;
}

void passa_Incidente(NoArv* raiz)
{
    int Incidente;
    if(raiz==NULL){
        printf("\t!!!Sem incidentes!!!\n");
        printf("\t\t\t---APERTE ENTER PARA CONTINUAR---\n");
        getchar();
    }
    else{
        printf("\tDigite o código do Incidente a ser consultado:");
        scanf("%d", &Incidente);

        limpar_buffer();

        NoArv* res=BuscaIncidente(raiz,Incidente);

        if (res!=NULL)
        {
            printf("\n\t--- Incidente Encontrado ---\n");
            printf("\tID do Incidente: %d\n", res->info.N_U_Id);
            printf("\tID do Equipamento associado: %d\n", res->info.id_equip);
            printf("\tNivel de Gravidade: %d\n", res->info.gravidade);
            printf("\t\t\t---APERTE ENTER PARA CONTINUAR---\n");
            getchar();

        }
        else{
            printf("\n\tIncidente não encontrado");
            printf("\t\t\t---APERTE ENTER PARA CONTINUAR---\n");
            getchar();
        }
    }
}

void ListaIncidentes(NoArv* raiz)
{
    if(raiz!=NULL)
    {
        ListaIncidentes(raiz->esq);

        printf("\t%-15d | %-16d | %-10d\n",
               raiz->info.N_U_Id, raiz->info.id_equip, raiz->info.gravidade);
        printf("\t--------------------------------------------------\n");

        ListaIncidentes(raiz->dir);
    }
}

NoArv* removerIncidente(NoArv* raiz,int remove_inci)
{
    if(raiz == NULL)
    {
        return NULL;
    }
    else
    {

        if(remove_inci == raiz->info.N_U_Id)
        {
            if(raiz->esq == NULL && raiz->dir==NULL)
            {
                free(raiz);
                return NULL;
            }
            if(raiz->esq == NULL && raiz->dir!=NULL)// ver com a luciaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
            {
                NoArv* aux = raiz->dir;
                free(raiz);
                raiz = aux;             // se poderia ser apenas return aux.
                return raiz;
            }
            if(raiz->esq != NULL && raiz->dir==NULL)// ver com a luciaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
            {
                NoArv* aux = raiz->esq;
                free(raiz);
                raiz = aux;
                return raiz;
            }

            NoArv* atual = raiz->esq;
            while (atual->dir != NULL)// maior da esqueda
            {
                atual = atual->dir;
            }

            raiz->info= atual->info;
            raiz->esq = removerIncidente(raiz->esq, atual->info.N_U_Id);

            return raiz;

        }
        if(remove_inci < raiz->info.N_U_Id)
        {
            raiz->esq = removerIncidente(raiz->esq, remove_inci);
            return raiz;
        }
        if(remove_inci > raiz->info.N_U_Id)
        {
            raiz->dir = removerIncidente(raiz->dir, remove_inci);
            return raiz;
        }

    }
}

void excluirInsidente(Arv* arvore)
{
    system("cls");
    int remover;
    if(ArvVazia(arvore) || arvore->raiz == NULL)
    {
        printf("\t!!!Sem incidentes!!!\n");
        printf("\t\t\t---APERTE ENTER PARA CONTINUAR---\n");
        getchar();
    }
    else{
        printf("\tDigite o código do Incidente a ser removido:");
        scanf("%d", &remover);

        limpar_buffer();

        NoArv* res= BuscaIncidente(arvore->raiz,remover);

        if (res!=NULL)
        {
            printf("\n\t--- Incidente Removido ---\n");
            printf("\tID do Incidente: %d\n", res->info.N_U_Id);
            printf("\tID do Equipamento associado: %d\n", res->info.id_equip);
            printf("\tNivel de Gravidade: %d\n", res->info.gravidade);
            printf("\t\t\t---APERTE ENTER PARA CONTINUAR---\n");
            getchar();

            arvore->raiz = removerIncidente(arvore->raiz, remover);
        }
        else{
            printf("\n\tIncidente não encontrado");
            printf("\t\t\t---APERTE ENTER PARA CONTINUAR---\n");
            getchar();
        }
    }
}
void liberarArvore(NoArv* raiz)
{
    if (raiz != NULL)
    {
        liberarArvore(raiz->esq);
        liberarArvore(raiz->dir);
        free(raiz);
    }
}
#endif
