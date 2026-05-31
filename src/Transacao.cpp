#include "Transacao.h"
#include "Cliente.h"
#include <iostream>
class Transacao;
using namespace std;

//Construtor setando o tipo,valor, data e horário da transação
Transacao::Transacao(int t, double v, string d, string h)
{
    setTipo(t);
    setValor(v);
    setData(d);
    setHorario(h);
}

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

// Exibe as transacoes realizadas 
void Transacao::exibirTransacao(){
    cout << "Tipo: "    <<  tipo   << endl;
    cout << "Valor: "   <<  valor  << endl;
    cout << "Data: "    <<  data   << endl;
    cout << "Horario: " << horario << endl;
    cout << "Clientes Envolvidos: " << endl;
    for(auto cliente : clientesEnvolvidos)
        cout << "Nome: " << cliente->getNome() << endl;
}

// Adiciona um cliente à lista de clientes
void Transacao::pushClienteEnvolvido(Cliente* cli) {
    this->clientesEnvolvidos.push_back(cli);
}

// Realiza a ação da transação, seja depósito ou saque, conferindo o saldo e o se o valor é válido
bool Transacao :: acao(Cliente *cliente, double valor){
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

// Realiza a ação da transferência, conferindo o saldo do remetente e o valor a ser transferido
bool Transacao :: acao(vector <Cliente*> clientes, double valor){ 
    if(valor * (clientes.size() - 1) > clientes[0]->getSaldo()){
        cout << "Saldo Insuficiente...\n";
        return false;
    }
    //primeira posição do vetor clientes é o remetente, as demais são os destinatários
    for (auto it = clientes.begin() + 1; it != clientes.end(); ++it) {

        (*it)->setSaldo((*it)->getSaldo() + valor);
        clientes[0]->setSaldo(clientes[0]->getSaldo() - valor);
    }
    return true;
}

// Destrutor
Transacao::~Transacao(){}
