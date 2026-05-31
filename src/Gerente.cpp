#include <iostream>
#include <vector>
#include "utils.h"
#include "Gerente.h"
#include "Pessoa.h"
#include "Cliente.h"
#include "menu.h"
using namespace std;

Gerente::Gerente(string n, string l, string s, string d, string t, size_t id):
    Pessoa(n, l, s, d, t) { ID = id;}
    
Gerente::~Gerente() {}

void Gerente::setCliente(Cliente* c) {
    clientes.push_back(c);
}
 
const vector<Cliente*> Gerente::getClientes() const{
    return clientes;
}

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

size_t Gerente::getID() const{
    return ID;
}
void Gerente::setID(size_t id){
    ID = id;
}

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

ostream& operator<<( std :: ostream& out , const Gerente& g) {//Sobrecarga
    cout << "ID: "<< g.getID()  << " | Nome:" << g.getNome() << endl;
    return out;
}
// istream& operator >>( std :: istream& in, Cliente& c){//Sobrecarga
//     in >> c.remuneracao >> c.tipoDeConta >> c.taxaDeRendimento >> c.saldo;
//     return in;
// }