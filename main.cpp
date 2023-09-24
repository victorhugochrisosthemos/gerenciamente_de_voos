#include <iostream>
#include "MI.h"

using namespace std;

int main()
{
    ListaDuplamenteEncadeada<string> lista_voos;
    ListaDuplamenteEncadeada<string> lista_clientes;
    ListaDuplamenteEncadeada<string> lista_saida;
    int escolha;
    string operacao;

    iniciar(lista_voos, lista_clientes, lista_saida);

    do{
        visualizar_listas(lista_voos, lista_clientes, lista_saida);
        cout << "1 - Sobre reservas\n";
        cout << "2 - Sair\n";
        cout << "Escolha uma opcao: ";
        cin >> escolha;
        if(escolha < 1 || escolha > 2){
            cout << "Opcao invalida!\n";
        }else{
            if(escolha == 1){
                cout << "\nDigite a operacao\n";
                cout << "Lembrando...('+/-' + espaco + 'NOME' + espaco + 'ORIGEM' + espaco + 'DESTINO')\n";
                cin.ignore();
                getline(cin,operacao);
                operacao = maiuscula(operacao);
                acao_cliente(lista_voos, lista_clientes, lista_saida, operacao);
            }
            cout << "Operacao encaminhada!\n\n";
        }
    }while(escolha != 2);

    Nodo<string> *atual = lista_voos.inicio;
    while(atual != NULL){
        Nodo<string> *proximo = atual->proximo;
        delete atual;
        atual = proximo;
    }
    lista_voos.cardinalidade = 0;
    lista_voos.inicio = NULL;
    lista_voos.fim = NULL;

    atual = lista_clientes.inicio;
    while(atual != NULL){
        Nodo<string> *proximo = atual->proximo;
        delete atual;
        atual = proximo;
    }
    lista_clientes.cardinalidade = 0;
    lista_clientes.inicio = NULL;
    lista_clientes.fim = NULL;

    atual = lista_saida.inicio;
    while(atual != NULL){
        Nodo<string> *proximo = atual->proximo;
        delete atual;
        atual = proximo;
    }
    lista_saida.cardinalidade = 0;
    lista_saida.inicio = NULL;
    lista_saida.fim = NULL;

    return 0;
}
