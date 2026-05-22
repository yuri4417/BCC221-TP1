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
        cliente->exibirCliente();
}

void Transacao :: transacoes(int tipo){
    if(tipo == 1){
        //acao(clientes[0], clientes, valor)
    } else if(tipo == 2){
        acao(clientesEnvolvidos[0], valor);
    } else if(tipo == 3){//loser         
        acao(clientesEnvolvidos[0], (-1) * valor);
    }
}

       
void Transacao :: acao(Cliente *cliente, double valor){ //Depósito e saque
    if(valor < 0){//Saque
        if(valor > cliente->getSaldo()){
            cout << "Saldo insuficiente" << endl;
            return;
        }
        else
            cout<< "Saque Concluído..." <<endl;
    }
    else{//Depósito
        cout << "Depósito Concluído..." <<endl;
    }
    cliente->setSaldo(cliente->getSaldo() + valor);
}

void Transacao :: acao(Cliente* a, vector <Cliente*> b, double valor){ //Transferência ("valor" se refere à quantia que cada cliente receberá)
    if(valor * b.size() > a->getSaldo()){
        cout << "Saldo Insuficiente...\n";
        return;
    }
    for(auto item : b){
        item->setSaldo(item->getSaldo() + valor);
        a->setSaldo(a->getSaldo() - valor);
        //acao(item, valor);
        //acao(a, -valor);
    }
}
