#ifndef PESSOA_H
#define PESSOA_H
#include <string>

class Pessoa{
    std::string nome;
    std::string login;
    std::string senha;
    std::string dataNasc;
    std::string trabalho;
public:

    Pessoa(std::string n="", std::string l="", std::string s="", std::string d="", std::string t="");
    virtual void exibirDados() = 0;

    //---------------------------------
    //getters

    std::string getNome() const;
    std::string getLogin() const;
    std::string getSenha() const;
    std::string getDataNasc() const;
    std::string getTrabalho() const;

    //---------------------------------
    //setters
    void setNome(std::string);    
    void setLogin(std::string);
    void setSenha(std::string);
    void setDataNasc(std::string);
    void setTrabalho(std::string);

    virtual void cadastro() = 0;
};

#endif
