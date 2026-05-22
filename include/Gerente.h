#ifndef GERENTE_H
#define GERENTE_H
#include <vector>
#include <string>
#include "Pessoa.h"

class Cliente;

class Gerente : public Pessoa {
    size_t ID;
    std::vector<Cliente*> clientes;
public:
    Gerente(std::string n="", std::string l="", std::string s="", std::string d="", std::string t="");
    const std::vector<Cliente*> getClientes() const;
    void setCliente(Cliente*);
    void exibirDados() override;
    size_t getID() const;
    void setID(size_t);

    virtual void cadastro();    
};



#endif