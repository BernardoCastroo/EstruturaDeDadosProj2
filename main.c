#include "BibliotecaGeral.h"

void menu(Arv* Arvore, NoHash* TabelaHash[])
{
    int opc;
    do {
        system("cls");
        opc = -1;

        printf("\n\t==================================================\n");
        printf("\t            GERENCIAMENTO DE FALHAS               \n");
        printf("\t==================================================\n");
        printf("\t [1] Cadastrar Equipamento                        \n");
        printf("\t [2] Registrar Incidente                          \n");
        printf("\t [3] Consultar Equipamento e Incidente            \n");
        printf("\t [4] Listar todos os Incidentes                   \n");
        printf("\t [5] Excluir um Incidente                         \n");
        printf("\t [6] Excluir um Equipamento                       \n");
        printf("\t [7] Encerrar Programa                            \n");
        printf("\t--------------------------------------------------\n");
        printf("\tDigite a opcão desejada: ");

        scanf("%d", &opc);
        limpar_buffer();

        switch(opc)
        {
            case 1:
                adicionarEquipamento(TabelaHash);
                break;

            case 2:
                adicionarIncidente(Arvore, TabelaHash);

                break;

            case 3:
                consultarEquipamento(Arvore->raiz, TabelaHash);
                break;

            case 4:
                system("cls");
                printf("\n\t==================================================\n");
                printf("\t            LISTA DE INCIDENTES            \n");
                printf("\t==================================================\n");
                printf("\t%-15s | %-16s | %-10s\n",
                           "ID_INCIDENTE", "ID_EQUIPAMENTO", "GRAVIDADE");
                printf("\t--------------------------------------------------\n");
                ListaIncidentes(Arvore->raiz);

                printf("\t==================================================\n");
                printf("\n\t\t---APERTE ENTER PARA CONTINUAR---\n");
                getchar();
                break;
                break;

            case 5:
                excluirIncidente(Arvore, TabelaHash);
                break;
            case 6:
                excluirEquipamento(Arvore, TabelaHash);
                printf("\n\t\t---APERTE ENTER PARA CONTINUAR---\n");
                getchar();
                break;

            case 7:
                system("cls");
                liberarLista(TabelaHash);
                liberarArvore(Arvore->raiz);
                liberarHash(TabelaHash);
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

    NoHash* TabelaHash[Tam_hash];
    inicializaHash(TabelaHash);

    menu(Arvore, TabelaHash);

    return 0;
}
