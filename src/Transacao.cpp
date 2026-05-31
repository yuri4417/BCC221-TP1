#include "Transacao.h"
#include "Cliente.h"
#include <iostream>
class Transacao;
using namespace std;

Transacao::Transacao(int t, double v, string d, string h)
{
    setTipo(t);
    setValor(v);
    setData(d);
    setHorario(h);
}
//------------------------------------
//getters
int Transacao::getTipo() const { 
    return tipo; 
} 
double Transacao::getValor() const { 
    return valor; 
} 
string Transacao::getData() const { 
    return data; 
}
string Transacao::getHorario() const { 
    return horario; 
}
const vector<Cliente*>& Transacao::getClientes() const { 
    return clientesEnvolvidos; 
}

//------------------------------------
//setters
void Transacao :: setTipo(int t){
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
void Transacao :: setClientes(vector <Cliente*> vecCliente){
    clientesEnvolvidos = vecCliente;
}

//-----------------------------------------
//exibir 

void Transacao::exibirTransacao(){
    cout << "Tipo: "    <<  tipo   << endl;
    cout << "Valor: "   <<  valor  << endl;
    cout << "Data: "    <<  data   << endl;
    cout << "Horario: " << horario << endl;
    cout << "Clientes Envolvidos: " << endl;
    for(auto cliente : clientesEnvolvidos)
        cout << "Nome: " << cliente->getNome() << endl;
}

/*
bool Transacao :: transacoes(){
    if(tipo == 1){//priemira posição do vetor clientes é o remetente, as demais são os destinatários
        return acao(clientesEnvolvidos, valor);
    } else if(tipo == 2){
        return acao(clientesEnvolvidos[0], valor);
    } else if(tipo == 3){       
        return acao(clientesEnvolvidos[0], (-1) * valor);
    }
}*/
       

void Transacao::pushClienteEnvolvido(Cliente* cli) {
    this->clientesEnvolvidos.push_back(cli);
}
bool Transacao :: acao(Cliente *cliente, double valor){ //Depósito e saque
    if (valor == 0){
        cout << "Valor inválido..." << endl;
        return false;
    }
    if(valor < 0){//Saque
        if(-valor > cliente->getSaldo()){
            cout << "Saldo insuficiente" << endl;
            return false;
        }
        else{
            cout << "Saque Concluído..." << endl;
        }
    }
    else{//Depósito
        cout<< "Depósito Concluído..." <<endl;
    }
    cliente->setSaldo(cliente->getSaldo() + valor);
    return true;
}

bool Transacao :: acao(vector <Cliente*> clientes, double valor){ //Transferência ("valor" se refere à quantia que cada cliente receberá)
    if(valor * (clientes.size() - 1) > clientes[0]->getSaldo()){
        cout << "Saldo Insuficiente...\n";
        return false;
    }
    for (auto it = clientes.begin() + 1; it != clientes.end(); ++it) {//primeira posição do vetor clientes é o remetente, as demais são os destinatários

        (*it)->setSaldo((*it)->getSaldo() + valor);
        clientes[0]->setSaldo(clientes[0]->getSaldo() - valor);
    }
    return true;
}

Transacao::~Transacao(){}
