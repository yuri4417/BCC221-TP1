#ifndef TRANSACAO_H
#define TRANSACAO_H

#include <string>
#include <vector>
// Forward declaration para evitar dependências circulares
class Cliente;

class Transacao{
    //Atributos privados
    int tipo; // 1 -> transferência; 2 -> depósito; 3 -> saque
    double valor;
    std::string data;
    std::string horario;
    std::vector<Cliente*> clientesEnvolvidos;
public:
    //Construtor
    Transacao(int t = -1, double v = 0.0, std::string d= "", std::string h = "");
    //Destrutor
    virtual ~Transacao();

    
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
    
    // Métodos para exibir
    void exibirTransacao();
    
    //Transações
    void pushClienteEnvolvido(Cliente* cli);
    bool acao(Cliente* cliente, double valor);
    bool acao(std::vector<Cliente*> b, double valor);
    bool transferenciaCredito(std::vector<Cliente*> clientes, double valor);

};
#endif
