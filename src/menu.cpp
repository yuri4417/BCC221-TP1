#include <iostream>
#include <cctype>
#include "menu.h"
#include "Cliente.h"
#include "Gerente.h"
#include "Pessoa.h"
#include "Transacao.h"
using namespace std;

Banco::Banco(int qtdC, int qtdG): 
    qtdClientes(qtdC), qtdGerentes(qtdG){}
    
void clearTerminal() {
    cout << "\033[H\033[2J"; 
}

void limpar_buffer() {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

int perguntaSN(string str) {
    string resp;
    cout << str;
    while (1) {
        cin >> resp;
        if (resp.size() == 1) {
            char opt = tolower(resp[0]);
            if (opt == 's') return 1;
            if (opt == 'n') return 0;
        }
        cout << "Opção Inválida! Tente novamente (Responda com S/N)\n";
    }
}

void Banco::run() {
    while (true) {
        imprimirOpcoes();
        int opt;
        cin >> opt;

        switch (opt) {
            case 1:
                cadastrarCliente(qtdClientes + 1);
                break;
            case 2:
                cadastrarGerente(qtdGerentes + 1);
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
                listarClientes(vecCliente);
                break;
            case 7:
                listarGerentes(vecGerente);
                break;
            case 8:
                salvarSair();
                return;
            case -1:
                if (perguntaSN("Tem certeza que deseja sair? (S/N): "))
                    return;
                else
                    cout << "Retornando ao menu..." << endl;
                break;
            default:
               cout << "Opcao invalida. Tente novamente." << endl;
               break;
        }
    }
}

void imprimirOpcoes()
{
        clearTerminal();
        cout << endl << "===== SISTEMA DE GERENCIAMENTO DE BANCO =====" << endl << endl;
        cout << "1. Cadastrar cliente" << endl;
        cout << "2. Cadastrar gerente" << endl;
        cout << "3. Criar transação" << endl;
        cout << "4. Exibir extrato de um cliente" << endl;
        cout << "5. Associar gerente a cliente" << endl;
        cout << "6. Listar clientes" << endl;
        cout << "7. Listar gerentes" << endl;
        cout << "8. Salvar dados e sair" << endl;
        cout << "-1. Sair do menu" << endl;
        cout << endl << "==================================================" <<endl;
        cout << endl << "Escolha uma opção: "; 
}
void Banco::cadastrarCliente(size_t novoID) {
    // Para fazer: pensar com carinho em fazer try throw e catch
    limpar_buffer();
    if (qtdGerentes == 0) {
        cout << "Erro: Cadastre um gerente antes de cadastrar novos clientes\n";
        cout << "Pressione qualquer tecla para retornar ao menu...\n";
        getchar();
        // getchar();
        
        return;
    }
    Cliente* novoCliente = new Cliente;

    novoCliente->cadastro();
    novoCliente->setID(novoID);
    vecCliente.push_back(novoCliente);
    qtdClientes++;
    cout << endl << endl;
    cout << " ========== Cliente cadastrado com sucesso! ==========" << endl << endl;
    cout << "Pressione qualquer tecla para voltar para o menu...\n";
    getchar();
}

void Banco::cadastrarGerente(size_t novoID) {
    Gerente* novoGerente = new Gerente; 
    novoGerente->cadastro();
    novoGerente->setID(novoID);
    vecGerente.push_back(novoGerente);
    qtdGerentes++;
    cout << " ========== Gerente cadastrado com sucesso! ==========" << endl;
    
    if (qtdClientes > 0){ //Cadastrar Cliente a esse Gerente
        cout << "\n ===== Associando Gerente a Cliente =====" << endl;
        int qtd;

        cout << "Digite quantos clientes deseja vincular: "; 
        cin >> qtd;
        while (qtd < 1 || qtd > qtdClientes) {
            cout << "ERRO: Quantidade inválida!"; cin >> qtd;
        }
        
        cout << "\n=== CLIENTES DISPONIVEIS PARA VINCULAR ===\n";
        for(auto cliente : vecCliente){
            if(cliente->getGerenteAssociadoID() == 0){
                cout << "ID: " << cliente->getID()
                    << " | Nome: " << cliente->getNome()
                    << endl;
                break;
            }    
        }
        
        for(int i=0; i<qtd; i++) {
            size_t idCliente;
            cout << "Digite o ID do cliente " << i+1 << ": ";
            cin >> idCliente;
            if (idCliente == 0)
                break;

            bool encontrado = false;
            for(auto cliente : vecCliente){
                if(cliente->getID() == idCliente){ 
                    if(cliente->getGerenteAssociadoID() != 0){
                        cout << "Cliente ja possui um gerente associado. Tente novamente." << endl;
                        i--;
                        encontrado = true;
                        break;
                    }
                    cliente->setGerenteAssociadoID(novoGerente->getID());
                    novoGerente->setCliente(cliente);
                    encontrado = true;
                    break;
                }
            }
            if(!encontrado){
                cout<<"Cliente nao encontrado. Tente novamente."<<endl;
                i--;
            }
        }
    }
    else{
        cout << "AVISO: Cadastre um Cliente para conseguir associar ele a algum Gerente." << endl;
        cout << "Pressione qualquer tecla para voltar para o menu...\n"; 
        getchar();
    }

}

void criarTransacao() {
    Transacao* novaTransacao = new Transacao; 
    int tipoTransacao;
    int aux;
    string temp;
    clearTerminal();
    cout << " ===== Iniciando Transacao =====" << endl;

    do{
        cout << "Informe o tipo de transação: " << endl;
        cout << "1. Transferência" << endl;
        cout << "2. Depósito" << endl;
        cout << "3. Saque" << endl;
        cout << endl << "==================================================" <<endl;
        cout << "Escolha uma opção: ";
        cin >> tipoTransacao;
        if(tipoTransacao < 1 || tipoTransacao > 3)
            cout << "Opção inválida. Tente novamente" << endl << endl;
    }while(tipoTransacao < 1 || tipoTransacao > 3);

    // Fazer verificação de alguma forma
    cout << "Informe a data: ";
    getline(cin >> ws, temp);
    novaTransacao->setData(temp);
    cout << endl;

    cout << "Informe o horário: ";
    getline(cin >> ws, temp);
    novaTransacao->setHorario(temp);    

    switch(tipoTransacao) {
        case 1:
            novaTransacao->setTipo(1);
            // cout << "Informe a quantidade de clientes envolvidos (excluindo a pessoa que fará o pagamento): ";
            // getline(cin << ws, quant);
            // while(quant < 1){
            //     cout << "Quantidade inválida, digite novamente: ";
            //     getline(cin << ws, quant);
            // }
            cout << "Informe o ID do remetente: ";
            cin >> aux;
            //Função de buscar cliente 
            // novaTransacao->setClientes(cliente);

            //while
                //cout << "Informe os IDs dos remetentes ou -1 para encerrar";
            
            
            break;
        case 2:
            novaTransacao->setTipo(2);
            break;
        case 3:
            novaTransacao->setTipo(3);
            break;
    }
}

void exibirExtrato(){
    clearTerminal();
    cout << " ===== Exibindo Extrato de Um Cliente =====" << endl;
}

void Banco :: associarGerenteCliente() {
    clearTerminal();
    cout << "\n ===== Associando Gerente a Cliente =====" << endl;
    int qtd;
    cout << "Selecione um gerente para associar clientes\n";
    for (auto gerente : vecGerente){
        cout << "ID: "<< gerente->getID() 
            << " | Nome:" << gerente->getNome() << endl;
    }
    
    cout << "Escolha o ID do gerente: ";
    size_t ID;
    while (!(cin >> ID) || ID > vecGerente.size())
        cout << "ERRO: ID não encontrado. Tente novamente: ";

    Gerente *novoGerente;
    for (auto g : vecGerente) 
        if (g->getID() == ID)
            novoGerente = g;


    cout << "Digite quantos clientes deseja vincular: "; 
    cin >> qtd;
    while (qtd < 1 || qtd > qtdClientes) {
        cout << "ERRO: Quantidade inválida!"; cin >> qtd;
    }
    
    cout << "\n=== CLIENTES DISPONIVEIS PARA VINCULAR ===\n";
    for(auto cliente : vecCliente){
        if(cliente->getGerenteAssociadoID() == __INT_MAX__){
            cout << "ID: " << cliente->getID() << " | Nome: " << cliente->getNome();
        }    
    }
    cout << "\n=== CLIENTES DISPONIVEIS PARA ALTERAR ===\n";
    for(auto cliente : vecCliente){
        if(cliente->getGerenteAssociadoID() != __INT_MAX__)
            cout << "\nID: " << cliente->getID() << "Nome: " << cliente->getNome() << endl; 
    }
    
    for(int i = 0; i < qtd; i++) {
        size_t idCliente;
        cout << "Digite o ID do cliente " << i+1 << ": ";
        cin >> idCliente;
        if (idCliente == 0)
            break;
            
        bool encontrado = false;
        for(auto cliente : vecCliente){
            if(cliente->getID() == idCliente){ 
                if(cliente->getGerenteAssociadoID() != __INT_MAX__){
                    if(perguntaSN("Este cliente ja possui um gerente associado. Deseja vinculá-lo a um novo gerente? (S/N)")){
                        cliente->setGerenteAssociadoID(novoGerente->getID());
                        novoGerente->setCliente(cliente);
                        encontrado = true;
                        break;
                    }
                    else {
                        cout << "Cliente mantido com o gerente atual, tente outro cliente." << endl;
                        encontrado = true;
                        break;
                    }
                } 
                else{
                    cliente->setGerenteAssociadoID(novoGerente->getID());
                        novoGerente->setCliente(cliente);
                        encontrado = true;
                        break;
                }
            }
        }
        if(!encontrado){
            cout<<"Cliente nao encontrado. Tente novamente."<<endl;
        }
    }
}

void Banco :: listarClientes(vector<Cliente*> vecCliente){
    string nome;
    clearTerminal();
    cout << " ===== Iniciando Listagem de Cliente =====" << endl;
    cout << "Informe o nome do Cliente: "; getline(cin >> ws, nome); 

    bool encontrou = false;
    for(auto cliente : vecCliente) {
        if(cliente->getNome() == nome) {
            cout << "\n===== CLIENTE ENCONTRADO =====\n";
            cout << "Nome: " << cliente->getNome() << endl;
            cout << "Login: " << cliente->getLogin() << endl;
            cout << "Data de Nascimento: " << cliente->getDataNasc() << endl;
            cout << "Profissao: " << cliente->getTrabalho() << endl;            
            cout << "Senha: " << cliente->getSenha() << endl;
            cout << "ID: " << cliente->getID() << endl;
            cout << "Gerente Associado: " << cliente->getGerenteAssociadoID() << endl;
            cout << "Saldo: " << cliente->getSaldo() << endl;
            cout << "Remuneracao: " << cliente->getRemuneracao() << endl;
            cout << "Tipo de Conta: " << cliente->getTipoDeConta() << endl;
            cout << "Taxa de rendimento: "<< cliente->getRendimento() << endl;
            encontrou = true;
        }
    }
    if (!encontrou)
        cout << "Cliente nao encontrado!" << endl;

    cout << endl << "Pressione qualquer tecla para voltar ao menu...\n";
    getchar();
}

void Banco :: listarGerentes(vector<Gerente*> vecGerente) {
    string nome;
    clearTerminal();
    cout << " ===== Iniciando Listagem de Gerente =====" << endl;
    cout << "Informe o nome do Gerente: "; 
    getline(cin >> ws, nome);
    bool encontrou = false;

    for(auto gerente : vecGerente){

        if(gerente->getNome() == nome){

            cout << "\n===== Gerente ENCONTRADO =====\n";

            cout << "Nome: " << gerente->getNome() << endl;
            cout << "Login: " << gerente->getLogin() << endl;
            cout << "Data de Nascimento: " << gerente->getDataNasc() << endl;
            cout << "Profissao: " << gerente->getTrabalho() << endl;
            cout << "Senha: " << gerente->getSenha() << endl;
            cout << "ID: " << gerente->getID() << endl;
            cout << "Clientes associados: " << endl;
            int count = 0;
            for(auto cliente : vecCliente){
                if(cliente->getGerenteAssociadoID() == gerente->getID()){
                    cout << cliente->getNome() << endl;
                    count++;
                }       
                if (!count) //TA IMPRIMINDO MESMO QUANDO TEM 
                    cout << "Nenhum cliente associado\n" << endl;
            }
            encontrou = true;
        }
    }

    if(!encontrou){
        cout << "Gerente nao encontrado!" << endl;
    }

    cout << "Pressione qualquer tecla para voltar ao menu...\n";
    getchar();
}
void salvarSair(){
    clearTerminal();
    cout << " ===== Salvando Dados =====" << endl;
}