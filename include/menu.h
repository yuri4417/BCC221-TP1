#ifndef BANCO_H
#define BANCO_H

#include <vector>
#include "Cliente.h"
#include "Gerente.h"
using namespace std;

class Banco {
    int qtdClientes;
    int qtdGerentes;
    vector <Cliente*> vecCliente;
    vector <Gerente*> vecGerente;

public:
    Banco(int qtdC = 0, int qtdG = 0);
    void run();
    void cadastrarCliente();
    void cadastrarGerente();
    void associarGerenteCliente();
    void imprimirOpcoes();
    void criarTransacao();
    void exibirExtrato();
    void listarClientes();
    void listarGerentes();
    void carregaDados();
    void salvaDados();
    void cartaoCredito();
    void criarCartao();
    void cadernetaDePoupanca();

    template<typename T>
    void showVector(vector<T*>& vec, string msg) {
        cout << msg << endl;
        for (auto ptr : vec)
            cout << *ptr;
        cout << endl;
    }
    Cliente* pesquisaIDCliente(size_t);


    int getQtdCliente() const;
    int getQtdGerente() const;
    void setQtdCliente(int);
    void setQtdGerente(int);

    friend Cliente* pesquisaIDCliente(size_t);
};

#endif