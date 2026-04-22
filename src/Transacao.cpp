#include "Transacao.h"
#include "Cliente.h"
#include <iostream>
using namespace std;

//Construtor aplicando boas praticas, e otimizar inicializacao de valores
Transacao::Transacao(string t, double v, string d, string h):
    tipo(t), valor(v), data(d), horario(h) {}


//------------------------------------
//getters

string Transacao::getTipo()                      const { return tipo; } 
double Transacao::getValor()                     const { return valor; } 
string Transacao::getData()                      const { return data; }
string Transacao::getHorario()                   const { return horario; }
const vector<Cliente*>& Transacao::getClientes() const { return clientesEnvolvidos; }

//------------------------------------
//setters

void Transacao :: setTipo(string t){
    tipo = t;
}

void Transacao :: setValor(double x){
    valor = x;
}

void Transacao :: setData(string d){
    data = d;
}

void Transacao :: setHorario(string h){
    horario = h; 
}

void Transacao :: setClientes(Cliente* c){
    clientesEnvolvidos.push_back(c);
}

//-----------------------------------------
//exibir 

void Transacao::exibirTransacao(){
    cout << "Tipo: "    <<  tipo   << endl;
    cout << "Valor: "   <<  valor  << endl;
    cout << "Data: "    <<  data   << endl;
    cout << "Horario: " << horario << endl;
    cout << "Clientes Envolvidos: " << endl;
    for(auto* cliente : clientesEnvolvidos)
        cliente->exibirCliente();
}