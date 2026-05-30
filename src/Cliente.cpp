#include <iostream>
#include <string>
#include "Cliente.h"
#include "menu.h"
using namespace std;

Cliente::Cliente(string nome, string login, string senha, string dataNasc, string trabalho,size_t ID,
                size_t gerenteAssociadoID, double remuneracao, string tipoConta, double taxaRendimento,
                double saldo, const vector<Transacao*>& transacoes,CartaoCredito* cartao):
    Pessoa(nome, login, senha, dataNasc, trabalho) {
    setID(ID);
    setGerenteAssociadoID(gerenteAssociadoID);
    setRemuneracao(remuneracao);
    setTipoDeConta(tipoConta);
    setRendimento(taxaRendimento);
    setSaldo(saldo);
    setTransacao(transacoes);
    setCartao(cartao); 
    }
//-----------------------------------------
//getters
size_t Cliente :: getID() const{
    return ID;
}
size_t Cliente :: getGerenteAssociadoID() const{
    return (gerenteAssociadoID != __INT_MAX__) ? ID : 0; 
}
vector<Transacao*> Cliente :: getTransacoes() const{
    return transacoes;
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
CartaoCredito* Cliente::getCartao() {
    return cartao;
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

void Cliente :: setRemuneracao(double r) {
    remuneracao = r;
}

void Cliente :: setCartao(CartaoCredito* c) {
    cartao = c; 
}

//-----------------------------------------
void Cliente::exibirDados() {
    cout<< "======= Dados do Cliente =======" << endl;
    cout << *this;
    cout << "Dados Privados do Cliente:" << endl;
    cout << "Login: " << getLogin() << endl;
    cout << "Senha: " << getSenha() << endl;
    cout << "===============================" << endl;
}

void Cliente::cadastro() {

    string temp;
    
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

void Cliente::criarCartao() {
    if(cartao != nullptr)
        return;
 
    cartao = new CartaoCredito(0,0,false);

    double limiteInicial = getRemuneracao() * 2.0;

    cartao->setLimite(limiteInicial);
}

//----------------------------------------

ostream& operator <<( std :: ostream& out , const Cliente& c){//Sobrecarga
    out << "Nome: " << c.getNome()  << endl;
    out << "ID: " << c.getID() << endl;
    out << "Remuneração: " << c.getRemuneracao() << endl;
    out << "Tipo de conta: " << c.getTipoDeConta() << endl;
    out << "Taxa de rendimento: " << c.getRendimento() << endl;
    out << "Saldo: " << c.getSaldo() << endl;
    out << "Gerente Associado ID: " << c.getGerenteAssociadoID() << endl;
    return out;
}
/*istream& operator >>( std :: istream& in, Cliente& c){//Sobrecarga
    in >> c.remuneracao >> c.tipoDeConta >> c.taxaDeRendimento >> c.saldo;
    return in;
}*/

void Cliente::pushTransacao(Transacao* t) {//insere nova transação no vetor de transações do cliente
    this->transacoes.push_back(t);
}
void Cliente::rendimento()
{
    if(tipoDeConta == "2")
    {
        saldo += saldo * (taxaDeRendimento /100);
        return;
    }
}
Cliente::~Cliente() {}
