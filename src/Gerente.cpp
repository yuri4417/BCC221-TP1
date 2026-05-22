#include <iostream>
#include <vector>

#include "Gerente.h"
#include "Pessoa.h"
#include "Cliente.h"
#include "menu.h"
using namespace std;

Gerente::Gerente(string n, string l, string s, string d, string t):
    Pessoa(n, l, s, d, t) {}
    
void Gerente :: setCliente(Cliente* c) {
    clientes.push_back(c);
}
 
const vector<Cliente*> Gerente::getClientes() const{
    return clientes;
}

void Gerente:: exibirDados() {
    cout << "Nome: " << getNome() << endl;
    cout << "Trabalho: " << getTrabalho() << endl;
    cout << "Qtd de clientes relacionados: " << clientes.size() << endl;
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

ostream& operator <<( std :: ostream& out , const Gerente& g) {//Sobrecarga
    out << "Nome: " << g.getNome() << endl;
    out << "ID: " << g.getID() << endl;
    return out;
}
// istream& operator >>( std :: istream& in, Cliente& c){//Sobrecarga
//     in >> c.remuneracao >> c.tipoDeConta >> c.taxaDeRendimento >> c.saldo;
//     return in;
// }