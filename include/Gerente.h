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
    
    // Getters
    const std::vector<Cliente*> getClientes() const;
    size_t getID() const;
    void setID(size_t);

    // Setters
    bool setCliente(Cliente*);
    void exibirDados() override;
    
    // Métodos de gerenciamento de clientes
    void removeCliente(size_t idCliente);
    virtual bool cadastro();   
    
    // Sobrecarga do operador << para exibir os dados do gerente
    friend std::ostream& operator << (std::ostream&, const Gerente&);

    //Destrutor
    virtual ~Gerente();
};



#endif