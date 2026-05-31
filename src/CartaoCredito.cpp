#include <iostream>
#include <iomanip>
#include <sstream>
#include "CartaoCredito.h"
#include "Cliente.h"

using namespace std;
CartaoCredito::CartaoCredito(unsigned long long numero, std::string senha, double limite, double faturaAtual, bool bloqueado, Cliente* cliente) {
    setNumero(numero);
    setSenha(senha);
    setLimite(limite);
    setFatura(faturaAtual);
    setBloqueado(bloqueado);
    associarCliente(cliente);
}

unsigned long long CartaoCredito::getNumero() const{
    return numero;
}
std::string CartaoCredito::getSenha() const{
    return senha;
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


void CartaoCredito::setNumero(unsigned long long n){
    numero = gerarNumeroCartao(n);
}
void CartaoCredito::setSenha(std::string s){
    senha = s;
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


//função auxiliar para calcular o dígito verificador (Algoritmo de Luhn)
int CartaoCredito::calcularDigitoVerificador(const std::string& numeroSemDigito) {
    int soma = 0;
    bool alternar = true;

    //caminha de tras para frente
    for (int i = numeroSemDigito.length() - 1; i >= 0; --i) {
        int digito = numeroSemDigito[i] - '0';//calcula o valor "real" usando a posição na tabela ascii

        if (alternar) {//multiplica dígitos por 2 alternadamente
            digito *= 2;
            if (digito > 9) {//soma os dois dígitos do resultado para manter o valor com apenas um dígito
                digito -= 9;//subtrair 9 é o equivalente a fazer a soma
            }
        }
        soma += digito;//adiciona valor ao contador
        alternar = !alternar;//alterna
    }

    return (10 - (soma % 10)) % 10;//o dígito verificador é definido como a "distância" da soma até a próxima dezena (%10 para o caso da distância ser 0)
}

unsigned long long CartaoCredito::gerarNumeroCartao(size_t id) {
    //define um bin (bank identification number) para ser usado na geração do número de cartão
    std::string bin = "426712";

    //formata o if do cliente para ter exatamente 9 dígitos (completa com zeros a esquerda se necessario)
    std::stringstream ss;
    ss << std::setw(9) << std::setfill('0') << id;//determina o tamanho mínimo da string como 9, preenchendo com o id e com zeros para completar, se necessário
    std::string idFormatado = ss.str();//transforma stringstream em string

    //se o id tiver mais de 9 dígitos, pegamos apenas os últimos 9 para não estourar os 16 dígitos
    if (idFormatado.length() > 9) {
        idFormatado = idFormatado.substr(idFormatado.length() - 9);//pega os caracteres a partir de (final - 9), ou seja, os últimos 9 elementos
    }

    //junta o bin com o id do cliente (total: 15 dígitos)
    std::string cartaoSemDigito = bin + idFormatado;

    //calcula o 16 digito usando o Algoritmo de Luhn
    int digitoVerificador = calcularDigitoVerificador(cartaoSemDigito);

    // concatena os valores, adicionando o digito verificador ao fim
    std::string numeroFinalStr = cartaoSemDigito + std::to_string(digitoVerificador);

    //converte a string de volta para size_t
    return std::stoull(numeroFinalStr);
}

ostream& operator <<( std :: ostream& out , const CartaoCredito& c){//Sobrecarga
    out << "| Numero: "<< c.getNumero() << endl;
    out << "| Senha: " << c.getSenha() << endl;
    out << "| Limite: " << c.getLimite() << endl;
    out << "| Fatura: " << c.getFatura() << endl;
    out << "| Bloqueado: " << (c.getBloqueado()? "Sim" : "Não") << endl;
    out << "| Cliente: " << (c.getCliente())->getNome() << endl;
    return out;
}
CartaoCredito::~CartaoCredito() {}