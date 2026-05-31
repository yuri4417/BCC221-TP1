#ifndef TRANSACAO_H
#define TRANSACAO_H

#include <string>
#include <vector>

class Cliente;

class Transacao{
    int tipo; // 1 -> transferência; 2 -> depósito; 3 -> saque
    double valor;
    std::string data;
    std::string horario;
    std::vector<Cliente*> clientesEnvolvidos;
public:
    //Construtor
    Transacao(int t = -1, double v = 0.0, std::string d= "", std::string h = "");
    
    //getters
    int getTipo() const; 
    double getValor() const;
    std::string getData() const;
    std::string getHorario() const;
    const std::vector<Cliente*>& getClientes() const;
    
    //setters
    void setTipo(int);
    void setValor(double);
    void setData(std::string);
    void setHorario(std::string);
    void setClientes(std::vector <Cliente*> vecCliente);
    void exibirTransacao();

    //Transações
    //bool transacoes();
    void pushClienteEnvolvido(Cliente* cli);
    bool acao(Cliente* cliente, double valor);
    bool acao(std::vector<Cliente*> b, double valor);
    ~Transacao();
};
#endif
