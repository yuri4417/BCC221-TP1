#ifndef GERENTE_H
#define GERENTE_H
#include <vector>
#include "Pessoa.h"

class Cliente;

class Gerente : public Pessoa {
    std::vector<Cliente> clientes;

public:
    Gerente();
<<<<<<< HEAD
    const std::vector<Cliente&> getClientes() const;
=======
    const std::vector<Cliente>& getClientes() const;
>>>>>>> 5a5ec6a (Correção de erros)
    void setCliente(const Cliente&);
    void exibirDados();

};



#endif