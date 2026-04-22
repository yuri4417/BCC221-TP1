#ifndef PESSOA_H
#define PESSOA_H
#include <string>
class Pessoa{
    std::string login;
    std::string senha;
    std::string dataNasc;
    
public:

    Pessoa(std::string l = "", std::string s = "", std::string d = "");

    std::string nome;
    std::string trabalho;

    void exibirDados();

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
};

#endif
#ifndef PESSOA_H
#define PESSOA_H
#include <string>
class Pessoa{
    std::string login;
    std::string senha;
    std::string dataNasc;
    
public:

    Pessoa(std::string, std::string, std::string);

    std::string nome;
    std::string trabalho;

    void exibirDados();

    //---------------------------------
    //getters

    std::string getNome();
    std::string getLogin();
    std::string getSenha();
    std::string getDataNasc();
    std::string getTrabalho();

    //---------------------------------
    //setters

    void setNome(std::string);    
    void setLogin(std::string);
    void setSenha(std::string);
    void setDataNasc(std::string);
    void setTrabalho(std::string);
};

#endif