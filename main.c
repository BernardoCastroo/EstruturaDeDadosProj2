#include "BibliotecaArvore.h"

int main(){

    setlocale(LC_ALL, "Portuguese");
    Arv* Arvore = criaArvore();

    Inci Teste={50,1024,2};
    Arvore->raiz=inserirIncidente(Arvore->raiz, Teste);

    return 0;
}
