#include <iostream>
#include <string>
#include "Cliente.h"
#include "Banco.h"
#include "utils.h"
using namespace std;

// Construtor de cliente, primeiro chamando o construtor da classe base, depois inicializando os atributos específicos de Cliente 
Cliente::Cliente(string nome, string login, string senha, string dataNasc, string trabalho,size_t ID,
                 size_t gerenteAssociadoID, double remuneracao, string tipoConta, double taxaRendimento,
                 double saldo, const vector<Transacao*>& transacoes,CartaoCredito* cartao):
                 Pessoa(nome, login, senha, dataNasc, trabalho), cartao(nullptr) {
                     setID(ID);
                     setGerenteAssociadoID(gerenteAssociadoID);
                     setRemuneracao(remuneracao);
                     setTipoDeConta(tipoConta);
                     setRendimento(taxaRendimento);
                     setSaldo(saldo);
                     setTransacao(transacoes);
                     setCartao(cartao);
                 }
// Destrutor
Cliente::~Cliente() {
    delete cartao;
}



//getters
size_t Cliente :: getID() const{
    return ID;
}
size_t Cliente :: getGerenteAssociadoID() const{
    return (gerenteAssociadoID != __INT_MAX__) ? gerenteAssociadoID : 0; 
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
    if (cartao != nullptr)
        delete cartao;
    cartao = c; 
}

// Metodo para exibir os dados do cliente, incluindo informações pessoais, detalhes da conta e status do cartão de crédito
void Cliente::exibirDados() {
    cout<< BOLD(GREEN("======= Dados do Cliente =======")) << endl;
    cout << BOLD("Nome: ") << getNome()  << endl;
    cout << BOLD(YELLOW("ID: ")) << getID() << endl;
    cout << BOLD(GREEN("Remuneração: ")) << printDinheiro(getRemuneracao()) << endl;
    cout << BOLD("Tipo de conta: ") << getTipoDeConta() << endl;
    cout << BOLD("Taxa de rendimento: ") << getRendimento() << endl;
    cout << BOLD("Saldo: ") << getSaldo() << endl;
    cout << BOLD(BLUE("Gerente Associado ID: ")) << getGerenteAssociadoID() << endl;
    cout << BOLD("Cartão de Crédito: ");
    CartaoCredito* cc = getCartao();
    if(cc == nullptr)
        cout << BOLD(RED("Cliente não possui cartão de crédito")) << endl;
    else{
        cout << BOLD(to_string(cc->getNumero()));
        if(cc->getBloqueado() == false)
            cout << BOLD(GREEN(" (Ativo)")) << endl;
        else
            cout << BOLD(RED(" (Inativo)")) << endl;
        cout << endl;
    }
    cout << BOLD(RED("===============================")) << endl;
    cout << BOLD(RED("Dados Privados do Cliente:")) << endl;
    cout << BOLD("Login: ") << getLogin() << endl;
    cout << BOLD("Senha: ") << getSenha() << endl;
    cout << BOLD(RED("===============================")) << endl;
}

// Metodo para realizar o cadastro de um cliente, solicitando informações ao usuário e validando as entradas
bool Cliente::cadastro() {
    clearTerminal();
    cout << BOLD(GREEN(" ===== Iniciando Cadastro de Cliente =====")) << endl;
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
    if (!lerEntrada(salario, BOLD("Digite o salário do cliente"), ": "))
        return false;

    cout << BOLD(GREEN("Escolha uma modalidade de conta: ")) << endl;
    cout << BOLD("1. Conta Corrente") << endl;
    cout << BOLD("2. Conta Poupança") << endl;
    while (1) {
        if (!lerEntrada(tipoConta, BOLD("Escolha uma opção"), ": "))
            return false;
        if (tipoConta >= 1 && tipoConta <= 2)
            break;
        cout << BOLD(RED("Opcao inválida. Tente novamente: "));
    }
    

    if (tipoConta == 2) {
        if(salario < 10000)
            taxa = 5; // rende 5%
        else if(salario < 50000)
            taxa = 7; // rende 7%
        else
            taxa = 10; // rende 10%
        cout << BOLD(WHITE("Taxa de rendimento do cliente: " + nome + " = " + to_string(taxa) + "%")) << endl;
    }
    
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

// Metodo para criar um cartão de crédito para o cliente, definindo um limite inicial com base na remuneração do cliente
void Cliente::criarCartao() {
    
    cartao = new(nothrow) CartaoCredito;
    
    if(cartao != nullptr)
        return;

    double limiteInicial = getRemuneracao() * 2.0;

    cartao->setLimite(limiteInicial);
}

// Metodo para inserir nova transação no vetor de transações do cliente
void Cliente::pushTransacao(Transacao* t) {
    this->transacoes.push_back(t);
}

// Metodo para calcular o rendimento da conta do cliente, aplicando a taxa de rendimento ao saldo atual se a conta for do tipo "Poupanca"
void Cliente::rendimento()
{
    if(tipoDeConta == "Poupanca")
    {
        saldo += saldo * (taxaDeRendimento /100.0);
        return;
    }
}

// Sobrecarga do operador << para exibir as informações do cliente de forma formatada
ostream& operator <<( std :: ostream& out , const Cliente& c){//Sobrecarga
    cout << BOLD("ID: " + to_string(c.getID()) + " | Nome: " + c.getNome()) << endl; 
    return out;
}

