#include "Pessoa.h"
#include <iostream>
using namespace std;

//----------------------------------------------------
//Construtor
    
Pessoa :: Pessoa(string l = "\0", string s = "\0", string d = "\0"): login(l), senha(s), dataNasc(d){}



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
string Pessoa::getNome() {
    return nome;
}
string Pessoa::getTrabalho(){
    return trabalho;
}
string Pessoa::getLogin(){
    return login;
}
string Pessoa::getSenha(){
    return senha;
}




   