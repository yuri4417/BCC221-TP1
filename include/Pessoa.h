#ifndef PESSOA_H
#define PESSOA_H
#include <string>

class Pessoa{
    //Atributos privados
    std::string nome;
    std::string login;
    std::string senha;
    std::string dataNasc;
    std::string trabalho;
public:
    //Construtor
    Pessoa(std::string n="", std::string l="", std::string s="", std::string d="", std::string t="");

    //getters
    std::string getNome() const;
    std::string getLogin() const;
    std::string getSenha() const;
    std::string getDataNasc() const;
    std::string getTrabalho() const;

    //setters
    void setNome(std::string);    
    void setLogin(std::string);
    void setSenha(std::string);
    void setDataNasc(std::string);
    void setTrabalho(std::string);

    //Métodos virtuais puros
    virtual void exibirDados() = 0;
    virtual bool cadastro() = 0;

    //Destrutor
    virtual ~Pessoa();
};

#endif
