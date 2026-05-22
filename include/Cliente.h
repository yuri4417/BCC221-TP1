#ifndef CLIENTE_H
#define CLIENTE_H
#include "Pessoa.h"
#include "Transacao.h"
#include <vector>

class Cliente: public Pessoa {
    size_t ID;
    size_t gerenteAssociadoID;
    double remuneracao;
    std::string tipoDeConta;
    double taxaDeRendimento;
    double saldo;
    std::vector<Transacao*> transacoes;

public:

//Construtor
    Cliente(std::string nome ="", std::string login ="", std::string senha ="", std::string dataNasc ="", std::string trabalho ="",
            size_t ID = 0,size_t gerenteAssociadoID = __INT_MAX__, double remuneracao = 0, std::string tipoConta = "", double taxaRendimento = 0,
            double saldo = 0, const std::vector<Transacao*>& transacoes = {});

        //----------------------------------------
//getters
    const std::vector<Transacao*>& getExtrato() const;
    std::string getTipoDeConta() const;
    double getSaldo() const;
    double getRendimento() const;
    double getRemuneracao() const;
    size_t getID() const;
    size_t getGerenteAssociadoID() const;

//----------------------------------------
//setters
    void setTransacao(const std::vector<Transacao*>&);
    void setTipoDeConta(std::string);
    void setSaldo(double);
    void setRendimento(double);
    void setRemuneracao(double);
    void setID(size_t);
    void setGerenteAssociadoID(size_t);
    void exibirDados() override;
    void exibirCliente();


    virtual void cadastro();


//----------------------------------------
    friend std::ostream& operator << (std::ostream&, const Cliente&);
    friend std::istream& operator >> (std::istream&, Cliente&);
};

#endif