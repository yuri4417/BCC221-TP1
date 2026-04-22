#include "Pessoa.h"
#include <iostream>
using namespace std;

//----------------------------------------------------
//Construtor
    
Pessoa::Pessoa(string l, string s, string d) : login(l), senha(s), dataNasc(d) {}



void Pessoa::exibirDados(){
    cout << "Nome: " << nome << endl;
    cout << "Trabalho: " << trabalho << endl;
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
    while (l.length() == 0) {
        cout << "Login Vazio! Digite novamente: ";
        cin >> l;
    }
    login = l;
}
void Pessoa::setSenha(string s) {
    while (s.length() == 0) {
        cout << "Senha Vazia! Digite novamente: ";
        cin >> s;
    }
    senha = s;
}

void Pessoa::setDataNasc(string d) {
    while (d.length() == 0) {
        cout << "Data de Nascimento Vazia! Digite novamente: ";
        cin >> d;
    }
    dataNasc = d;
}

//------------------------------------------------------
//Getters
string Pessoa::getNome() const     { return nome; }
string Pessoa::getTrabalho() const { return trabalho; }
string Pessoa::getLogin() const    { return login; }
string Pessoa::getSenha() const    { return senha; }
string Pessoa::getDataNasc() const { return dataNasc; }


   