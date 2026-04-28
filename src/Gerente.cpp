#include <iostream>
#include <vector>

#include "Gerente.h"
#include "Pessoa.h"
#include "Cliente.h"

using namespace std;

Gerente::Gerente(string n, string l, string s, string d, string t):
     Pessoa(n, l, s, d, t) {}
    

void Gerente :: setCliente(const Cliente& c){
    clientes.push_back(c);
}
 

const vector<Cliente>& Gerente::getClientes() const{
    return clientes;
}

void Gerente:: exibirDados() {
    cout << "Nome: " << getNome() << endl;
    cout << "Trabalho: " << getTrabalho() << endl;
    cout << "Qtd de clientes relacionados: " << clientes.size() << endl;
}

/*ostream& operator <<( std :: ostream& out , const Cliente& c){//Sobrecarga
    out << "Remuneração: " << c.remuneracao << endl;
    out << "Tipo de conta: " << c.tipoDeConta << endl;
    out << "Taxa de rendimento: " << c.taxaDeRendimento << endl;
    out << "Saldo: " << c.saldo << endl;
    return out;
}
istream& operator >>( std :: istream& in, Cliente& c){//Sobrecarga
    in >> c.remuneracao >> c.tipoDeConta >> c.taxaDeRendimento >> c.saldo;
    return in;
}*/