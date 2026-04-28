#include <iostream>
#include "Cliente.h"
using namespace std;


Cliente::Cliente(double remuneracao, string tipoConta, double taxaRendimento,
                double saldo, const vector<Transacao>& transacoes, string login,
                string senha, string dataNasc, string nome, string trabalho):
    Pessoa::Pessoa(nome, login, senha, dataNasc,trabalho){
    setRemuneracao(remuneracao);
    setTipoDeConta(tipoConta);
    setRendimento(taxaRendimento);
    setSaldo(saldo);
    setTransacao(transacoes);
    }
//-----------------------------------------
//getters

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
void Cliente :: setTransacao(const vector<Transacao>& t) {
    transacoes = t;
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
    cout << "Nome: " << getNome() << endl;
}

//----------------------------------------

ostream& operator <<( std :: ostream& out , const Cliente& c){//Sobrecarga
    out << "Remuneração: " << c.remuneracao << endl;
    out << "Tipo de conta: " << c.tipoDeConta << endl;
    out << "Taxa de rendimento: " << c.taxaDeRendimento << endl;
    out << "Saldo: " << c.saldo << endl;
    return out;
}
/*istream& operator >>( std :: istream& in, Cliente& c){//Sobrecarga
    in >> c.remuneracao >> c.tipoDeConta >> c.taxaDeRendimento >> c.saldo;
    return in;
}*/