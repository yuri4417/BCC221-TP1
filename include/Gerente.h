#ifndef GERENTE_H
#define GERENTE_H
#include <vector>
#include "Pessoa.h"

class Cliente;

class Gerente : public Pessoa {
    std::vector<Cliente> clientes;

public:
    Gerente();
    const std::vector<Cliente&> getClientes() const;
    void setCliente(const Cliente&);
    void exibirDados();

};



#endif