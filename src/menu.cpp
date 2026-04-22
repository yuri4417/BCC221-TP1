#include <iostream>
#include "menu.h"
#include "Cliente.h"
#include "Gerente.h"
#include "Pessoa.h"
#include "Transacao.h"
using namespace std;

void menu() {
    while (true) {
        cout << "\033[H\033[2J";
        cout << "===== SISTEMA DE GERENCIAMENTO DE BANCO =====" << endl << endl;
        cout << "1. Cadastrar cliente" << endl;
        cout << "2. Cadastrar gerente" << endl;
        cout << "3. Criar transação" << endl;
        cout << "4. Exibir extrato de um cliente" << endl;
        cout << "5. Associar gerente a cliente" << endl;
        cout << "6. Listar clientes" << endl;
        cout << "7. Listar gerentes" << endl;
        cout << "8. Salvar dados e sair" << endl;
        cout << endl << "==================================================" <<endl;
        cout << endl << "Escolha uma opção: ";
        int opt;
        cin >> opt;

        switch (opt) {
            case 1:
                cadastrarCliente();
                break;
            case 2:
                cadastrarGerente();
                break;
            case 3:
                criarTransacao();
                break;
            case 4:
                exibirExtrato();
                break;
            case 5: 
                associarGerenteCliente();
                break;
            case 6:
                listarClientes();
                break;
            case 7:
                listarGerentes();
                break;
            case 8:
                salvarSair();
                return;
            default:
               cout << "Opcao invalida. Tente novamente." << endl;
               break;
        }
    }
}

void cadastrarCliente() {
    Cliente p;
    string temp;

    cout << " ===== Iniciando Cadastro de Cliente =====" << endl;
    cout << "Digite o nome do cliente: ";
    getline(cin >> ws, temp);
    p.setNome(temp);

    cout << "Digite a data de nascimento do cliente (dd/mm/aaaa): ";
    getline(cin >> ws, temp);
    p.setDataNasc(temp);


    cout << "Digite a profissão do cliente: ";
    getline(cin >> ws, temp);
    p.setTrabalho(temp);


    float salario;
    cout << "Digite o salario do cliente: ";
    cin >> salario;
    int opt;
    cout << "Escolha uma modalidade de conta: " << endl;
    cout << "1. Conta Corrente" << endl;
    cout << "2. Conta Poupança" << endl;
    cout << "Escolha uma opção: ";
    cin >> opt;
    while (!(cin >> opt) || opt < 1 || opt > 2) {
        cout << "Opcao invalida. Tente novamente: ";
        cin.clear();
        cin >> opt;
        cin.ignore(1000, '\n');
    }

    if (opt == 1) 
        p.setTipoDeConta("Corrente");
    else 
        p.setTipoDeConta("Poupanca");

    if (opt == 2) {
        float taxa;
        cout << "Digite a taxa de rendimento da conta poupança: ";
        cin >> taxa;
        p.setRendimento(taxa);
    }

    cout << "Digite o login do cliente: ";
    getline(cin >> ws, temp);
    p.setLogin(temp);


    cout << "Digite a senha do cliente: ";
    getline(cin >> ws, temp);
    p.setSenha(temp);

    // TODO: Adicionar o cliente ao sistema (banco.adicionarCliente(p);)
    cout << " ========== Cliente cadastrado com sucesso! ==========" << endl;
}


void cadastrarGerente(){
    cout << " ===== Iniciando Cadastro de Gerente =====" << endl;
}
void criarTransacao(){
    cout << " ===== Iniciando Transacao =====" << endl;
}
void exibirExtrato(){
    cout << " ===== Exibindo Extrato de Um Cliente =====" << endl;
}
void associarGerenteCliente(){
    cout << " ===== Associando Gerente a Cliente =====" << endl;
}
void listarClientes(){
    //Cliente p;
    string nome;
    cout << " ===== Iniciando Listagem de Cliente =====" << endl;
    cout << "Informe o nome do Cliente: "; getline(cin, nome); 

}
void listarGerentes(){
    //Gerente g;
    string nome;
    cout << " ===== Iniciando Listagem de Gerente =====" << endl;
    cout << "Informe o nome do Gerente: "; getline(cin, nome);
}
void salvarSair(){
    cout << " ===== Salvando Dados =====" << endl;
}