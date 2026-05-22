#include <iostream>
#include "Cliente.h"
#include "menu.h"
using namespace std;

Cliente::Cliente(string nome, string login, string senha, string dataNasc, string trabalho,size_t ID,
                size_t gerenteAssociadoID, double remuneracao, string tipoConta, double taxaRendimento,
                double saldo, const vector<Transacao*>& transacoes):
    Pessoa(nome, login, senha, dataNasc, trabalho) {
    setID(ID);
    setGerenteAssociadoID(gerenteAssociadoID);
    setRemuneracao(remuneracao);
    setTipoDeConta(tipoConta);
    setRendimento(taxaRendimento);
    setSaldo(saldo);
    setTransacao(transacoes);
    }
//-----------------------------------------
//getters
size_t Cliente :: getID() const{
    return ID;
}
size_t Cliente :: getGerenteAssociadoID() const{
    return (gerenteAssociadoID != __INT_MAX__) ? ID : 0; 
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
const vector<Transacao*>& Cliente :: getExtrato() const{
    return transacoes;
}
double Cliente:: getRemuneracao() const{
    return remuneracao;
}

//-----------------------------------------
//setters
void Cliente :: setID(size_t id) {
    ID = id;
}
void Cliente :: setGerenteAssociadoID(size_t idAssociado) {
    gerenteAssociadoID = idAssociado;
}
void Cliente :: setTransacao(const vector<Transacao*>& t) {
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
void Cliente::exibirDados() {
    cout<< "Remuneração: " << remuneracao << endl;
    cout<< "Tipo de conta: " << tipoDeConta << endl;
    cout<< "Taxa de rendimento: " << taxaDeRendimento << endl;
    cout<< "Saldo: " << saldo << endl;
}

void Cliente::exibirCliente(){
    cout << "Nome: " << getNome() << endl;
}

void Cliente :: cadastro() {

    string temp;
    clearTerminal();
    cout << endl;
    cout << " ===== Iniciando Cadastro de Cliente =====" << endl << endl;
    cout << "Digite o nome do cliente: ";
    getline(cin >> ws, temp);
    this->setNome(temp);

    cout << "Digite a data de nascimento do cliente (dd/mm/aaaa): ";
    getline(cin >> ws, temp);
    this->setDataNasc(temp);

    cout << "Digite a profissão do cliente: ";
    getline(cin >> ws, temp);
    this->setTrabalho(temp);

    float salario;
    cout << "Digite o salario do cliente: ";
    cin >> salario;
    int opt;
    cout << "Escolha uma modalidade de conta: " << endl;
    cout << "1. Conta Corrente" << endl;
    cout << "2. Conta Poupança" << endl;
    cout << "Escolha uma opção: ";
    while (!(cin >> opt) || opt < 1 || opt > 2) {
        cout << "Opcao invalida. Tente novamente: ";
        cin.clear();
        cin >> opt;
        cin.ignore(1000, '\n');
    }
    if (opt == 1) 
        this->setTipoDeConta("Corrente");
    else 
        this->setTipoDeConta("Poupanca");

    if (opt == 2) {
        float taxa;
        cout << "Digite a taxa (%) de rendimento da conta poupança: ";
        cin >> taxa;
        this->setRendimento(taxa);
    }

    cout << "Digite o login do cliente: ";
    getline(cin >> ws, temp);
    this->setLogin(temp);

    cout << "Digite a senha do cliente: ";
    getline(cin >> ws, temp);
    this->setSenha(temp);    

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