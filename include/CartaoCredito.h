#ifndef CARTAOCREDITO_H
#define CARTAOCREDITO_H
#include <iostream>
#include "Cliente.h"

class CartaoCredito {
private:
    double limite;
    double faturaAtual;
    bool bloqueado;
    Cliente* cliente;

public:
    CartaoCredito(double = 0.0, double = 0.0,bool = true, Cliente* = nullptr);

    double getLimite() const;
    double getFatura() const;
    bool getBloqueado() const;
    Cliente* getCliente() const;
    

    void setLimite(double);
    void setFatura(double);
    void setBloqueado(bool);
    void associarCliente(Cliente*);

    void listarCartao();
    void alterarLimite();
    void pagamentoParcelado();
    void pagarFatura();
    void bloquear();
    void desbloquear();
    

    bool realizarCompra(double);
    bool pagarFatura(double);
    ~CartaoCredito();

    void exibirMenu();
};
#endif