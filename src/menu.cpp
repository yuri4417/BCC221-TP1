#include <iostream>
#include <cctype>
#include <fstream>
#include <sstream>  
#include <string>   
#include <vector>   

#include "menu.h"
#include "Cliente.h"
#include "Gerente.h"
#include "Pessoa.h"
#include "Transacao.h"
#include "utils.h"
#include "CartaoCredito.h"

using namespace std;

Banco::Banco(int qtdC, int qtdG):
    qtdClientes(qtdC), qtdGerentes(qtdG){
        carregaDados();
    }

void Banco::run() {
    while (true) {
        clearTerminal();
        cout << endl << "===== SISTEMA DE GERENCIAMENTO DE BANCO =====" << endl << endl;
        cout << "1. Cadastrar cliente" << endl;
        cout << "2. Cadastrar gerente" << endl;
        cout << "3. Criar transação" << endl;
        cout << "4. Exibir extrato de um cliente" << endl;
        cout << "5. Associar gerente a cliente" << endl;
        cout << "6. Listar cliente" << endl;
        cout << "7. Listar gerente" << endl;
        cout << "8. Gerenciar cartão de crédito" << endl;
        cout << "9. Salvar dados e sair" << endl;
        cout << "-1. Sair do menu" << endl;
        cout << "==================================================" <<endl;
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
                cartaoCredito();
                break;
            case 9:
                salvaDados();
                break;
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

void Banco::cadastrarCliente() {
    // Para fazer: pensar com carinho em fazer try throw e catch
    limpar_buffer();
    if (qtdGerentes == 0) {
        cout << "Erro: Cadastre um gerente antes de cadastrar novos clientes\n";
        cout << "Pressione qualquer tecla para retornar ao menu...\n";
        getchar();
        
        return;
    }
    Cliente* novoCliente = new(nothrow) Cliente;
    if (!novoCliente)
        return;

    //alocar ID, ler dados do cliente e adicionar ao vetor de clientes
    novoCliente->cadastro();
    novoCliente->setID(qtdClientes + 1);
    vecCliente.push_back(novoCliente);

    // Associar o cliente a um gerente
    cout << "\n ===== Associando o Cliente a um Gerente =====" << endl;
    showVector(vecGerente, "====== Selecione o ID do gerente para associar ao cliente ======");
    cout << "Escolha o ID do gerente: ";
    size_t id;
    
    while (!(cin >> id) || id <  1 || id > vecGerente.size()) {
            cout << "ERRO: ID não encontrado. Tente novamente: ";
            cin.clear();
            cin.ignore(10000, '\n');
    }
        
    Gerente *ptrGerente;
    for (auto g : vecGerente)
        if (g->getID() == id)
            ptrGerente = g;

    novoCliente->setGerenteAssociadoID(ptrGerente->getID());
    ptrGerente->setCliente(novoCliente);
    qtdClientes++;
    cout << endl << endl;
    cout << " ========== Cliente cadastrado com sucesso! ==========" << endl << endl;
    cout << "Pressione qualquer tecla para voltar para o menu...\n";
    getchar();
    
}

void Banco::cadastrarGerente() {
    Gerente* novoGerente = new(nothrow) Gerente; 
    if (!novoGerente)
        return;
    novoGerente->cadastro();
    novoGerente->setID(qtdGerentes + 1);
    vecGerente.push_back(novoGerente);
    qtdGerentes++;
    cout << " ========== Gerente cadastrado com sucesso! ==========" << endl;

    cout << "AVISO: Vincule clientes a esse gerente por meio da opção \"5. Associar gerente a cliente\"." << endl;
    cout << "Pressione qualquer tecla para voltar para o menu...\n"; 
    limpar_buffer();
    string pegaLixo;
    getline(cin, pegaLixo);  // Limpa o buffer para evitar que o getchar() seja pulado

}

void Banco::criarTransacao() {
    Transacao* novaTransacao = new(nothrow) Transacao; 
    if (!novaTransacao)
        return;
    int tipoTransacao;
    size_t id;
    int quant;
    double valor;
    string temp;
    clearTerminal();
    cout << " ===== Iniciando Transacao =====" << endl;
    
    cout << "Informe o tipo de transação: " << endl;
    cout << "1. Transferência" << endl;
    cout << "2. Depósito" << endl;
    cout << "3. Saque" << endl;
    cout << "4. Caderneta de Poupança" << endl;
    cout << endl << "==================================================" << endl;
    cout << "Escolha uma opção: ";
    
    while(!(cin >> tipoTransacao) || tipoTransacao < 1 || tipoTransacao > 3) {
        if(tipoTransacao < 1 || tipoTransacao > 3)
            cout << "Opção inválida. Tente novamente" << endl << endl;
    }

    // Fazer verificação de alguma forma
    cout << "Informe a data: ";
    getline(cin >> ws, temp);
    novaTransacao->setData(temp);

    cout << "Informe o horário: ";
    getline(cin >> ws, temp);
    novaTransacao->setHorario(temp);

    // Seleciona o cliente a realizar o saque, deposito, transferencia
    showVector(vecCliente, "====== Clientes Cadastrados ======");
    Cliente *ptrRemetente;
    cout << "Selecione o ID do cliente (remetente) para realizar a ação: ";
    while(1) {
        cin >> id;
        cin.clear();
        ptrRemetente = pesquisaIDCliente(id);
        if (ptrRemetente)
            break;
        cout << endl << "Cliente não encontrado. Tente novamente: ";
    }

    string verify;
    switch (tipoTransacao) {
        case 1: 
        {
            size_t idDestinatario;
            novaTransacao->setTipo(1);
            novaTransacao->pushClienteEnvolvido(ptrRemetente);
            cout << "Informe a quantidade de destinatários para o pagamento: ";
            cin >> quant;
            while(quant < 1){
                cout << "Quantidade inválida, digite novamente: ";
                cin >> quant;
            }

            cout << "Informe o valor que será transferido para cada destinatário (ou 0 para cancelar a ação): ";
            cin >> valor;
            if(valor <= 0)
                return;
            novaTransacao->setValor(valor);
            // Lê destinatário(s) e os adiciona no vetor clientesEnvolvidos
            for(int i = 0; i < quant; i++){
                do{
                    cout << "Informe o ID do destinatário " << i+1 << ": ";
                    cin >> idDestinatario;
                    if(id < 1 || idDestinatario > vecCliente.size())
                        cout << endl << "ID inválido. Digite novamente." << endl;
                } while(id < 1 || idDestinatario > vecCliente.size());
                
                Cliente *ptrDestinatario = pesquisaIDCliente(idDestinatario);
                if(ptrDestinatario)
                    novaTransacao->pushClienteEnvolvido(ptrDestinatario);
            }
            
            for(int i=4 ;i>0; i--) {                
                cout << "Digite a sua senha para finalizar a transacao: "; cin >> verify;

                if (verify == ptrRemetente->getSenha()) {
                    cout<< "Senha validada com sucesso!" <<endl;
                    break;
                }
                else {
                    if (i <= 1)
                        return;
                cout << "Senha inválida! Você tem " << i-1 << " tentativas!" << endl;
                }
            }
            cout << endl;
            while (!novaTransacao->acao(novaTransacao->getClientes(), valor)) {
                cout << "\nInsira outro valor (ou digite 0 para cancelar): ";
                cin >> valor;
                if(valor <= 0){
                    delete(novaTransacao);
                    return;
                }
                novaTransacao->setValor(valor);
            }
            // SOMENTE AGORA adiciona a transação
            ptrRemetente->pushTransacao(novaTransacao);
            for(auto cliente : novaTransacao->getClientes()) 
                if(cliente != ptrRemetente)
                    cliente->pushTransacao(novaTransacao);
            cout << "Transferência concluída com sucesso!\n";
        }    
            break;
        case 2:
        {
            Cliente *clienteDeposito = pesquisaIDCliente(id);
            novaTransacao->setTipo(2);
            cout << "Informe o valor do depósito (Insira um valor negativo para cancelar): R$ "; 
            cin >> valor;
            if(valor <= 0)
                return;
            for(int i=4 ;i>0; i--) {                
                cout << "Digite a sua senha para finalizar a transacao: "; cin >> verify;

                if (verify == clienteDeposito->getSenha()) {
                    cout<< "Senha validada com sucesso!" <<endl;
                    break;
                }
                else {
                    if (i <= 1){
                        delete(clienteDeposito);
                        return;
                    }
                    cout << "Senha inválida! Você tem " << i-1 << " tentativas!" << endl;
                }
            }
            cout << endl;
            novaTransacao->setValor(valor);
            if(novaTransacao->acao(clienteDeposito, valor))
                clienteDeposito->pushTransacao(novaTransacao);
            cout << "Depósito concluído com sucesso!\n";
        } 
            break;
        case 3: 
        {
            Cliente *clienteSaque = pesquisaIDCliente(id);
            novaTransacao->setTipo(3);
            cout << "Digite o valor a ser sacado (negativo para cancelar)." << endl << "R$ ";
            while (!(cin >> valor) || valor == 0 || valor > vecCliente[id-1]->getSaldo()) {
                cin.clear();
                cin.ignore(10000, '\n');
                if (valor < 0)
                    return;
                cout << "Valor invalido. Digite novamente: ";
            }
            for(int i = 4; i > 0; i--){
                cout << "Digite a sua senha para finalizar a transacao: "; cin >> verify;
                if (verify == clienteSaque->getSenha()){
                    cout << "Senha validada com sucesso!" <<endl;
                    break;
                }
                else{
                    if (i <= 1){
                        delete(clienteSaque);
                        return;
                    }
                    cout << "Senha inválida! Você tem " << i-1 << " tentativas!" << endl;
                }
            }
            cout << "Valor sacado: " << valor << endl;
            novaTransacao->setValor(valor); 
            if(novaTransacao->acao(clienteSaque, valor))
                clienteSaque->pushTransacao(novaTransacao);
            cout << "Saque concluído com sucesso!\n";
        }
        break;
        case 4:
            this->cadernetaDePoupanca();
            break;
        default:
            cout << "Opção inválida. Tentte novamente." << endl;       
            break;
    }
}

void Banco::exibirExtrato() {
    clearTerminal();
    size_t id;
    cout << " ===== Exibindo Extrato de Um Cliente =====" << endl;
    cout << "Informe o ID do cliente para exibir o extrato (0 para cancelar): "; cin >> id;
    if(id <= 0)
        return;
    while (id > vecCliente.size()){
        cout << "ID inválido. Digite novamente: ";
        cin >> id;
    }
    Cliente* clienteExtrato = pesquisaIDCliente(id);
    cout << "\n===== EXTRATO DE " << vecCliente[id-1]->getNome() << " =====\n";
    for(auto transacao : clienteExtrato->getTransacoes()) {
        cout << "Data: " << transacao->getData() << endl;
        cout << "Horario: " << transacao->getHorario() << endl;
        cout << "Tipo: " << (transacao->getTipo() == 1 ? "Transferência" : (transacao->getTipo() == 2 ? "Depósito" : "Saque")) << endl;
        cout << "Valor: R$ " << transacao->getValor() << endl;
        if(transacao->getTipo() == 1) {
            cout << "Transação para o(s) Cliente(s): " << endl;
            for(auto cliente : transacao->getClientes())
                if(cliente->getID() != id)
                    cout << "ID: " << cliente->getID() << " | Nome: " << cliente->getNome() << endl;
        }
        cout << endl;
    }
    cout << endl << "Pressione qualquer tecla para voltar ao menu...\n";
    limpar_buffer();
    getchar();
}

void Banco::associarGerenteCliente() {
    clearTerminal();
    cout << "\n ===== Associando um Gerente a Cliente =====" << endl;
    int qtd;
    cout << "Selecione um gerente para associar clientes\n";
    for (auto gerente : vecGerente) {
        cout << "ID: "<< gerente->getID() 
             << " | Nome:" << gerente->getNome() << endl;
    }
    cout << "Escolha o ID do gerente: ";
    size_t ID;  
    while (!(cin >> ID) || ID < 1 || ID > vecGerente.size()) {
        cout << "ERRO: ID não encontrado. Tente novamente: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }

    Gerente *novoGerente;
    for (auto g : vecGerente) 
        if (g->getID() == ID)
            novoGerente = g;

    cout << "Digite quantos clientes deseja vincular: "; 
    cin >> qtd;
    while(qtd < 1 || qtd > qtdClientes) {
        cout << "ERRO: Quantidade inválida!"; 
        cin >> qtd;
    }

    cout << "\n=== CLIENTES DISPONIVEIS PARA ALTERAR ===\n";
    for(auto cliente : vecCliente){
        if(cliente->getGerenteAssociadoID() != novoGerente->getID())
            cout << "ID: " << cliente->getID() << " | Nome: " << cliente->getNome() << endl;
    }
    
    for(int i = 0; i < qtd; i++) {
        size_t idCliente;
        cout << "Digite o ID do cliente (Digite 0 para cancelar)" << i+1 << ": ";
        cin >> idCliente;
        if (idCliente == 0)
            break;
        Cliente *ptr = pesquisaIDCliente(idCliente);
        if (ptr) {
            ptr->setGerenteAssociadoID(novoGerente->getID());
            novoGerente->setCliente(ptr);
        }
        else {
            cout<<"Cliente nao encontrado. Tente novamente."<<endl;
            i--;
        }
        
    }
}

void Banco::listarClientes(){
    string nome;
    clearTerminal();
    cout << " ===== Iniciando Listagem de Cliente =====" << endl;
    cout << "Informe o nome do Cliente: ";
    getline(cin >> ws, nome);

    bool encontrou = false;
    for(auto cliente : vecCliente) {
        if(cliente->getNome() == nome) {
            cout << "\n===== CLIENTE ENCONTRADO =====\n";
            cliente->exibirDados();
            encontrou = true;
            break;
        }
    }
    if (!encontrou)
        cout << "Cliente nao encontrado!" << endl;
    
    cout << endl << "Pressione qualquer tecla para voltar ao menu...\n";
    getchar();
}

void Banco::listarGerentes() {
    string nome;
    clearTerminal();
    cout << " ===== Iniciando Listagem de Gerente =====" << endl;
    cout << "Informe o nome do Gerente: "; 
    getline(cin >> ws, nome);
    bool encontrou = false;

    for(auto gerente : vecGerente){

        if(gerente->getNome() == nome){
            cout << "\n===== Gerente ENCONTRADO =====\n";
            gerente->exibirDados();
            encontrou = true;
            break;
        }
    }

    if(!encontrou){
        cout << "Gerente nao encontrado!" << endl;
    }

    cout << "Pressione qualquer tecla para voltar ao menu...\n";
    getchar();
}

Cliente* Banco::pesquisaIDCliente(size_t id) {
    for (auto ptr : vecCliente)
        if (ptr->getID() == id)
            return ptr;
    return nullptr;
}

void Banco::carregaDados() {
    fstream clientes;
    clientes.open("./data/clientes.csv", ios::in);
    if (!clientes){
        cout << "Erro ao abrir o arquivo. " << endl;
        return;
    }
    // carregamento dos clientes
    string linha;
    getline(clientes, linha); //consome o cabecalho
    while (getline(clientes, linha)) {
        if (!linha.empty() && linha.back() == '\r')
            linha.pop_back();
        stringstream ss(linha);
        vector<string> campos;
        string campo;   

        while (getline(ss, campo, ','))
            campos.push_back(campo);
        if (campos.size() < 11) 
            continue;

        Cliente *pCliente = new(nothrow) Cliente;
        if (!pCliente)  
            return;
        pCliente->setNome(campos[0]);
        pCliente->setLogin(campos[1]);
        pCliente->setSenha(campos[2]);
        pCliente->setDataNasc(campos[3]);
        pCliente->setTrabalho(campos[4]);
        pCliente->setID((size_t) stoi(campos[5]));
        pCliente->setGerenteAssociadoID((size_t) stoi(campos[6]));
        pCliente->setRemuneracao(stod(campos[7]));
        pCliente->setTipoDeConta(campos[8]);
        pCliente->setRendimento(stod(campos[9]));
        pCliente->setSaldo(stod(campos[10]));
        vecCliente.push_back(pCliente);    
    }    
    clientes.close();

    fstream gerentes;
    gerentes.open("./data/gerentes.csv", ios::in);
    if (!gerentes){
        cout << "Erro ao abrir o arquivo. " << endl;
        return;
    }

    getline(gerentes, linha); //consome o cabecalho
    while (getline(gerentes, linha)) {
        if (!linha.empty() && linha.back() == '\r')
            linha.pop_back(); 
        stringstream ss(linha);
        vector<string> campos;
        string campo;
        while (getline(ss, campo, ','))
            campos.push_back(campo);
        if (campos.size() < 7) 
            continue;

        Gerente *pGerente = new(nothrow) Gerente;
        if (!pGerente)
            return;
        pGerente->setNome(campos[0]);
        pGerente->setLogin(campos[1]);
        pGerente->setSenha(campos[2]);
        pGerente->setDataNasc(campos[3]);
        pGerente->setTrabalho(campos[4]);
        pGerente->setID((size_t) stoi(campos[5]));

        // lista de clientes associados
        string clientesAssociados = campos.back();
        clientesAssociados = clientesAssociados.substr(1, clientesAssociados.size() - 2);
        stringstream ss2(clientesAssociados);
        string num;
        while (getline(ss2, num, ';')) {
            Cliente *pCliente = pesquisaIDCliente((size_t) stoi(num));
            if (pCliente)
                pGerente->setCliente(pCliente);   
        }     
        vecGerente.push_back(pGerente);
    } 
    gerentes.close();
}

void Banco::salvaDados() {
    clearTerminal();
    cout << " ===== Salvando Dados =====" << endl;
    fstream clientes;
    clientes.open("./data/clientes.csv", ios::out);
    if (!clientes) {
        cout << "Erro ao abrir o arquivo. Tente novamente.\n";
        return;
    }
    clientes << "nome,login,senha,dataNasc,trabalho,ID,gerenteID,remuneracao,tipoConta,taxaRendimento,saldo\n";
    for (auto ptrCliente : vecCliente) {
        clientes <<  ptrCliente->getNome() << "," << ptrCliente->getLogin() << "," <<
                ptrCliente->getSenha() << "," << ptrCliente->getDataNasc() << "," <<
                ptrCliente->getTrabalho() << "," << ptrCliente->getID() << "," <<
                ptrCliente->getGerenteAssociadoID() << "," << ptrCliente->getRemuneracao() << "," <<
                ptrCliente->getTipoDeConta() << "," << ptrCliente->getRendimento() << "," <<
                ptrCliente->getSaldo() << "\n";
    }
    clientes.close();

    fstream gerentes;
    gerentes.open("./data/gerentes.csv", ios::out);
    if (!gerentes) {
        cout << "Erro ao abrir o arquivo. Tente novamente.\n";
        return;
    }
    gerentes << "nome,login,senha,dataNasc,trabalho,ID,clientesAssociados\n";
    for (auto ptrGerente : vecGerente) {
        gerentes <<
                ptrGerente->getNome() << "," << ptrGerente->getLogin() << "," <<
                ptrGerente->getSenha() << "," << ptrGerente->getDataNasc() << "," <<
                ptrGerente->getTrabalho() << "," << ptrGerente->getID() << ",";

        gerentes << "[";
        auto clientes = ptrGerente->getClientes();
        for (auto it = clientes.begin(); it != clientes.end(); ++it) {
            gerentes << (*it)->getID();
            if (next(it) != clientes.end()) 
                gerentes << ";";
        }
        gerentes << "]" << endl;
    }
}


void Banco::cadernetaDePoupanca() {
    for(auto cliente: vecCliente) {
        if(cliente->getTipoDeConta() == "2") {
            double valorRend = cliente->getSaldo() * (cliente->getRendimento()/100);
            cout << "Valor do Rendimento R$:" << valorRend << "Cliente: " << cliente->getNome() << "ID: " << cliente->getID() << endl;
            cliente->rendimento();
        }
    }
}

void Banco::cartaoCredito(){
    cout << " ===== Iniciando processo de Cartão de Crédito =====" << endl << endl;
    cout << "1. Criar cartão de crédito" << endl;
    cout << "2. Listar cartões de crédito" << endl;
    cout << "3. Alterar limite do cartão de crédito" << endl;
    cout << "4. Pagamento parcelado" << endl;
    cout << "5. Pagar fatura" << endl;
    cout << "6. Bloquear cartão" << endl;
    cout << "7. Desbloquear cartão" << endl;
    cout << "8. Voltar ao menu principal" << endl;
    cout << endl << "==================================================" << endl;
    cout << "Escolha uma opção: ";

    int opt;
    cin >> opt;

    while(opt < 1 || opt > 8) {
        cout << "Opção inválida. Tente novamente: ";
        cin >> opt;
    }
    
    while(1) {
        switch(opt){
            case 1:
                criarCartao();
                break;
            case 2:
                //listarCartao();
                break;
            case 3:
                //alterarLimite();
                break;
            case 4:
                //pagamentoParcelado();
                break;
            case 5:
                //pagarFatura();
                break;
            case 6:
                //bloquear();
                break;
            case 7:
                //desbloquear();
                break;
            case 8:
                cout << "Voltando ao menu principal..." << endl;
                return;
            default:
                cout << "Entrada desconhecida. Tente novamente." << endl;
                break;
        }        
    }
}

void Banco::criarCartao() {
    clearTerminal();
    cout << " ===== Criando Cartão de Crédito =====" << endl;
    size_t id;
    cout << "Informe o ID do cliente para criar um cartão de crédito (Digite 0 para cancelar): ";
    cin >> id;
    if (id == 0)
        return;
    
    while(id < 1 || id > vecCliente.size()) {
        cout << "ID inválido. Digite novamente: ";
        cin >> id;
    }
    Cliente *ptrCliente = pesquisaIDCliente(id);
    CartaoCredito *novoCartao = new(nothrow) CartaoCredito;
    if (!novoCartao)
        return;
    if(ptrCliente) {
        novoCartao->associarCliente(ptrCliente);
        ptrCliente->setCartao(novoCartao);
        cout << "Cartão de crédito criado com sucesso para o cliente " << ptrCliente->getNome() << "!" << endl;
    }
    double limite;
    cout << "\nDigite o limite do cartão: ";
    cin >> limite;
    while (limite <= 0) {
        cout << "Valor inválido. Digite novamente: ";
        cin >> limite;
    }
    novoCartao->setLimite(limite);
}

