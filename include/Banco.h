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
    vector <Transacao*> vecTransacao;

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
    void listarCartao();
    void alterarStatusCartao(bool bloquear);
    void bloquear();
    void desbloquear();
    void alterarLimite();
    void pagamentoParcelado();
    void pagarFatura();
    void cadernetaDePoupanca();

    template<typename T>
    void showVector(vector<T*>& vec, string msg) {
        cout << msg << endl;
        for (auto ptr : vec)
            cout << *ptr;
        cout << endl;
    }
    template<typename T>
    T* pesquisaID(const std::vector<T*>& vec, size_t id) {
        for (auto ptr : vec) {
            if (ptr->getID() == id)
                return ptr;
        }
        return nullptr;
    }


    int getQtdCliente() const;
    int getQtdGerente() const;
    void setQtdCliente(int);
    void setQtdGerente(int);

    friend Cliente* pesquisaIDCliente(size_t);
    ~Banco();
};

#endif