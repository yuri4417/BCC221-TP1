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
    Gerente(std::string n="", std::string l="", std::string s="", std::string d="", std::string t="", size_t id=__INT_MAX__);
    const std::vector<Cliente*> getClientes() const;
    void setCliente(Cliente*);
    void exibirDados() override;
    size_t getID() const;
    void setID(size_t);

    virtual bool cadastro();    
    friend std::ostream& operator << (std::ostream&, const Gerente&);


    virtual ~Gerente();
};



#endif