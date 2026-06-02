#ifndef GERENTE_H
#define GERENTE_H
#include <vector>
#include <string>
#include "Pessoa.h"

class Cliente;

class Gerente : public Pessoa {
    // Atributos privados
    size_t ID;
    std::vector<Cliente*> clientes;
public:
    // Construtor
    Gerente(std::string n="", std::string l="", std::string s="", std::string d="", std::string t="", size_t id=__INT_MAX__);
    //Destrutor
    virtual ~Gerente();

    // Getters
    size_t getID() const;
    const std::vector<Cliente*> getClientes() const;
    
    // Setters
    bool setCliente(Cliente*);
    void setID(size_t);
    
    // Métodos de gerenciamento de clientes
    void exibirDados() override;
    void removeCliente(size_t idCliente);
    virtual bool cadastro();   
    
    // Sobrecarga do operador << para exibir os dados do gerente
    friend std::ostream& operator << (std::ostream&, const Gerente&);
};



#endif