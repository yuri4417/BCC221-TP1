#include <iostream>
#include <string>
#include "Cliente.h"
#include "menu.h"
#include "utils.h"
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
CartaoCredito* Cliente::getCartao() const{
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
    cout << "Nome: " << getNome()  << endl;
    cout << "ID: " << getID() << endl;
    cout << "Remuneração: " << getRemuneracao() << endl;
    cout << "Tipo de conta: " << getTipoDeConta() << endl;
    cout << "Taxa de rendimento: " << getRendimento() << endl;
    cout << "Saldo: " << getSaldo() << endl;
    cout << "Gerente Associado ID: " << getGerenteAssociadoID() << endl;
    cout << "Cartão de Crédito: ";
    CartaoCredito* cc = getCartao();
    if(cc == nullptr)
        cout << "Cliente não possui cartão de crédito" << endl;
    else{
        cout << cc->getNumero();
        if(cc->getBloqueado() == false)
            cout << " (Ativo)" << endl;
        else
            cout << " (Inativo)" << endl;
        cout << endl;
    }
    cout << "===============================" << endl;
    cout << "Dados Privados do Cliente:" << endl;
    cout << "Login: " << getLogin() << endl;
    cout << "Senha: " << getSenha() << endl;
    cout << "===============================" << endl;
}

bool Cliente::cadastro() {
    clearTerminal();
    cout << " ===== Iniciando Cadastro de Cliente =====" << endl;
    string nome;
    string dataNasc;
    string profissao;
    float salario;
    int tipoConta;
    float taxa;
    string login;
    string senha;
    

    if (!lerEntrada(nome, BOLD("Digite o nome do cliente"), ": "))
        return false;

    if (!lerEntrada(dataNasc, BOLD("Digite a data de nascimento do cliente (dd/mm/aaaa)"), ": "))
        return false;

    if (!lerEntrada(profissao, BOLD("Digite a profissão do cliente"), ": "))
        return false;

    if (!lerEntrada(salario, BOLD("Digite o salario do cliente"), ": "))
        return false;

    cout << "Escolha uma modalidade de conta: " << endl;
    cout << "1. Conta Corrente" << endl;
    cout << "2. Conta Poupança" << endl;
    while (1) {
        if (!lerEntrada(tipoConta, BOLD("Escolha uma opção"), ": "))
            return false;
        if (tipoConta >= 1 && tipoConta <= 2)
            break;
        cout << BOLD(RED("Opcao invalida. Tente novamente: "));
    }
    

    if (tipoConta == 2) 
        if (!lerEntrada(taxa, BOLD("Digite a taxa (%) de rendimento da conta poupança"), ": "))
            return false;
    
    if (!lerEntrada(login, BOLD("Digite o login do cliente"), ": "))
        return false;
    if (!lerEntrada(senha, BOLD("Digite a senha do cliente"), ": "))
        return false;

    this->setNome(nome);
    this->setDataNasc(dataNasc);
    this->setTrabalho(profissao);
    this->setRemuneracao(salario);
    if (tipoConta == 1) 
        this->setTipoDeConta("Corrente");
    else 
        this->setTipoDeConta("Poupanca");
    this->setRendimento(tipoConta == 2 ? taxa : 0);
    this->setLogin(login);
    this->setSenha(senha);
    return true;
}

void Cliente::criarCartao() {
    if(cartao != nullptr)
        return;
 
    cartao = new CartaoCredito(0, "", 0, 0, false, nullptr);

    double limiteInicial = getRemuneracao() * 2.0;

    cartao->setLimite(limiteInicial);
}

//----------------------------------------

ostream& operator <<( std :: ostream& out , const Cliente& c){//Sobrecarga
    cout << "ID: "<< c.getID()  << " | Nome:" << c.getNome() << endl;
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
    if(tipoDeConta == "Poupanca")
    {
        saldo += saldo * (taxaDeRendimento /100);
        return;
    }
}
Cliente::~Cliente() {}
