#include <iostream>
#include <iomanip>
#include <sstream>
#include "CartaoCredito.h"
#include "Cliente.h"
#include "cores.h"
#include "utils.h"
using namespace std;

//Construtor do cartão de crédito, recebe os dados necessários para criar um cartão e associa a um cliente
CartaoCredito::CartaoCredito(unsigned long long numero, std::string senha, double limite, std::vector<double> fatura, bool bloqueado, Cliente* cliente, double disponivel) {
    setNumero(numero);
    setSenha(senha);
    setLimite(limite);
    setBloqueado(bloqueado);
    associarCliente(cliente);
    setDisponivel(disponivel);
    faturas = fatura;
    faturas.resize(MAXPARCELAS, 0.0);
}
//Destrutor
CartaoCredito::~CartaoCredito() {}


//Getters
unsigned long long CartaoCredito::getNumero() const{
    return numero;
}
std::string CartaoCredito::getSenha() const{
    return senha;
}
double CartaoCredito::getLimite() const{
    return limite;
}
vector<double> CartaoCredito::getFaturas() const{
    return faturas;
}
bool CartaoCredito::getBloqueado() const{
    return bloqueado;
}
Cliente* CartaoCredito::getCliente() const{
    return cliente;
}
double CartaoCredito::getDisponivel() const{
    return disponivel;
}
double CartaoCredito::getFatura(int idx) const{
    return (idx >= MAXPARCELAS) ? -1 : faturas[idx];
}

//Setters
void CartaoCredito::setNumero(unsigned long long n){
    numero = n;
}
void CartaoCredito::setSenha(std::string s){
    senha = s;
}
void CartaoCredito::setLimite(double l){
    limite = l;
}
void CartaoCredito::setFatura(double valor, int idx){
    if(idx > MAXPARCELAS)
        return;
    faturas[idx] = valor;
}
void CartaoCredito::setBloqueado(bool b){
    bloqueado = b;
}
void CartaoCredito::associarCliente(Cliente* c){
    cliente = c;
}
void CartaoCredito::setDisponivel(double d){
    disponivel = d;
}

//Função para pagar a fatura, reduz o valor da fatura atual pelo valor pago
void CartaoCredito::pagarFaturaAtual(double valor) {
    cout << BOLD(GREEN("Pagamento realizado com sucesso!\n"));
    if(valor > faturas[0]){
        valor = faturas[0];
        cout << BOLD("Valor limitado a ") << printDinheiro(faturas[0]);
    }
    faturas[0] -= valor;
    disponivel += valor;
    if(faturas[0] == 0){
        for(int i = 0; i < MAXPARCELAS - 1; i++)
            faturas[i] = faturas[i + 1];
        faturas[MAXPARCELAS - 1] = 0;
        cout << BOLD("Sua próxima fatura é de ") << printDinheiro(faturas[0]);
    }
    else
        cout << BOLD("O valor restante da fatura é ") << printDinheiro(faturas[0]);
}

void CartaoCredito::insereFaturas(double valor, int parcelas){
    double valorPorFatura = valor / parcelas;
    for (int i = 0 ; i < parcelas; i++)
        faturas[i] += valorPorFatura;
    disponivel -= valor;
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

//função para gerar o número do cartão de crédito, combinando um BIN fixo com o ID do cliente formatado e calculando o dígito verificador usando o Algoritmo de Luhn
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


//Sobrecarga do operador << para facilitar a exibição dos dados do cartão de crédito
ostream& operator <<( std :: ostream& out , const CartaoCredito& c){
    out << BOLD("| Numero: ") << c.getNumero() << endl;
    out << BOLD("| Senha: ")  << c.getSenha() << endl;
    out << BOLD("| Limite: ") << printDinheiro(c.getLimite()) << endl;
    out << BOLD("| Fatura Atual: ") << c.getFatura() << endl;
    out << BOLD("| Bloqueado: ") << (c.getBloqueado()? BOLD(RED("Sim")) : BOLD(GREEN("Não"))) << endl;
    out << BOLD("| Disponivel: ") << printDinheiro(c.getDisponivel()) << endl;
    return out;
}


