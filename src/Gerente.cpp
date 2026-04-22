#include <iostream>
#include <vector>

#include "Gerente.h"
#include "Pessoa.h"
#include "Cliente.h"

using namespace std;

void Gerente :: setCliente(const Cliente& c){
    clientes.push_back(c);
}

<<<<<<< HEAD
vector <Cliente> Gerente :: getClientes(){
    return clientes;
}


void Gerente:: exibirDados(){
    int tam = clientes.size();
    for(int i = 0; i < tam; i++){
        cout << "Remuneração: " << remuneracao << endl;
        cout << "Tipo de conta: " << tipoDeConta << endl;
        cout << "Taxa de rendimento: " << taxaDeRendimento << endl;
        cout << "Saldo: " << saldo << endl;
    }
}

/*ostream& operator <<( std :: ostream& out , const Cliente& c){//Sobrecarga
    out << "Remuneração: " << remuneracao << endl;
    out << "Tipo de conta: " << tipoDeConta << endl;
    out << "Taxa de rendimento: " << taxaDeRendimento << endl;
    out << "Saldo: " << saldo << endl;
=======
const vector<Cliente>& Gerente::getClientes() const{
    return clientes;
}

void Gerente:: exibirDados(){
    cout << "Nome: " << nome << endl;
    cout << "Trabalho: " << trabalho << endl;
    cout << "Qtd de clientes relacionados: " << clientes.size() << endl;
}

/*ostream& operator <<( std :: ostream& out , const Cliente& c){//Sobrecarga
    out << "Remuneração: " << c.remuneracao << endl;
    out << "Tipo de conta: " << c.tipoDeConta << endl;
    out << "Taxa de rendimento: " << c.taxaDeRendimento << endl;
    out << "Saldo: " << c.saldo << endl;
>>>>>>> 5a5ec6a (Correção de erros)
    return out;
}
istream& operator >>( std :: istream& in, Cliente& c){//Sobrecarga
    in >> c.remuneracao >> c.tipoDeConta >> c.taxaDeRendimento >> c.saldo;
    return in;
}*/