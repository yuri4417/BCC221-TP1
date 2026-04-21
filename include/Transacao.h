#ifndef TRANSACAO_H
#define TRANSACAO_H

#include <string>
#include <vector>

class Cliente;

class Transacao{
    std::string tipo;
    double valor;
    std::string data;
    std::string horario;
    std::vector<Cliente*> clientesEnvolvidos;    
public:
    //Construtor
    Transacao(std::string, double, std::string, std::string);
    
    //getters
    std::string getTipo() const; 
    double getValor() const;
    std::string getData() const;
    std::string getHorario() const;
    const std::vector<Cliente*>& getClientes() const;
    
    //setters
    void setTipo(std::string);
    void setValor(double);
    void setData(std::string);
    void setHorario(std::string);
    void setClientes(Cliente);
    //exibir
    void exibirTransacao();
};
#endif
