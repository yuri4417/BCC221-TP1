#ifndef CLIENTE_H
#define CLIENTE_H
#include "Pessoa.h"
#include "Transacao.h"
#include <vector>


class Cliente : public Pessoa {
    double remuneracao;
    std::string tipoDeConta;
    double taxaDeRendimento;
    double saldo;
    std::vector<Transacao> transacoes;

public:


//----------------------------------------
//getters
    int getCliente() const;
    const std::vector<Transacao>& getExtrato() const;
    std::string getTipoDeConta() const;
    double getSaldo() const;
    double getRendimento() const;
    double getRemuneracao() const;

//----------------------------------------
//setters
    void setCliente(const Pessoa&);
    void setTransacao(const Transacao&);
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