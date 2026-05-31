#ifndef CARTAOCREDITO_H
#define CARTAOCREDITO_H
#include <iostream>
#include "Cliente.h"

class CartaoCredito {
private:
    size_t numero;
    std::string senha;
    double limite;
    double faturaAtual;
    bool bloqueado;
    Cliente* cliente;

public:
    CartaoCredito(unsigned long long = 0, std::string senha = "", double = 0.0, double = 0.0, bool = true, Cliente* = nullptr);

    unsigned long long getNumero() const;
    std::string getSenha() const;
    double getLimite() const;
    double getFatura() const;
    bool getBloqueado() const;
    Cliente* getCliente() const;
    
    void setNumero(unsigned long long);
    void setSenha(std::string);
    void setLimite(double);
    void setFatura(double);
    void setBloqueado(bool);
    void associarCliente(Cliente*);

    void bloquear();
    void desbloquear();

    int calcularDigitoVerificador(const std::string&);
    unsigned long long gerarNumeroCartao(size_t id);

    bool realizarCompra(double);
    bool pagarFatura(double);
    virtual ~CartaoCredito();

    void exibirMenu();

    friend std::ostream& operator << (std::ostream&, const CartaoCredito&);
};
#endif