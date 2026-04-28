#ifndef GERENTE_H
#define GERENTE_H
#include <vector>
#include <string>
#include "Pessoa.h"

class Cliente;

class Gerente : public Pessoa {
    std::vector<Cliente> clientes;

public:
    Gerente(std::string n="", std::string l="", std::string s="", std::string d="", std::string t="");
    const std::vector<Cliente>& getClientes() const;
    void setCliente(const Cliente&);
    void exibirDados();

};



#endif