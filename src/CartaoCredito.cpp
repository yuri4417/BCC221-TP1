#include <iostream>
#include "CartaoCredito.h"
#include "Cliente.h"

using namespace std;
CartaoCredito::CartaoCredito(double limite, double faturaAtual, bool bloqueado, Cliente* cliente) {
    setLimite(limite);
    setFatura(faturaAtual);
    setBloqueado(bloqueado);
    associarCliente(cliente);
}

double CartaoCredito::getLimite() const{
    return limite;
}
double CartaoCredito::getFatura() const{
    return faturaAtual;
}
bool CartaoCredito::getBloqueado() const{
    return bloqueado;
}
Cliente* CartaoCredito::getCliente() const{
    return cliente;
}

void CartaoCredito::setLimite(double l){
    limite = l;
}
void CartaoCredito::setFatura(double f){
    faturaAtual = f;
}
void CartaoCredito::setBloqueado(bool b){
    bloqueado = b;
}
void CartaoCredito::associarCliente(Cliente* c){
    cliente = c;
}

void CartaoCredito::bloquear(){
    setBloqueado(true);
}
void CartaoCredito::desbloquear(){
    setBloqueado(false);
}

bool CartaoCredito::realizarCompra(double valor) {
    if(bloqueado)
        return false;
        
    if(faturaAtual + valor > limite)
        return false;

    faturaAtual += valor;
    return true;
}

bool CartaoCredito::pagarFatura(double valor) {
    if(valor > faturaAtual)
        valor = faturaAtual;

    faturaAtual -= valor;
    return true;
}
