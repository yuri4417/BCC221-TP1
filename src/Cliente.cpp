#include <iostream>
#include "Cliente.h"

using namespace std;

//-----------------------------------------
//getters

int Cliente :: getCliente() const{
    // Voltar aqui
    return 0;
}
string Cliente :: getTipoDeConta() const{
    return tipoDeConta;
}
double Cliente :: getSaldo() const{
    return saldo;
}
double Cliente :: getRendimento() const{
    return taxaDeRendimento;
}
const vector<Transacao>& Cliente :: getExtrato() const{
    return transacoes;
}
double Cliente:: getRemuneracao() const{
    return remuneracao;
}

//-----------------------------------------
//setters
<<<<<<< HEAD
=======
// Adicionar ao vetor de transacoes?
>>>>>>> 5a5ec6a (Correção de erros)
void Cliente :: setTransacao(const vector<Transacao>& t) {
    transacoes = t;
}
void Cliente :: setCliente(const Pessoa& p) {//setCliente preenche os atributos de Pessoa
<<<<<<< HEAD
    
=======
>>>>>>> 5a5ec6a (Correção de erros)
    setNome(p.getNome());
    setTrabalho(p.getTrabalho());
    setLogin(p.getLogin());
    setSenha(p.getSenha());
}
void Cliente :: setTipoDeConta(string tipo) {
    tipoDeConta = tipo;
}
void Cliente :: setSaldo(double s) {
    saldo = s;
}
void Cliente :: setRendimento(double t) {
    taxaDeRendimento = t;
}

void Cliente:: setRemuneracao(double r) {
    remuneracao = r;
}

//-----------------------------------------
void Cliente :: exibirDados() {
    cout<< "Remuneração: " << remuneracao << endl;
    cout<< "Tipo de conta: " << tipoDeConta << endl;
    cout<< "Taxa de rendimento: " << taxaDeRendimento << endl;
    cout<< "Saldo: " << saldo << endl;
}

void Cliente::exibirCliente(){
    cout << "Nome: " << nome << endl;
}

//----------------------------------------

ostream& operator <<( std :: ostream& out , const Cliente& c){//Sobrecarga
<<<<<<< HEAD
    out << "Remuneração: " << remuneracao << endl;
    out << "Tipo de conta: " << tipoDeConta << endl;
    out << "Taxa de rendimento: " << taxaDeRendimento << endl;
    out << "Saldo: " << saldo << endl;
=======
    out << "Remuneração: " << c.remuneracao << endl;
    out << "Tipo de conta: " << c.tipoDeConta << endl;
    out << "Taxa de rendimento: " << c.taxaDeRendimento << endl;
    out << "Saldo: " << c.saldo << endl;
>>>>>>> 5a5ec6a (Correção de erros)
    return out;
}
/*istream& operator >>( std :: istream& in, Cliente& c){//Sobrecarga
    in >> c.remuneracao >> c.tipoDeConta >> c.taxaDeRendimento >> c.saldo;
    return in;
}*/