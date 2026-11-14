#include "BibliotecaArvore.h"

void menu(Arv* Arvore)
{
    int opc;
    do {
        system("cls");
        opc = -1;

        printf("\n\t==================================================\n");
        printf("\t            GERENCIAMENTO DE FALHAS               \n");
        printf("\t==================================================\n");
        printf("\t [1] Cadastrar Equipamento (Tabela Hash)          \n");
        printf("\t [2] Registrar Incidente                          \n");
        printf("\t [3] Consultar Equipamento e Incidente            \n");
        printf("\t [4] Listar todos os Incidentes                   \n");
        printf("\t [5] Excluir um Incidente                         \n");
        printf("\t [6] Excluir um Equipamento                       \n");
        printf("\t [7] Encerrar Programa                            \n");
        printf("\t--------------------------------------------------\n");
        printf("\tDigite a opcao desejada: ");

        scanf("%d", &opc);
        limpar_buffer();

        switch(opc)
        {
            case 1://fazer a hash
                system("cls");
                printf("\n\t==================================================\n");
                printf("\t             CADASTRAR EQUIPAMENTO                \n");
                printf("\t==================================================\n");


                printf("\n\t\t---APERTE ENTER PARA CONTINUAR---\n");
                getchar();
                break;

            case 2:
                adicionarIncidente(Arvore);
                getchar();
                break;

            case 3://mostrar as coisa da HAsh
                system("cls");
                printf("\n\t==================================================\n");
                printf("\t         CONSULTAR EQUIPAMENTO E INCIDENTE        \n");
                printf("\t==================================================\n\n");

                passa_Incidente(Arvore->raiz);

                break;

            case 4:
                system("cls");
                printf("\n\t==================================================\n");
                printf("\t            LISTA DE INCIDENTES            \n");
                printf("\t==================================================\n");
                printf("\t%-15s | %-16s | %-10s\n",
                           "ID_INCIDENTE", "ID_EQUIPAMENTO", "GRAVIDADE");
                ListaIncidentes(Arvore->raiz);

                printf("\t==================================================\n");
                printf("\n\t\t---APERTE ENTER PARA CONTINUAR---\n");
                getchar();
                break;
                break;

            case 5:
                system("cls");
                printf("\n\t==================================================\n");
                printf("\t                 EXCLUIR INCIDENTE                \n");
                printf("\t==================================================\n");
                excluirInsidente(Arvore);
                break;
            case 6:
                system("cls");
                printf("\n\t==================================================\n");
                printf("\t                EXCLUIR EQUIPAMENTO               \n");
                printf("\t==================================================\n");
                printf("\n\t[Aguardando implementacao da Hash...]\n");

                printf("\n\t\t---APERTE ENTER PARA CONTINUAR---\n");
                getchar();
                break;

            case 7:// liberar a tabela Hash
                system("cls");
                liberarArvore(Arvore->raiz);
                free(Arvore);
                printf("\n\t==================================================\n");
                printf("\t             FINALIZANDO O PROGRAMA...            \n");
                printf("\t==================================================\n\n");
                break;

            default:
                system("cls");
                printf("\n\t==================================================\n");
                printf("\t               !!! OPCAO INVALIDA !!!             \n");
                printf("\t              Insira um valor valido.             \n");
                printf("\t==================================================\n");
                printf("\n\t\t---APERTE ENTER PARA CONTINUAR---\n");
                getchar();
                break;
        }
    } while(opc != 7);
}

int main()
{
    setlocale(LC_ALL, "Portuguese");
    Arv* Arvore = criaArvore();

    Inci Teste={50,1024,2};
    Arvore->raiz=inserirIncidente(Arvore->raiz, Teste);

    menu(Arvore);

    return 0;
}
