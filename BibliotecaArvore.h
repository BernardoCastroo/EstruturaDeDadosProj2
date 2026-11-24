#ifndef BIBLIOTECAARVORE_H_INCLUDED
#define BIBLIOTECAARVORE_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#define Tam_hash 61// 52/61=~0,85

typedef struct Incidentes
{
    int N_U_Id;
    int id_equip;
    int gravidade;
} Inci;

typedef struct NoListaInci
{
    int id_incidente;
    struct NoListaInci *prox;
} NoListaInci;

typedef struct Equipamento
{
    int C_U_Id;
    char nome[11];
    NoListaInci *listaIncidentes;
}Equip;
// struct arvore
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

typedef struct NoHash
{
    Equip info;
    struct NoHash *prox;
}NoHash;

void inicializaHash(NoHash* hash[])
{
    for (int i = 0; i < Tam_hash; i++)
    {
        hash[i] = NULL;
    }
}

int HashVazia(NoHash* hash[])
{
    for (int i = 0; i < Tam_hash; i++)
    {
        if (hash[i] != NULL)
        {
            return 0;
        }
    }
    return 1;
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

int funcaoHash(int codigo)
{
    return codigo%Tam_hash;
}

void inserirEquipamento(NoHash* Hash[], Equip novoEq)
{
    int ind = funcaoHash(novoEq.C_U_Id);

    NoHash* novo = (NoHash*) malloc(sizeof(NoHash));

    novo->info = novoEq;
    novo->prox = Hash[ind];
    Hash[ind] = novo;;
}

NoHash* buscarEquipamento(NoHash* TabHash[], int codigo)
{
    int ind= funcaoHash(codigo);

    NoHash* atual = TabHash[ind];

    while(atual != NULL)
    {
        if(atual->info.C_U_Id == codigo)
        {
            return atual;
        }
        atual= atual->prox;
    }
    return NULL;
}

int removerEquipamento (NoHash* TabHash[], int codigo)
{
    int ind= funcaoHash(codigo);
    NoHash* atual = TabHash[ind];
    NoHash* ante = NULL;

    while (atual != NULL)
    {
        if(atual->info.C_U_Id == codigo)
        {
            if(ante ==NULL)
            {
                TabHash[ind] = atual->prox;
            }
            else
            {
                ante->prox = atual->prox;
            }
            free(atual);
            return 1;
        }

        ante=atual;
        atual=atual->prox;
    }
    return 0;
}
void adicionarEquipamento(NoHash* TabHash[])
{
    Equip novo;
    int valido;

    do{
        system("cls");
        printf("\n\t==================================================\n");
        printf("\t             CADASTRAR EQUIPAMENTO                \n");
        printf("\t==================================================\n");

        printf("\n\tDigite o Código do Equipamento(4 Dígitos):");
        scanf("%d",&novo.C_U_Id);
        limpar_buffer();

        if(novo.C_U_Id<1000 || novo.C_U_Id>9999)
        {
            system("cls");
            printf("\n\tERRO!!! O Código tem que ter 4 dígitos!");
            printf("\n\t\t---APERTE ENTER PARA CONTINUAR---\n");
            getchar();
        }


    }while(novo.C_U_Id<1000 || novo.C_U_Id>9999);

    if(buscarEquipamento(TabHash, novo.C_U_Id)!=NULL)
    {
        system("cls");
        printf("\n\tERRO!!! O Código do Equipamento já existe!");
        printf("\n\t\t---APERTE ENTER PARA CONTINUAR---\n");
        getchar();
    }
    else
    {
        do
        {
            valido = 0;
            printf("\n\tDigite o Nome do Equipamento (Máximo 10 caracteres): ");
            fgets(novo.nome, sizeof(novo.nome), stdin);

            if (novo.nome[strlen(novo.nome) - 1] != '\n')
            {
                system("cls");
                valido = 1;
                limpar_buffer();
                printf("\n\t!!! O nome do equipamento deve ter no máximo 10 caracteres !!!\n");
            }
            else
            {
                novo.nome[strcspn(novo.nome, "\n")] = '\0';
                if (strlen(novo.nome) == 0)
                {
                    system("cls");
                    valido = 1;
                    printf("\n\t!!! O nome do equipamento nao pode ficar vazio !!!\n");
                }
            }

        } while (valido == 1);

        novo.listaIncidentes = NULL;
        inserirEquipamento(TabHash, novo);

        inserirEquipamento(TabHash, novo);

        printf("\n\tEquipamento: %s (ID: %d) cadastrado com sucesso!\n", novo.nome, novo.C_U_Id);
        printf("\n\t\t---APERTE ENTER PARA CONTINUAR---\n");
        getchar();
    }

}

void liberarHash(NoHash* tabHash[])
{
    NoHash* atual;
    NoHash* pr;

    for(int i = 0; i < Tam_hash; i++)
    {
        atual = tabHash[i];
        pr = NULL;
        while(atual != NULL)
        {
            pr=atual->prox;
            free(atual);
            atual=pr;
        }
        tabHash[i] = NULL;
    }
}












//ARVORE

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
