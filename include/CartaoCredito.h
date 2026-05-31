#ifndef CARTAOCREDITO_H
#define CARTAOCREDITO_H
#include <iostream>
#include "Cliente.h"

#define MAXPARCELAS 18

class CartaoCredito {
    // Atributos privados
    size_t numero;
    std::string senha;
    double limite;
    std::vector<double> faturas;
    bool bloqueado;
    Cliente* cliente;
    double disponivel;

public:
    //Construtor
    CartaoCredito(unsigned long long = 0, std::string = "", double = 0.0, std::vector<double> = {}, bool = false, Cliente* = nullptr, double = 0);

    //Getters
    unsigned long long getNumero() const;
    std::string getSenha() const;
    double getLimite() const;
    std:: vector<double> getFaturas() const;
    bool getBloqueado() const;
    Cliente* getCliente() const;
    double getDisponivel() const;
    double getFatura(int = 0) const;
    
    // Setters
    void setNumero(unsigned long long);
    void setSenha(std::string);
    void setLimite(double);
    void setFatura(double, int);
    void setBloqueado(bool);
    void associarCliente(Cliente*);
    void setDisponivel(double);

    // Métodos para operações do cartão de crédito
    void bloquear();
    void desbloquear();
    int calcularDigitoVerificador(const std::string&);
    unsigned long long gerarNumeroCartao(size_t);
    bool realizarCompra(double);
    void pagarFaturaAtual(double);
    void exibirMenu();
    void insereFaturas(double, int);
    // Sobrecarga do operador << para exibir informações do cartão
    friend std::ostream& operator << (std::ostream&, const CartaoCredito&);
    
    //Destrutor
    virtual ~CartaoCredito();
};
#endif