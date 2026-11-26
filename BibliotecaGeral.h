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

void inserirInciNaLista(NoHash* equip, int Codigo_inci)
{
    NoListaInci* novo = (NoListaInci*) malloc(sizeof(NoListaInci));
    if (novo != NULL)
    {
        novo->id_incidente = Codigo_inci;
        novo->prox = equip->info.listaIncidentes;
        equip->info.listaIncidentes = novo;
    }
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

        printf("\n\tEquipamento: %s (ID: %d) cadastrado com sucesso!\n", novo.nome, novo.C_U_Id);
        printf("\n\t\t---APERTE ENTER PARA CONTINUAR---\n");
        getchar();
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
            if(raiz->esq == NULL && raiz->dir!=NULL)
            {
                NoArv* aux = raiz->dir;
                free(raiz);
                return aux;
            }
            if(raiz->esq != NULL && raiz->dir==NULL)
            {
                NoArv* aux = raiz->esq;
                free(raiz);
                return aux;
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

void excluirEquipamento(Arv* arvore, NoHash* TabHash[])
{
    Inci Equipexclu;
    if (HashVazia(TabHash)==1)
    {
       system("cls");
        printf("\n\tERRO! Não ha códigos cadastados!");
        printf("\n\t\t---APERTE ENTER PARA CONTINUAR---\n");
        getchar();
    }
    else
    {
        do{
            system("cls");
            printf("\n\t==================================================\n");
            printf("\t                EXCLUIR EQUIPAMENTO               \n");
            printf("\t==================================================\n");

            printf("\n\tDigite o Código do Equipamento(4 Dígitos):");
            scanf("%d",&Equipexclu.id_equip);
            limpar_buffer();

            if(Equipexclu.id_equip<1000 || Equipexclu.id_equip>9999)
            {
                system("cls");
                printf("\n\tERRO!!! O Código tem que ter 4 dígitos!");
                printf("\n\t\t---APERTE ENTER PARA CONTINUAR---\n");
                getchar();
            }
        }while(Equipexclu.id_equip<1000 || Equipexclu.id_equip>9999);

        NoHash* equip= buscarEquipamento(TabHash, Equipexclu.id_equip);
        if (equip == NULL)
        {
            system("cls");
            printf("\n\tERRO!!! Equipamento não encontrado!");

        }
        else
        {
            NoListaInci* aux;
            while(equip->info.listaIncidentes!= NULL)
            {
                aux = equip->info.listaIncidentes;

                arvore->raiz=removerIncidente(arvore->raiz, aux->id_incidente);
                equip->info.listaIncidentes= equip->info.listaIncidentes->prox;
                free(aux);
            }
            int ind= funcaoHash(Equipexclu.id_equip), excluiu =0;
            NoHash* atual = TabHash[ind];
            NoHash* ante = NULL;

            while (atual != NULL && excluiu != 1)
            {
                if(atual->info.C_U_Id == Equipexclu.id_equip)
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
                    excluiu = 1;
                }
                if(excluiu != 1)
                {
                    ante=atual;
                    atual=atual->prox;
                }
                else
                {
                    system("cls");
                    printf("\n\tEquipamento excluido com sucesso!");
                }

            }
        }
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

void liberarLista(NoHash* TabHash[])
{
    NoHash* atual;
    NoListaInci* aux;

    for(int i = 0; i < Tam_hash; i++)
    {
        atual = TabHash[i];
        while(atual != NULL)
        {
            while(atual->info.listaIncidentes != NULL)
            {
                aux = atual->info.listaIncidentes;
                atual->info.listaIncidentes = atual->info.listaIncidentes->prox;
                free(aux);
            }
            atual = atual->prox;
        }
    }
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

void adicionarIncidente(Arv* arvore, NoHash* TabHash[])
{
    Inci novo;
    if (HashVazia(TabHash)==1)
    {
       system("cls");
        printf("\n\tERRO! Não ha códigos cadastados!");
        printf("\n\t\t---APERTE ENTER PARA CONTINUAR---\n");
        getchar();
    }
    else
    {
        do{
            system("cls");
            printf("\n\t==================================================\n");
            printf("\t               REGISTRAR INCIDENTE                \n");
            printf("\t==================================================\n");

                printf("\n\tDigite o Código do Equipamento(4 Dígitos):");
                scanf("%d",&novo.id_equip);
                limpar_buffer();

                if(novo.id_equip<1000 || novo.id_equip>9999)
                {
                    system("cls");
                    printf("\n\tERRO!!! O Código tem que ter 4 dígitos!");
                    printf("\n\t\t---APERTE ENTER PARA CONTINUAR---\n");
                    getchar();
                }
        }while(novo.id_equip<1000 || novo.id_equip>9999);

        NoHash* equip = buscarEquipamento(TabHash, novo.id_equip);

        if(equip == NULL)
        {
                system("cls");
                printf("\n\tERRO!!! Código não encontrado!");
                printf("\n\t\t---APERTE ENTER PARA CONTINUAR---\n");
                getchar();
        }
        else
        {
            do{
                printf("\n\t--- Equipamento Encontrado ---\n");
                printf("\tEquipamento: %s\n", equip->info.nome);
                printf("\tID: %d\n", equip->info.C_U_Id);

                printf("\n\tDigite o ID do Incidente (2 digitos): ");
                scanf("%d", &novo.N_U_Id);
                limpar_buffer();

                if(novo.N_U_Id<10 || novo.N_U_Id>99)
                {
                    system("cls");
                    printf("\n\tERRO!!! O ID do Incidente de ter 2 dígitos!");
                    printf("\n\t\t---APERTE ENTER PARA CONTINUAR---\n");
                    getchar();
                }
            }while(novo.N_U_Id<10 || novo.N_U_Id>99);

            if (BuscaIncidente(arvore->raiz,novo.N_U_Id)!=NULL)
            {
                    system("cls");
                    printf("\n\tERRO!!! Já existe um incidente com esse ID!");
                    printf("\n\t\t---APERTE ENTER PARA CONTINUAR---\n");
                    getchar();
            }
            else
            {
                do
                {
                    printf("\tDigite a Gravidade (1-Baixa, 2-Media, 3-Alta): ");
                    scanf("%d", &novo.gravidade);
                    limpar_buffer();

                    if(novo.gravidade<1 || novo.gravidade>3)
                    {
                        system("cls");
                        printf("\n\tA gravidade de estra entre (1-Baixa, 2-Media, 3-Alta)!");
                        printf("\n\t\t---APERTE ENTER PARA CONTINUAR---\n");
                        getchar();
                    }

                }while(novo.gravidade<1 || novo.gravidade>3);

                arvore->raiz=inserirIncidente(arvore->raiz, novo);
                inserirInciNaLista(equip,novo.N_U_Id);

                printf("\n\tIncidente cadastrado com sucesso!\n");

                printf("\n\t\t---APERTE ENTER PARA CONTINUAR---\n");
            }
        }
    }
}

void imprimirGradeEquipamento(NoArv* raiz, NoHash* equip)
{
    NoListaInci* atual = equip->info.listaIncidentes;

    system("cls");
    printf("\n\t==================================================\n");
    printf("\t               DADOS DO EQUIPAMENTO               \n");
    printf("\t==================================================\n");
    printf("\t Código: %-10d | Nome: %-20s\n", equip->info.C_U_Id, equip->info.nome);
    printf("\t==================================================\n");

    if(atual==NULL)
            {
                printf("\n\t\tEste equipamento não possui incidentes!");
                printf("\n\t\t---APERTE ENTER PARA CONTINUAR---\n");
            }
    else
    {
        printf("\t%-22s | %-25s\n", "ID_INCIDENTE", "GRAVIDADE");
        printf("\t--------------------------------------------------\n");
        while(atual!=NULL)
        {
            NoArv* noInci= BuscaIncidente(raiz, atual->id_incidente);

            if (noInci != NULL)
                {
                    printf("\t%-22d | %-25d\n",
                           noInci->info.N_U_Id, noInci->info.gravidade);
                    printf("\t--------------------------------------------------\n");
                }
                atual = atual->prox;
        }
            printf("\t==================================================\n");
            printf("\n\t\t---APERTE ENTER PARA CONTINUAR---\n");
    }
}

void consultarEquipamento(NoArv* raiz, NoHash* TabHash[])
{
    Inci novo;
    if(HashVazia(TabHash)==1)
    {
        system("cls");
        printf("\n\tERRO! Não ha códigos cadastados!");
        printf("\n\t\t---APERTE ENTER PARA CONTINUAR---\n");
        getchar();
    }
    else
    {
        do{
            system("cls");
            printf("\n\t==================================================\n");
            printf("\t            CONSULTAR EQUIPAMENTO E INCIDENTE \n");
            printf("\t==================================================\n");

            printf("\n\tDigite o Código do Equipamento(4 Dígitos):");
            scanf("%d",&novo.id_equip);
            limpar_buffer();

            if(novo.id_equip<1000 || novo.id_equip>9999)
            {
                system("cls");
                printf("\n\tERRO!!! O Código tem que ter 4 dígitos!");
                printf("\n\t\t---APERTE ENTER PARA CONTINUAR---\n");
                getchar();
            }
        }while(novo.id_equip<1000 || novo.id_equip>9999);

        NoHash* equip = buscarEquipamento(TabHash, novo.id_equip);

        if(equip == NULL)
        {
                system("cls");
                printf("\n\tERRO!!! Código não encontrado!");
                printf("\n\t\t---APERTE ENTER PARA CONTINUAR---\n");
                getchar();
        }
        else
        {
            imprimirGradeEquipamento(raiz, equip);
            getchar();
        }
    }
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

void removerInciDaLista(NoHash* equip, int Codigo_inci)
{
    NoListaInci* atual = equip->info.listaIncidentes;
    NoListaInci* ante = NULL;
    int achou = 0;

    while (atual != NULL && achou == 0)
    {
        if (atual->id_incidente == Codigo_inci)
        {
            if (ante == NULL)
            {
                equip->info.listaIncidentes = atual->prox;
            }
            else
            {
                ante->prox = atual->prox;
            }
            free(atual);
            achou = 1;
        }
        else
        {
            ante = atual;
            atual = atual->prox;
        }
    }
}

void excluirIncidente(Arv* arvore, NoHash* TabHash[])
{
    Inci novo;
    if(HashVazia(TabHash)== 1)
    {
        system("cls");
        printf("\n\tERRO! Não ha códigos cadastados!");
        printf("\n\t\t---APERTE ENTER PARA CONTINUAR---\n");
        getchar();
    }
    else
    {
        do{
            system("cls");
            printf("\n\t==================================================\n");
            printf("\t                 EXCLUIR INCIDENTE                \n");
            printf("\t==================================================\n");

            printf("\n\tDigite o Código do Equipamento(4 Dígitos):");
            scanf("%d",&novo.id_equip);
            limpar_buffer();

            if(novo.id_equip<1000 || novo.id_equip>9999)
            {
                system("cls");
                printf("\n\tERRO!!! O Código tem que ter 4 dígitos!");
                printf("\n\t\t---APERTE ENTER PARA CONTINUAR---\n");
                getchar();
            }
        }while(novo.id_equip<1000 || novo.id_equip>9999);

        NoHash* equip = buscarEquipamento(TabHash, novo.id_equip);
        if(equip == NULL)
        {
            system("cls");
            printf("\n\tERRO!!! Código não encontrado!");
            printf("\n\t\t---APERTE ENTER PARA CONTINUAR---\n");
            getchar();
        }
        else
        {
            imprimirGradeEquipamento(arvore->raiz, equip);
            if (equip->info.listaIncidentes == NULL)
            {
                getchar();
            }
            else
            {
                do{
                    printf("\n\tDigite o ID do Incidente (2 digitos), que você deseja excluir: ");
                    scanf("%d", &novo.N_U_Id);
                    limpar_buffer();

                    if(novo.N_U_Id<10 || novo.N_U_Id>99)
                    {
                        system("cls");
                        printf("\n\tERRO!!! O ID do Incidente de ter 2 dígitos!");
                        printf("\n\t\t---APERTE ENTER PARA CONTINUAR---\n");
                        getchar();
                    }
                }while(novo.N_U_Id<10 || novo.N_U_Id>99);

                NoArv* alvo = BuscaIncidente(arvore->raiz, novo.N_U_Id);

                if (alvo == NULL || alvo->info.id_equip != equip->info.C_U_Id)
                {
                    system("cls");
                    printf("\n\tERRO!!! Esse incidente não pertence a este equipamento!");
                    printf("\n\t\t---APERTE ENTER PARA CONTINUAR---\n");
                    getchar();
                }
                else
                {
                    removerInciDaLista(equip, novo.N_U_Id);
                    arvore->raiz = removerIncidente(arvore->raiz, novo.N_U_Id);

                    printf("\n\tIncidente excluido com sucesso!");
                    printf("\n\t\t---APERTE ENTER PARA CONTINUAR---\n");
                    getchar();
                }
            }
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
