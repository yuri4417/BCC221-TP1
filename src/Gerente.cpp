#include <iostream>
#include <vector>
#include "utils.h"
#include "cores.h"
#include "Gerente.h"
#include "Pessoa.h"
#include "Cliente.h"
#include "Banco.h"
using namespace std;

// Construtor de gerente, primeiro chamando o construtor da classe base e depois setando o ID do gerente
Gerente::Gerente(string n, string l, string s, string d, string t, size_t id):
    Pessoa(n, l, s, d, t) { setID(id);}
    
// Getters
size_t Gerente::getID() const{
    return ID;
}
const vector<Cliente*> Gerente::getClientes() const{
    return clientes;
}

//Setters
bool Gerente::setCliente(Cliente* c) {
    for (auto clienteExistente : clientes) {
        if (clienteExistente->getID() == c->getID()) {
            cout << endl << endl; 
            cout << "Cliente: " << (c->getNome()) << " | "<<"Id: " << c->getID() <<
            " "<< "Já está associado ao gerente: " << getID() << endl; 
            cout << endl << endl;
            confirmar("Pressione ENTER para retornar ao menu...");
            return false;
        }
    }
    clientes.push_back(c);
    return true;
}
void Gerente::setID(size_t id){
    ID = id;
}

// Método para exibir os dados do gerente, incluindo os clientes relacionados e os dados privados
void Gerente::exibirDados() {
    cout << "===== Dados do Gerente =====" << endl;
    cout << "Nome: " << getNome() << endl;
    cout << "ID: " << getID() << endl;
    cout << "Trabalho: " << getTrabalho() << endl;
    cout << "Qtd de clientes relacionados: " << getClientes().size() << endl;
    cout << "Clientes relacionados: " << endl;
    for (const auto& cliente : getClientes()) {
        cout << " - " << cliente->getNome() << " (ID: " << cliente->getID() << ")" << endl;
    }
    cout << "Dados Privados do Gerente:" << endl;
    cout << "Login: " << getLogin() << endl;
    cout << "Senha: " << getSenha() << endl;
    cout << "============================" << endl;
}

// Método para remover um cliente da lista de clientes relacionados ao gerente, utilizando o ID do cliente
void Gerente::removeCliente(size_t idCliente){
    for(auto it = clientes.begin(); it != clientes.end(); ++it){
        if((*it)->getID() == idCliente){
            clientes.erase(it);
            return;
        }
    }
}

// Método para realizar o cadastro de um gerente, solicitando os dados necessários e validando as entradas
bool Gerente::cadastro(){
    clearTerminal();
    cout << BOLD(GREEN(" ===== Iniciando Cadastro de Gerente =====")) << endl;
    string nome;
    string dataNasc;
    string trabalho;
    string login;
    string senha;

    if (!lerEntrada(nome, BOLD("Digite o nome do Gerente"), ": "))
        return false;
    if (!lerEntrada(dataNasc, BOLD("Digite a data de nascimento do Gerente (dd/mm/aaaa)"), ": "))
        return false;
    if (!lerEntrada(trabalho, BOLD("Digite a profissão do Gerente"), ": "))
        return false;
    if (!lerEntrada(login, BOLD("Digite o login do Gerente"), ": "))
        return false;
    if (!lerEntrada(senha, BOLD("Digite a senha do Gerente"), ": "))
        return false;

    this->setNome(nome);
    this->setTrabalho(trabalho);
    this->setLogin(login);
    this->setSenha(senha);
    return true;
}

// Sobrecarga do operador << para exibir os dados do gerente de forma formatada
ostream& operator<<( std :: ostream& out , const Gerente& g) {
    cout << "ID: "<< g.getID()  << " | Nome:" << g.getNome() << endl;
    return out;
}

//Destrutor 
Gerente::~Gerente() {}