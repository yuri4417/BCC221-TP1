#ifndef CLIENTE_H
#define CLIENTE_H
#include "Pessoa.h"
#include "Transacao.h"
#include <vector>


class Cliente: public Pessoa {
    double remuneracao;
    std::string tipoDeConta;
    double taxaDeRendimento;
    double saldo;
    std::vector<Transacao> transacoes;

public:

//Construtor
    Cliente(double remuneracao = 0, std::string tipoConta = "", double taxaRendimento = 0, double saldo = 0,
        const std::vector<Transacao>& transacoes = {}, std::string login ="", std::string senha ="", 
        std::string dataNasc ="", std::string nome ="", std::string trabalho ="");

        //----------------------------------------
//getters
    const std::vector<Transacao>& getExtrato() const;
    std::string getTipoDeConta() const;
    double getSaldo() const;
    double getRendimento() const;
    double getRemuneracao() const;

//----------------------------------------
//setters
    void setTransacao(const std::vector<Transacao>&);
    void setTipoDeConta(std::string);
    void setSaldo(double);
    void setRendimento(double);
    void setRemuneracao(double);


    void exibirDados();
    void exibirCliente();


//----------------------------------------
    friend std::ostream& operator << (std::ostream&, const Cliente&);
    friend std::istream& operator >> (std::istream&, Cliente&);
};

#endif