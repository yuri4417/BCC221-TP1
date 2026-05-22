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
    void cadastrarCliente(size_t);
    void cadastrarGerente(size_t);
    void associarGerenteCliente();
    void listarClientes(vector<Cliente*> vecCliente);
    void listarGerentes(vector<Gerente*> vecGerente);
    
    int getQtdCliente() const;
    int getQtdGerente() const;
    
    void setQtdCliente(int qtdCliente);
    void setQtdGerente(int qtdCliente);
};


void clearTerminal();
void imprimirOpcoes();
void criarTransacao();
void exibirExtrato();


void salvarSair();
#endif