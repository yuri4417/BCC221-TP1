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
    
void Gerente :: setCliente(Cliente* c) {
    clientes.push_back(c);
}
 
const vector<Cliente*> Gerente::getClientes() const{
    return clientes;
}

void Gerente:: exibirDados() {
    cout << "===== Dados do Gerente =====" << endl;
    cout << *this << endl; // Usa a sobrecarga do operador << para exibir os dados do gerente
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

void Gerente :: cadastro(){
    string temp;
    clearTerminal();
    cout << " ===== Iniciando Cadastro de Gerente =====" << endl;
    cout << "Digite o nome do Gerente: ";
    getline(cin >> ws, temp);
    this->setNome(temp);

    cout << "Digite a data de nascimento do Gerente (dd/mm/aaaa): ";
    getline(cin >> ws, temp);
    this->setDataNasc(temp);

    cout << "Digite a profissão do Gerente: ";
    getline(cin >> ws, temp);
    this->setTrabalho(temp);

    cout << "Digite o login do Gerente: ";
    getline(cin >> ws, temp);
    this->setLogin(temp);
    //cout << "Gerente Associado: " << cliente->getGerenteAssociadoID() << endl;
    cout << "Digite a senha do Gerente: ";
    getline(cin >> ws, temp);
    this->setSenha(temp);
}

ostream& operator<<( std :: ostream& out , const Gerente& g) {//Sobrecarga
    out << "Nome: " << g.getNome() << endl;
    out << "ID: " << g.getID() << endl;
    out << "Trabalho: " << g.getTrabalho() << endl;
    out << "Qtd de clientes relacionados: " << g.getClientes().size() << endl;
    out << "Clientes relacionados: " << endl;
    for (const auto& cliente : g.getClientes()) {
        out << " - " << cliente->getNome() << " (ID: " << cliente->getID() << ")" << endl;
    }
    return out;
}
// istream& operator >>( std :: istream& in, Cliente& c){//Sobrecarga
//     in >> c.remuneracao >> c.tipoDeConta >> c.taxaDeRendimento >> c.saldo;
//     return in;
// }