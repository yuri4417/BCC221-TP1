#include "Pessoa.h"
#include <iostream>
using namespace std;

//----------------------------------------------------
//Construtor

Pessoa::Pessoa(string n, string l, string s, string d, string t) {
    setNome(n); setLogin(l); setSenha(s); setDataNasc(d); setTrabalho(t);
}

//------------------------------------------------------
//Setters

void Pessoa::setNome(string n) {
    nome = n;
}
void Pessoa::setTrabalho(string t){
    trabalho = t;
}
void Pessoa::setLogin(string l) {
    login = l;
}
void Pessoa::setSenha(string s) {
    senha = s;
}

void Pessoa::setDataNasc(string d) {
    dataNasc = d;
}

//------------------------------------------------------
//Getters
string Pessoa::getNome() const     { 
    return nome; 
}
string Pessoa::getTrabalho() const { 
    return trabalho; 
}
string Pessoa::getLogin() const    { 
    return login; 
}
string Pessoa::getSenha() const    { 
    return senha; 
}
string Pessoa::getDataNasc() const { 
    return dataNasc; 
}

Pessoa::~Pessoa(){}