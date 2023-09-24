#ifndef MI_H_INCLUDED
#define MI_H_INCLUDED
#include <sstream>
#include <fstream>

using namespace std;

//Será acessada pela struct ListaDuplamenteEncadeada via "->"
template<typename T>
struct Nodo{
    T elemento;
    Nodo<T> *anterior;
    Nodo<T> *proximo;
};

//Terá acesso aos seus atributos internos via "."
template<typename T>
struct ListaDuplamenteEncadeada{
    int cardinalidade;
    Nodo<T> *inicio;
    Nodo<T> *fim;
};

//Inicializa as variáveis *lista_ e usa outra função para carrregar os dados do arquivo para uma lista
template<typename T>
void iniciar(ListaDuplamenteEncadeada<T> &lista_voos, ListaDuplamenteEncadeada<T> &lista_clientes, ListaDuplamenteEncadeada<T> &lista_saida){
    lista_voos.cardinalidade = 0;
    lista_voos.inicio = NULL;
    lista_voos.fim = NULL;
    lista_clientes.cardinalidade = 0;
    lista_clientes.inicio = NULL;
    lista_clientes.fim = NULL;
    lista_saida.cardinalidade = 0;
    lista_saida.inicio = NULL;
    lista_saida.fim = NULL;

    fstream fin("ENTRADA.TXT");
    for(string linha; getline(fin,linha);){
        gerar_lista(lista_voos, linha);
    }
    fin.close();
}

template<typename T>
void gerar_lista(ListaDuplamenteEncadeada<T> &lista, T elemento){
    Nodo<T> *nodo_novo = new Nodo<T>;
    nodo_novo->elemento = elemento;
    nodo_novo->anterior = NULL;
    nodo_novo->proximo = NULL;

    //Condicional para não gerar lista de linha indevida
    if(elemento.size() > 8){
        if(lista.cardinalidade == 0){
            lista.inicio = nodo_novo;
            lista.fim = nodo_novo;
        }else{
            nodo_novo->anterior = lista.fim;
            lista.fim->proximo = nodo_novo;
            lista.fim = nodo_novo;
        }
        lista.cardinalidade++;
    }
}

template<typename T>
void mostrar(ListaDuplamenteEncadeada<T> &lista){
    Nodo<T> *atual = lista.inicio;
    while(atual != NULL){
        cout << " " << atual->elemento << endl;
        atual = atual->proximo;
    }
}

template<typename T>
void visualizar_listas(ListaDuplamenteEncadeada<T> lista_voos, ListaDuplamenteEncadeada<T> lista_clientes, ListaDuplamenteEncadeada<T> lista_saida){
    cout << "---------------------------------------------------\n";
    cout << "---------------------------------------------------\n";
    cout << "Lista voos\n";
    mostrar<string>(lista_voos);
    cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - \n";
    cout << "lista clientes\n";
    mostrar<string>(lista_clientes);
    cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - \n";
    cout << "lista de saida\n";
    mostrar<string>(lista_saida);
}

//Garante que as letras estarão padronizadas para haver comparações futuras
string maiuscula(string linha){
    string valor;
    char aux;
    for(unsigned int i = 0; i < linha.size(); i++){
        aux = linha[i];
        valor += toupper(aux);
    }

    return valor;
}

string pegar_origem_cliente(string linha){
    int cont = 0, inicio, fim;
    string parte = "";
    for(unsigned int i = linha.size(); i >= 0; i--){
        if(linha[i] == ' '){
            cont++;
        }
        if(cont == 2){
            inicio = i + 1;
            break;
        }
    }
    for(unsigned int i = inicio; i < linha.size(); i++){
        if(linha[i] == ' '){
            fim = i;
            break;
        }
    }
    for(int i = inicio; i < fim; i++){
        parte += linha[i];
    }
    return parte;
}

string pegar_destino_cliente(string linha){
    int inicio;
    string parte = "";
    for(unsigned int i = linha.size() - 1; i >= 0; i--){
        if(linha[i] == ' '){
            inicio = i + 1;
            break;
        }
    }
    for(unsigned int i = inicio; i < linha.size(); i++){
        parte += linha[i];
    }

    return parte;
}

string pegar_origem_voo(string linha){
    int inicio, fim;
    string parte = "";
    for(unsigned int i = 0; i < linha.size(); i++){
        if(linha[i] == ' '){
            inicio = i + 1;
            break;
        }
    }
    for(unsigned int i = inicio; i < linha.size(); i++){
        if(linha[i] == ' '){
            fim = i;
            break;
        }
    }
    for(int i = inicio; i  < fim; i++){
        parte += linha[i];
    }

    return parte;
}

string pegar_destino_voo(string linha){
    int cont = 0, inicio, fim;
    string parte = "";
    for(unsigned int i = linha.size() - 1; i >= 0; i--){
        if(linha[i] == ' '){
            cont++;
        }
        if(cont == 2){
            inicio = i + 1;
            break;
        }
    }
    for(unsigned int i = inicio; i < linha.size(); i++){
        if(linha[i] == ' '){
            fim = i;
            break;
        }
    }
    for(int i = inicio; i < fim; i++){
        parte += linha[i];
    }

    return parte;
}

string pegar_id_aviao(string linha){
    string parte = "";
    for(unsigned int i = 0; i < linha.size(); i++){
        if(linha[i] != ' '){
            parte += linha[i];
        }else{
            break;
        }
    }

    return parte;
}

int pegar_quantidade_assentos(string linha){
    int inicio, valor;
    string parte = "";
    for(unsigned int i = linha.size() - 1; i >= 0; i--){
        if(linha[i] == ' '){
            inicio = i + 1;
            break;
        }
    }
    for(unsigned int i = inicio; i < linha.size(); i++){
        parte += linha[i];
    }
    valor = atoi(parte.c_str());

    return valor;
}

string pegar_nome_cliente(string linha){
    int cont = 0, inicio, fim;
    string parte = "";
    for(unsigned int i = 0; i < linha.size(); i++){
        if(linha[i] == ' '){
            inicio = i + 1;
            break;
        }
    }
    for(unsigned int i = linha.size() - 1; i >= 0; i--){
        if(linha[i] == ' '){
            cont++;
        }
        if(cont == 2){
            fim = i;
            break;
        }
    }
    for(int i = inicio; i < fim; i++){
        parte += linha[i];
    }

    return parte;
}

template<typename T>
void acao_cliente(
    ListaDuplamenteEncadeada<T> &lista_voos,
    ListaDuplamenteEncadeada<T> &lista_clientes,
    ListaDuplamenteEncadeada<T> &lista_saida,
    T operacao){

    string nome_cliente, origem_cliente, destino_cliente;
    int espacos = 0;

    //Verificar a validade da linha da lista, no mínimo a linha precisa ter 3 espaços
    for(unsigned int i = 0; i < operacao.size(); i++){
        if(operacao[i] == ' '){
            espacos++;
        }
    }
    if(espacos < 3){
        cout << "Operacao invalida!\n";
    }else{
        Nodo<T> *nodo_novo = new Nodo<T>;
        nodo_novo->elemento = operacao;
        nodo_novo->anterior = NULL;
        nodo_novo->proximo = NULL;

        if(lista_clientes.cardinalidade == 0){
            lista_clientes.inicio = nodo_novo;
            lista_clientes.fim = nodo_novo;
        }else{
            nodo_novo->anterior = lista_clientes.fim;
            lista_clientes.fim->proximo = nodo_novo;
            lista_clientes.fim = nodo_novo;
        }
        lista_clientes.cardinalidade++;

        //Partes que serão geradas para a lista_saida
        string parte1, parte2, parte3;

        nome_cliente = pegar_nome_cliente(operacao);
        parte2 = nome_cliente;
        parte2 += " ** ";

        string origem_voo, destino_voo, id_aviao;
        int quantidade_assentos;
        bool achou = false;
        Nodo<T> *atual = lista_voos.inicio;
        while(atual != NULL){
            origem_cliente = pegar_origem_cliente(operacao);
            destino_cliente = pegar_destino_cliente(operacao);
            origem_voo = pegar_origem_voo(atual->elemento);
            destino_voo = pegar_destino_voo(atual->elemento);
            if(origem_voo == origem_cliente && destino_voo == destino_cliente){
                achou = true;
                quantidade_assentos = pegar_quantidade_assentos(atual->elemento);
                id_aviao = pegar_id_aviao(atual->elemento);
                if(operacao[0] == '-'){
                    quantidade_assentos++;
                    stringstream ss;
                    ss << quantidade_assentos;
                    string aux_quantidade_assentos = ss.str();
                    atual->elemento = id_aviao + " " + origem_voo + " " + destino_voo + " " + aux_quantidade_assentos;

                    parte1 = "** CONFIRMADO ** ";
                    parte3 = "VOO DESMARCADO";
                }else{
                    if(quantidade_assentos == 0){
                        parte1 = "** NAO CONFRIMADO ** ";
                        parte3 = "VOO LOTADO";
                    }else{
                        quantidade_assentos--;
                        stringstream ss;
                        ss << quantidade_assentos;
                        string aux_quantidade_assentos = ss.str();
                        atual->elemento = id_aviao + " " + origem_voo + " " + destino_voo + " " + aux_quantidade_assentos;

                        parte1 = "** CONFIRMADO ** ";
                        parte3 = id_aviao;
                    }
                }
                break;
            }
            atual = atual->proximo;
        }
        //Para caso o voo não for encontrado na lista!
        if(!achou){
            parte1 = "** NAO CONFIRMADO ** ";
            parte3 = "VOO INEXISTENTE";
        }

        //Armazenar as atualizações na lista_saida
        Nodo<T> *nodo_saida = new Nodo<T>;
        nodo_saida->elemento = parte1 + parte2 + parte3;
        nodo_saida->anterior = NULL;
        nodo_saida->proximo = NULL;

        if(lista_saida.cardinalidade == 0){
            lista_saida.inicio = nodo_saida;
            lista_saida.fim = nodo_saida;
        }else{
            nodo_saida->anterior = lista_saida.fim;
            lista_saida.fim->proximo = nodo_saida;
            lista_saida.fim = nodo_saida;
        }
        lista_saida.cardinalidade++;
    }
}

#endif // MI_H_INCLUDED
