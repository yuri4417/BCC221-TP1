#ifndef BANCO_H
#define BANCO_H

#include <vector>
#include "Cliente.h"
#include "utils.h"
#include "Gerente.h"
using namespace std;

class Banco {
    int qtdClientes;
    int qtdGerentes;
    vector <Cliente*> vecCliente;
    vector <Gerente*> vecGerente;
    vector <Transacao*> vecTransacao;


    bool verificaSenha(const std::string& senhaCorreta, const std::string& prompt);
public:

    Banco(int qtdC = 0, int qtdG = 0);
    virtual ~Banco();
    void run();
    void cadastrarCliente();
    void cadastrarGerente();
    void criarTransacao();
    void exibirExtrato();
    void associarGerenteCliente();
    void listarClientes();
    void listarGerentes();
    void listarCartao();
    void carregaDados();
    void salvaDados();
    void cadernetaDePoupanca();
    void cartaoCredito();
    void criarCartao();
    void alterarStatusCartao(bool bloquear);
    void alterarLimite();
    void pagamentoParcelado();
    void pagarFatura();

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

    template<typename T>
    T* pesquisaPessoa(const std::vector<T*>& vec, const std::string& prompt) {
        size_t id;
        T* ptr = nullptr;
        while (true) {
            if (!lerEntrada(id, prompt, ": ")) 
                return nullptr;
            ptr = pesquisaID(vec, id);
            if (ptr) 
                return ptr;
            std::cout << BOLD(RED("ID não encontrado. Tente novamente.\n"));
        }
    }
};

#endif