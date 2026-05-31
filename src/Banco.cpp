#include <iostream>
#include <cctype>
#include <fstream>
#include <sstream>  
#include <string>   
#include <vector>   

#include "Banco.h"
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
    while (true) {//imprime as opções de menu
        clearTerminal();
        cout << endl << BOLD(MAGENTA("======= SISTEMA DE GERENCIAMENTO DE BANCO =======")) << endl;
        cout << BOLD(GREEN("1. Cadastrar cliente")) << endl;
        cout << BOLD(GREEN("2. Cadastrar gerente")) << endl;
        cout << BOLD(GREEN("3. Criar transação")) << endl;
        cout << BOLD(GREEN("4. Associar gerente a cliente")) << endl;
        cout << BOLD(CYAN("5. Listar cliente")) << endl;
        cout << BOLD(CYAN("6. Listar gerente")) << endl;
        cout << BOLD(CYAN("7. Exibir extrato de um cliente")) << endl;
        cout << BOLD(YELLOW("8. Gerenciar cartão de crédito")) << endl;
        cout << BOLD(YELLOW("9. Calcular rendimento da caderneta de poupança")) << endl; 
        cout << BOLD(RED("10. Salvar dados e sair")) << endl;
        cout << BOLD(RED("-1. Sair do menu")) << endl;
        cout << BOLD(MAGENTA("=================================================")) <<endl;
        int opt;
        cout << BOLD(GREEN("Escolha uma opção: ")); cin >> opt;
        cin.ignore(10000, '\n');
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
                associarGerenteCliente();
                break;
            case 5: 
                listarClientes();
                break;
            case 6:
                listarGerentes();
                break;
            case 7:
                exibirExtrato();
                break;
            case 8:
                cartaoCredito();
                break;
            case 9:
                cadernetaDePoupanca();
                break;
            case 10:
                salvaDados();
                break;
            case -1:
                if (perguntaSN(BOLD(RED("Tem certeza que deseja sair? (S/N): "))))
                    return;
                break;
            default:
               cout << BOLD(YELLOW("Opcao invalida. Tente novamente.")) << endl;
               break;
        }
    }
}

void Banco::cadastrarCliente() {
    // Para fazer: pensar com carinho em fazer try throw e catch
    
    if (qtdGerentes == 0) {
        cout << BOLD(RED("Erro: Cadastre um gerente antes de cadastrar novos clientes")) << endl;
        confirmar((BOLD(GREEN("Pressione ENTER para continuar..."))));
        return;
    }
    Cliente* novoCliente = new(nothrow) Cliente;
    if (!novoCliente)
        return;

    //alocar ID, ler dados do cliente e adicionar ao vetor de clientes
    if (!novoCliente->cadastro()) {
        delete novoCliente;
        confirmar(BOLD(RED("Cadastro de Cliente CANCELADO. Pressione ENTER para sair...")));
        return;
    }
        
    novoCliente->setID(qtdClientes + 1);
    vecCliente.push_back(novoCliente);

    // Associar o cliente a um gerente
    cout << BOLD(GREEN("\n ===== Associando o Cliente a um Gerente =====")) << endl;
    showVector(vecGerente, BOLD(GREEN("====== Selecione o ID do gerente para associar ao cliente ======")));
    size_t id;
    Gerente *ptrGerente;
    while (1) {
        if (!lerEntrada(id, BOLD("Escolha o ID do gerente"), ": ")) {
            delete novoCliente;
            return;
        }
        ptrGerente = pesquisaID(vecGerente, id);
        if (ptrGerente)
            break;
        cout << BOLD(RED("ERRO: ID não encontrado"));
    }
    novoCliente->setGerenteAssociadoID(ptrGerente->getID());
    ptrGerente->setCliente(novoCliente);
    qtdClientes++;
    cout << endl << endl;
    cout << BOLD(GREEN(" ========== Cliente cadastrado com sucesso! ==========")) << endl;
    confirmar(BOLD(GREEN("Pressione qualquer tecla para voltar para o menu...")));
    
}

void Banco::cadastrarGerente() {
    Gerente* novoGerente = new(nothrow) Gerente; 
    if (!novoGerente)
        return;
    if(!novoGerente->cadastro()) {
        delete novoGerente;
        confirmar(BOLD(RED("Cadastro de Gerente CANCELADO. Pressione ENTER para sair...")));
        return;
    }

    novoGerente->setID(qtdGerentes + 1);
    vecGerente.push_back(novoGerente);
    qtdGerentes++;
    cout << BOLD(GREEN(" ========== Gerente cadastrado com sucesso! ==========")) << endl;
    confirmar(BOLD(GREEN("Pressione qualquer tecla para voltar para o menu...")));
}

void cancelaTransacao(Transacao *t) {
    delete t;
    confirmar(BOLD(RED("Transacao CANCELADA. Pressione ENTER para retornar ao menu... ")));
}

void Banco::criarTransacao() {
    Transacao* novaTransacao = new(nothrow) Transacao;
    if (!novaTransacao)
        return;
    int tipoTransacao;
    size_t id;
    int quant = 0;
    double valor;
    string temp;
    clearTerminal();
    cout << BOLD(GREEN(" ===== Iniciando Transacao =====")) << endl;
    
    cout << "Informe o tipo de transação: " << endl;
    cout << "1. Transferência" << endl;
    cout << "2. Depósito" << endl;
    cout << "3. Saque" << endl;
    cout << endl << "==================================================" << endl;
    while(1) {
        if (!lerEntrada(tipoTransacao, "Escolha uma opção ", ": ")) {
            cancelaTransacao(novaTransacao);
            return;
        }
        if(tipoTransacao >= 1 && tipoTransacao <= 3)
            break;
        cout << "Opção inválida. Tente novamente" << endl;
    }

    // Fazer verificação de alguma forma
    if (!lerEntrada(temp, "Informe a data", ": "))  {
        cancelaTransacao(novaTransacao);
        return;
    }
    novaTransacao->setData(temp);


    if (!lerEntrada(temp, "Informe o horário", ": ")) {
        cancelaTransacao(novaTransacao);
        return;
    }
    novaTransacao->setHorario(temp);

    // Seleciona o cliente a realizar o saque, deposito, transferencia
    showVector(vecCliente, "====== Clientes Cadastrados ======");
    Cliente *ptrRemetente;
    while(1) {
        if (!lerEntrada(id, "Selecione o ID do cliente (remetente) para realizar a ação ",": ")) {
            cancelaTransacao(novaTransacao);
            return;
        }
        ptrRemetente = pesquisaID(vecCliente, id);
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
            while(1) {
                if (!lerEntrada(quant, "Informe a quantidade de destinatários para o pagamento ", ": ")) {
                    cancelaTransacao(novaTransacao);
                    return;
                }
                if (quant >= 1 && quant < qtdClientes)
                    break;
                cout << BOLD(YELLOW("Quantidade inválida, digite novamente.")) << endl;
            }

            if (!lerEntrada(valor, "Informe o valor que será transferido para cada destinatário ", ": ")) {
                cancelaTransacao(novaTransacao);
                return;
            }
            if(valor <= 0) {
                cout << "Valor inválido\n";
                cancelaTransacao(novaTransacao);
                return;
            }
            novaTransacao->setValor(valor);
            // Lê destinatário(s) e os adiciona no vetor clientesEnvolvidos
            for(int i = 0; i < quant; i++){
                do{
                    if (!lerEntrada(idDestinatario, "Informe o ID do destinatário ", ": ")) {
                        cancelaTransacao(novaTransacao);
                        return;
                    }
                    if(id < 1 || idDestinatario > vecCliente.size() || idDestinatario == id)
                        cout << endl << "ID inválido. Digite novamente." << endl;
                    
                } while(idDestinatario < 1 || idDestinatario > vecCliente.size() || idDestinatario == id);
                
                Cliente *ptrDestinatario = pesquisaID(vecCliente, idDestinatario);
                if(ptrDestinatario)
                    novaTransacao->pushClienteEnvolvido(ptrDestinatario);
            }
            
            for(int i=4 ;i>0; i--) {    
                if (!lerEntrada(verify, "Digite a sua senha para finalizar a transacao ")) {
                    cancelaTransacao(novaTransacao);
                    return;
                }            
                if (verify == ptrRemetente->getSenha()) {
                    cout<< "Senha validada com sucesso!" <<endl;
                    break;
                }
                else {
                    if (i <= 1) {
                        cancelaTransacao(novaTransacao);
                        return;
                    }
                    cout << "Senha inválida! Você tem " << i-1 << " tentativas!" << endl;
                }
            }
            cout << endl;
            while (!novaTransacao->acao(novaTransacao->getClientes(), valor)) {
                if (!lerEntrada(valor, "\nInsira outro valor ", ": R$ ")) {
                    cancelaTransacao(novaTransacao);
                    return;
                }
                novaTransacao->setValor(valor);
            }
            // SOMENTE AGORA adiciona a transação
            ptrRemetente->pushTransacao(novaTransacao);
            for(auto cliente : novaTransacao->getClientes()) 
                if(cliente != ptrRemetente)
                    cliente->pushTransacao(novaTransacao);
            cout << "Transferência concluída com sucesso!" << endl;
            confirmar("Pressione ENTER para retornar ao menu...");
        }    
            break;
        case 2:
        {
            Cliente *clienteDeposito = ptrRemetente;
            novaTransacao->setTipo(2);
            if (!lerEntrada(valor, "Informe o valor do depósito", ": R$ ")) {
                cancelaTransacao(novaTransacao);
                return;
            }
            for(int i=4 ;i>0; i--) {        
                if (!lerEntrada(verify,"Digite a sua senha para finalizar a transacao", ": ")) {
                    cancelaTransacao(novaTransacao);
                    return;
                }        
                if (verify == clienteDeposito->getSenha()) {
                    cout<< "Senha validada com sucesso!" <<endl;
                    break;
                }
                else {
                    if (i <= 1) {
                        cancelaTransacao(novaTransacao);
                        return;
                    }
                    cout << "Senha inválida! Você tem " << i-1 << " tentativas!" << endl;
                }
            }
            cout << endl;
            novaTransacao->setValor(valor);
            if(novaTransacao->acao(clienteDeposito, valor)) {
                novaTransacao->pushClienteEnvolvido(clienteDeposito);
                clienteDeposito->pushTransacao(novaTransacao);
            }
            confirmar("Pressione ENTER para retornar ao menu...");
        } 
            break;
        case 3: 
        {
            Cliente *clienteSaque = pesquisaID(vecCliente, id);
            novaTransacao->setTipo(3);
           
            while (1) {
                if (!lerEntrada(valor, "Digite o valor a ser sacado", ": R$ ")) {
                    cancelaTransacao(novaTransacao);
                    return;
                }
                if (valor <= clienteSaque->getSaldo())
                    break;
                cout << "Valor invalido. Digite novamente: ";
            }
            for(int i = 4; i > 0; i--){
                if (!lerEntrada(verify, "Digite a sua senha para finalizar a transacao ", ": ")) {
                    cancelaTransacao(novaTransacao);
                    return;
                }
                if (verify == clienteSaque->getSenha()){
                    cout << "Senha validada com sucesso!" <<endl;
                    break;
                }
                else{
                    if (i <= 1) {
                        cancelaTransacao(novaTransacao);
                        return;
                    }
                    cout << "Senha inválida! Você tem " << i-1 << " tentativas!" << endl;
                }
            }
            cout << "Valor sacado: " << valor << endl;
            novaTransacao->setValor(valor); 
            if(novaTransacao->acao(clienteSaque, -valor)) {
                novaTransacao->pushClienteEnvolvido(clienteSaque);
                clienteSaque->pushTransacao(novaTransacao);
            }
            confirmar("Pressione ENTER para retornar ao menu...");
        }
        break;
        default:
            cout << "Opção inválida. Tente novamente." << endl;       
            break;        
    }
    vecTransacao.push_back(novaTransacao);
}

void Banco::exibirExtrato() {
    clearTerminal();
    size_t id;
    cout << BOLD(GREEN("===== Exibindo Extrato de Um Cliente =====")) << endl;
    for(auto clientes: vecCliente)
        cout << "ID: " << clientes->getID() << " | Nome: " << clientes->getNome() << endl;
    while (true){
        if (!lerEntrada(id, "Informe o ID do cliente para exibir o extrato ", ": "))
            return;
        if (id >= 1 && id <= vecCliente.size())
            break;
        cout << "ID inválido. Digite novamente: ";
    }
    
    Cliente* clienteExtrato = pesquisaID(vecCliente, id);
    cout << "\n===== EXTRATO DE " << clienteExtrato->getNome() << " =====\n";
    for(auto transacao : clienteExtrato->getTransacoes()) {
        size_t idRemetente = transacao->getClientes()[0]->getID();
        string nomeRemetente = transacao->getClientes()[0]->getNome();

        cout << "Data: " << transacao->getData() << endl;
        cout << "Horario: " << transacao->getHorario() << endl;
        cout << "Tipo: " << (transacao->getTipo() == 1 ? "Transferência" : (transacao->getTipo() == 2 ? "Depósito" : "Saque")) << endl;
        cout << "Valor: R$ " << transacao->getValor() << endl;

        if(transacao->getTipo() == 1) {
            if(idRemetente == clienteExtrato->getID())
                cout << "Transação para o(s) Cliente(s): " << endl;
            else{
                cout << "Transação recebida de " << nomeRemetente << endl;
                continue;
            }
            for(auto cliente : transacao->getClientes())
                if(cliente->getID() != id)
                    cout << "ID: " << cliente->getID() << " | Nome: " << cliente->getNome() << endl;
        }
        cout << endl;
        cout << "=================\n";
    }
    confirmar();
}

void Banco::associarGerenteCliente() {
    clearTerminal();
    cout << BOLD(GREEN("===== Associando um Gerente a Cliente =====\n")) << endl;
    int qtd;
    if(qtdGerentes == 0 || qtdClientes == 0) {
        cout << BOLD(RED("Erro: Cadastre clientes e gerentes antes de associar!")) << endl;
        confirmar(BOLD(GREEN("Pressione qualquer tecla para voltar ao menu...")));
        return;
    }
    showVector(vecGerente, BOLD(GREEN("====== Selecione o ID do gerente para associar ao cliente ======")));
    size_t ID;  
    
    Gerente *novoGerente = nullptr;
    
    while (1) {
        if (!lerEntrada(ID, BOLD(YELLOW("Escolha o ID do gerente")), ": "))
            return;
        novoGerente = pesquisaID(vecGerente, ID); 
        if (novoGerente != nullptr) break; 
        
        cout << BOLD(RED("ERRO: ID não encontrado. Tente novamente: \n"));
    }
    int clientesDisponiveis = vecCliente.size() - (int)novoGerente->getClientes().size();
    if(clientesDisponiveis == 0) {
        cout << BOLD(YELLOW("O gerente selecionado já possui todos os clientes associados!\n"));
        confirmar(BOLD(GREEN("Pressione qualquer tecla para voltar ao menu...")));
        return;
    }
    while(1) {
        if (!lerEntrada(qtd,"Digite quantos clientes deseja vincular", ": "))
            return;
        if (qtd >= 1 && qtd <= clientesDisponiveis)
            break;
        cout << BOLD(RED("ERRO: Quantidade inválida!\n")) << BOLD(GREEN("Quantidade disponível: \n")) << clientesDisponiveis << endl;
    }

    cout << BOLD(GREEN("=== CLIENTES DISPONIVEIS PARA ALTERAR ===\n"));
    for(auto cliente : vecCliente){
        if(cliente->getGerenteAssociadoID() != novoGerente->getID())
            cout << "ID: " << cliente->getID() << " | Nome: " << cliente->getNome() << endl;
    }
    
    for(int i = 0; i < qtd; i++) {
        size_t idCliente;
        size_t idGerenteAntigo;
        if (!lerEntrada(idCliente, "Digite o ID do cliente", ": "))
            return;
        Cliente *ptr = pesquisaID(vecCliente, idCliente);
        if (ptr) {
           if (ptr->getGerenteAssociadoID() == novoGerente->getID()) {
                cout << BOLD(YELLOW("O cliente ")) << ptr->getNome() 
                << BOLD(YELLOW(" já está associado a este gerente. Nenhuma alteração feita.")) << endl;
                i--;    
                continue; 
             }
            if (ptr->getGerenteAssociadoID() != 0){
                // Desassocia cliente da lista de clientes associados do gerente antigo
                idGerenteAntigo = ptr->getGerenteAssociadoID();
                Gerente *ptrGerenteAntigo = pesquisaID(vecGerente, idGerenteAntigo);
                ptrGerenteAntigo->removeCliente(ptr->getID());
            }
            ptr->setGerenteAssociadoID(novoGerente->getID());
            cout << BOLD(GREEN("Gerente ")) << BOLD(CYAN(novoGerente->getNome())) << BOLD(GREEN(" associado ao cliente ")) << BOLD(CYAN(ptr->getNome())) << BOLD(GREEN(" com sucesso!\n"));
            confirmar();
            if(!novoGerente->setCliente(ptr))
                i--;
        }
        else {
            cout<< BOLD(YELLOW("Cliente nao encontrado. Tente novamente.")) << endl;
            i--;
        }
        
    }
}

void Banco::listarClientes(){
    string nome;
    clearTerminal();
    cout << BOLD(GREEN("===== Iniciando Listagem de Cliente =====")) << endl;
    for(auto clientes: vecCliente)
        cout << *clientes;
    if (!lerEntrada(nome, "Informe o nome do Cliente ",": "))
        return;

    bool encontrou = false;
    for(auto cliente : vecCliente) {
        if(cliente->getNome() == nome) {
            cout << BOLD(GREEN("\n===== CLIENTE ENCONTRADO =====\n"));
            cliente->exibirDados();
            encontrou = true;
            break;
        }
    }
    if (!encontrou)
        cout << BOLD(RED("Cliente nao encontrado!")) << endl;
    confirmar(BOLD(GREEN("Pressione qualquer tecla para voltar ao menu...")));
}

void Banco::listarGerentes() {
    string nome;
    clearTerminal();
    cout << BOLD(GREEN("===== Iniciando Listagem de Gerente =====")) << endl;
    for(auto gerentes: vecGerente)
        cout << *gerentes;
    if (!lerEntrada(nome, "Informe o nome do Gerente "))
        return;
    bool encontrou = false;
    for(auto gerente : vecGerente) {
        if(gerente->getNome() == nome){
            cout << BOLD(GREEN("\n===== Gerente ENCONTRADO =====\n"));
            gerente->exibirDados();
            encontrou = true;
            break;
        }
    }
    if(!encontrou)
        cout << BOLD(YELLOW("Gerente nao encontrado!")) << endl;
    confirmar(BOLD(GREEN("Pressione qualquer tecla para voltar ao menu...")));
}

void Banco :: listarCartao(){   
    size_t id;
    clearTerminal();
    cout << BOLD(GREEN("===== Iniciando Listagem do Cartão de Cliente =====")) << endl;
    for(auto clientes: vecCliente)
        cout << *clientes;
    if (!lerEntrada(id, BOLD("Informe o id do Cliente"), ": "))
        return;

    bool encontrou = false;
    for(auto cliente : vecCliente) {
        if(cliente->getID() == id) {
            if(cliente->getCartao() != nullptr){
                cout << BOLD(GREEN("\n===== CARTAO ENCONTRADO =====\n"));
                cout << *cliente;
                cout << *(cliente->getCartao());
                encontrou = true;
                break;
            }
            else{
                cout << BOLD(YELLOW("=== Cliente não possui cartão de crédito ===\n"));
                encontrou = true;
            }
        }
    }
    if (!encontrou)
        cout << BOLD(RED("Cliente nao encontrado!")) << endl;
    confirmar(BOLD(GREEN("Pressione qualquer tecla para voltar ao menu...")));
}

void Banco::carregaDados() {
    // Carregamento dos clientes
    // nome,login,senha,dataNasc,trabalho,id,gerenteID,remuneracao,tipoConta,taxaRendimento,saldo,{numCartao;senhaCartao;limite;bloqueado;[fatura0:fatura1:...]}
    fstream clientes;   
    string linha;
    clientes.open("./data/clientes.csv", ios::in);
    if (!clientes){
        cout << BOLD(RED("Erro ao abrir o arquivo. Tente novamente.\n")) << endl;
        return;
    }
    getline(clientes, linha); //consome o cabecalho
    while (getline(clientes, linha)) {
        if (!linha.empty() && linha.back() == '\r')
            linha.pop_back();
        stringstream ss(linha);
        vector<string> campos;
        string campo;

        while (getline(ss, campo, ',')){
            campos.push_back(campo);
        }
        if (campos.size() < 12) 
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

        // Lendo cartao
        vector<string> dadosCartao;
        string dados = campos[11];
        size_t ini = dados.find('{');
        size_t end = dados.find('}');
        if (ini != string::npos && end != string::npos) {
            string listaPartes = dados.substr(ini + 1, end - ini - 1);
            stringstream ssParts(listaPartes);
            string dadoCartao;
            while (getline(ssParts, dadoCartao, ';')) 
                dadosCartao.push_back(dadoCartao);
            
            if (dadosCartao.size() >= 4) {
                CartaoCredito *novoCartao = new(nothrow) CartaoCredito;
                if (!novoCartao)
                    return;

                novoCartao->setNumero(stoull(dadosCartao[0]));
                novoCartao->setSenha(dadosCartao[1]);
                novoCartao->setLimite(stod(dadosCartao[2]));
                if(stoi(dadosCartao[3]) == 1)
                novoCartao->setBloqueado(true);
                else
                    novoCartao->setBloqueado(false);

                novoCartao->setDisponivel(stod(dadosCartao[4]));
                
                if (dadosCartao.size() > 5) {
                    string faturaBloco = dadosCartao[5];
                    size_t ini2 = faturaBloco.find('[');
                    size_t end2 = faturaBloco.find(']');
                    if (ini2 != string::npos && end2 != string::npos) {
                        string listaFaturas = faturaBloco.substr(ini2 + 1, end2 - ini2 - 1);
                        stringstream ssFat(listaFaturas);
                        string fat;
                        int i = 0;
                        while (getline(ssFat, fat, ':')) 
                            if (!fat.empty()){
                                novoCartao->setFatura(stod(fat), i);
                                i++;
                            }
                    }
                }
                pCliente->setCartao(novoCartao);   
            }
        }
        vecCliente.push_back(pCliente);
        qtdClientes++;
    }
    clientes.close();



    // Carregamento das transações
    // tipo,valor,data,horario,[id1;id2;id3;id4]
    fstream transacoes;
    transacoes.open("./data/transacoes.csv", ios::in);
    if (!transacoes) {
        cout << BOLD(RED("Erro ao abrir o arquivo. Tente novamente.\n")) << endl;
        return;
    }
    getline(transacoes, linha); //consome cabecalho
    while (getline(transacoes, linha)) {
        if (!linha.empty() && linha.back() == '\r')
            linha.pop_back();

        stringstream ss(linha);
        string tipo, valorStr, data, horario, participantes;

        getline(ss, tipo, ',');
        getline(ss, valorStr, ',');
        getline(ss, data, ',');
        getline(ss, horario, ',');
        getline(ss, participantes);   // [id1;id2;id3]

        // Parseia os participantes [id1;id2;id3]
        vector<size_t> partsIDs;
        size_t ini = participantes.find('[');
        size_t end = participantes.find(']');
        if (ini != string::npos && end != string::npos) {
            string listaParts = participantes.substr(ini + 1, end - ini - 1);
            stringstream ssParts(listaParts);
            string idStr;
            while (getline(ssParts, idStr, ';')) {
                if (!idStr.empty())
                    partsIDs.push_back((size_t)stoi(idStr));
            }
        }
        Transacao *t = new(nothrow) Transacao;
        if (!t) 
            return;
        t->setTipo(stoi(tipo));
        t->setValor(stod(valorStr));
        t->setData(data);
        t->setHorario(horario);
        for (auto idPart : partsIDs) {
            Cliente* tempCliente = pesquisaID(vecCliente, idPart);
            if (tempCliente)
                t->pushClienteEnvolvido(tempCliente);
        }
        vecTransacao.push_back(t);    
    }
    for (auto pTransacao : vecTransacao) {
        for (auto pCliente : pTransacao->getClientes()) {
            if (pCliente)
                pCliente->pushTransacao(pTransacao);
        }
    }
    // Carregamento dos gerentes
    fstream gerentes;
    gerentes.open("./data/gerentes.csv", ios::in);
    if (!gerentes){
        cout << BOLD(RED("Erro ao abrir o arquivo. Tente novamente.\n")) << endl;
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
        if (campos.size() < 6) 
            continue;

        Gerente *pGerente = new(nothrow) Gerente;
        if (!pGerente)
            return;
        pGerente->setNome(campos[0]);
        pGerente->setLogin(campos[1]);
        pGerente->setSenha(campos[2]);
        pGerente->setTrabalho(campos[3]);
        pGerente->setID((size_t) stoi(campos[4]));

        // lista de clientes associados
        string clientesAssociados = campos.back();
        clientesAssociados = clientesAssociados.substr(1, clientesAssociados.size() - 2);
        stringstream ss2(clientesAssociados);
        string num;
        while (getline(ss2, num, ';')) {
            Cliente *pCliente = pesquisaID(vecCliente,(size_t) stoi(num));
            if (pCliente)
                pGerente->setCliente(pCliente);   
        }     
        vecGerente.push_back(pGerente);
        qtdGerentes++;
    }
    gerentes.close();
}

void Banco::salvaDados() {
    clearTerminal();
    // Salvamento dos clientes
    fstream clientes;
    clientes.open("./data/clientes.csv", ios::out);
    if (!clientes) {
        cout << BOLD(RED("Erro ao abrir o arquivo. Tente novamente.\n"));
        return;
    }
    clientes << "nome,login,senha,dataNasc,trabalho,ID,gerenteID,remuneracao,tipoConta,taxaRendimento,saldo,cartao\n";
    // nome,login,senha,dataNasc,trabalho,id,gerenteID,remuneracao,tipoConta,taxaRendimento,saldo,{numCartao;senhaCartao;limite;bloqueado;[fatura0:fatura1:...]}
    for (auto ptrCliente : vecCliente) {
        clientes <<  ptrCliente->getNome() << "," << ptrCliente->getLogin() << "," <<
            ptrCliente->getSenha() << "," << ptrCliente->getDataNasc() << "," <<
            ptrCliente->getTrabalho() << "," << ptrCliente->getID() << "," <<
            ptrCliente->getGerenteAssociadoID() << "," << ptrCliente->getRemuneracao() << "," <<
            ptrCliente->getTipoDeConta() << "," << ptrCliente->getRendimento() << "," <<
            ptrCliente->getSaldo() << ",";
        
        // Dados do cartão
        clientes << "{";
        if(ptrCliente->getCartao()){
            clientes << ptrCliente->getCartao()->getNumero() << ";"
                     << ptrCliente->getCartao()->getSenha() << ";"
                     << ptrCliente->getCartao()->getLimite() << ";"
                     << ((ptrCliente->getCartao()->getBloqueado()) ? "1" : "0") << ";"
                     << ptrCliente->getCartao()->getDisponivel() <<  ";";
            
            clientes << "[";
            for(int i = 0; i < MAXPARCELAS; i++){
                clientes << ptrCliente->getCartao()->getFatura(i);
                if (i < MAXPARCELAS - 1)
                    clientes << ":";
            }
            clientes << "]";
        }
        clientes << "}\n";
    }
    clientes.close();

    // Salvamento dos gerentes
    fstream gerentes;
    gerentes.open("./data/gerentes.csv", ios::out);
    if (!gerentes) {
        cout << "Erro ao abrir o arquivo. Tente novamente.\n";
        return;
    }
    gerentes << "nome,login,senha,trabalho,ID,clientesAssociados\n";
    for (auto ptrGerente : vecGerente) {
        gerentes <<
                ptrGerente->getNome() << "," << ptrGerente->getLogin() << "," <<
                ptrGerente->getSenha() << "," << ptrGerente->getTrabalho() << "," << ptrGerente->getID() << ",[";

        auto clientes = ptrGerente->getClientes();
        for (auto it = clientes.begin(); it != clientes.end(); ++it) {
            gerentes << (*it)->getID();
            if (next(it) != clientes.end()) gerentes << ";";
        }
        gerentes << "]\n";
    }
    gerentes.close();
       
    // Salvamento das transacoes
    // tipo,valor,data,horario,[id1;id2;id3]
    fstream transacoes;
    transacoes.open("./data/transacoes.csv", ios::out);
    if (!transacoes) {
        cout << BOLD(RED("Erro ao abrir o arquivo. Tente novamente.\n"));
    }
    
    transacoes << "tipo,valor,data,horario,clientesEnvolvidos\n";
    for(auto ptrTransacao : vecTransacao) {
        transacoes << ptrTransacao->getTipo() << "," << ptrTransacao->getValor() << ","
                   << ptrTransacao->getData() << "," << ptrTransacao->getHorario() << ",";
        
        transacoes << "[";
        auto clientes = ptrTransacao->getClientes();
        for (auto it = clientes.begin(); it != clientes.end(); ++it) {
            transacoes << (*it)->getID();
            if (next(it) != clientes.end()) 
                transacoes << ";";
        }
        transacoes << "]" << endl;   
        
    }
    transacoes.close();

    cout << BOLD(GREEN("Dados Salvos com Sucesso!\n"));
    confirmar(BOLD(GREEN("Pressione ENTER para prosseguir ao menu...\n")));
}

//simula um "ciclo" de rendimento da poupanca 
void Banco::cadernetaDePoupanca() {

    clearTerminal();
    cout << " ===== Calculando rendimento da caderneta de poupança =====" << endl << endl;


    bool rendimento = false;
    for(auto cliente: vecCliente) {
        //realiza o rendimento apenas para os clientes que possuem a conta do tipo poupanca
        if(cliente->getTipoDeConta() == "Poupanca") {
            double valorRend = cliente->getSaldo() * (cliente->getRendimento()/100);
            cout << "Valor do Rendimento R$:" << valorRend << " | " "Cliente:" 
                 << cliente->getNome() << " | " "ID:" << cliente->getID() << endl;
            cliente->rendimento();
            rendimento = true;
        }
    }
    //se ninguem teve rendimento, imprime que nenhum possui poupanca
    if(!rendimento)
        cout << "Nenhum cliente possui conta poupança!" << endl;
    cout << endl;

    confirmar("Pressione ENTER para retornar ao menu...");
}

void Banco::cartaoCredito(){

    //imprime o menu das operacoes envolvendo o cartao de credito
    while(1) {
        clearTerminal();
        int opt;
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
        if (!lerEntrada(opt, "Escolha uma opção ", ": "))
                return;

        switch(opt){
            case 1:
                criarCartao();
                break;
            case 2:
                listarCartao();
                break;
            case 3:
                alterarLimite();
                break;
            case 4:
                pagamentoParcelado();
                break;
            case 5:
                pagarFatura();
                break;
            case 6:
                bloquear();
                break;
            case 7:
                desbloquear();
                break;
            case 8:
                cout << "Voltando ao menu principal..." << endl;
                return;
            default:
                cout << "Entrada desconhecida. " << endl;
                confirmar("Pressione enter para tentar novamente" );
                break;
        }        
    }
}

void Banco::criarCartao() {

    //imprime cabecalho
    clearTerminal();
    cout << " ===== Criando Cartão de Crédito =====" << endl;

    //mostra todos os gerentes cadastrados no banco
    showVector(vecGerente, "");

    //ids para busca e senha para confirmacao
    size_t idGerente, idCliente;
    string senhaGerente;


    //loop responsavel pela leitura valida do id do gerente
    while(1) {
        if (!lerEntrada(idGerente, "Informe o ID do gerente responsável pela criação do cartão ", ": "))
            return;
        if (idGerente >= 1 && idGerente <= vecGerente.size())
            break;
        cout << "ID inválido. Digite novamente: ";
    }


    //busca gerente responsavel pela criacao do cartao
    Gerente* GerenteResponsavel = pesquisaID(vecGerente, idGerente);
    Cliente *ptrCliente = nullptr;


    //mostra clientes associados ao gerente
    cout << " ===== Clientes Associados =====" << endl;
    auto vec = GerenteResponsavel->getClientes();
    showVector(vec, "");


    //loop para escolher um cliente (dentre os associados ao gerente)
    while(1) {
        if (!lerEntrada(idCliente, "Informe o ID do cliente para criar um cartão de crédito ", ": "))
            return;
        ptrCliente = pesquisaID(vecCliente, idCliente);
        if (ptrCliente != nullptr)
            break;
        cout << "Cliente não encontrado\n";
    }
    
    //cria um novo cartão
    CartaoCredito *novoCartao = new(nothrow) CartaoCredito;
    if (!novoCartao)
        return;

    //limite inicial eh igual a 60% da renda do cliente
    double limite = 0.6 * ptrCliente->getRemuneracao();
    cout << BOLD(GREEN("Limite inicial de R$ ")) << printDinheiro(limite);

    //senha para o cartao
    std::string senha;
    if (!lerEntrada(senha, "Digite a senha para o cartão", ":"))
        return;


    //exige senha do gerente para confirmacao do processo 
    while(1) {
        if (!lerEntrada(senhaGerente, "Digite a senha do gerente responsável para finalizar ", ": "))
            return;
        if (GerenteResponsavel->getSenha() == senhaGerente)
            break;
        cout << "Senha Incorreta\n";
    }

    //preenche cartao com informacoes adquiridas
    novoCartao->setLimite(limite);
    novoCartao->setSenha(senha);
    novoCartao->setNumero(idCliente);
    novoCartao->associarCliente(ptrCliente);
    novoCartao->setDisponivel(limite);
    
    cout << endl;
    ptrCliente->setCartao(novoCartao);
    cout << "Cartão de crédito criado com sucesso para o cliente " << ptrCliente->getNome() << "! " << endl;
    confirmar("Pressione ENTER para retornar ao menu...");
}

void Banco::alterarStatusCartao(bool bloquear) {
    // imprime cabecalho dinamico
    clearTerminal();
    if (bloquear) {
        cout << "===== BLOQUEAR CARTAO =====\n";
    } else {
        cout << "===== DESBLOQUEAR CARTAO =====\n";
    }

    // mostra os clientes cadastrados no banco
    showVector(vecCliente, "");

    // realiza a leitura do id
    size_t id;
    if (!lerEntrada(id, "Informe o ID do cliente", ": "))
        return;

    // busca o cliente desejado pelo id
    Cliente *ptrCliente = pesquisaID(vecCliente, id);
    if (!ptrCliente) {
        cout << BOLD(RED("Cliente nao encontrado!\n"));
        confirmar();
        return;
    }

    // pega o cartao do cliente desejado
    CartaoCredito *cartao = ptrCliente->getCartao();
    if (!cartao) {
        cout << "Este cliente nao possui cartao de credito.\n";
        confirmar();
        return;
    }

    // verifica a senha (padronizado com loop para ambas as acoes)
    string senha;
    while (true) {
        if (!lerEntrada(senha, "Digite a senha do Cartão", ": "))
            return;
        
        if (senha == cartao->getSenha()) 
            break;
        
        cout << "Senha incorreta!\n";
    }

    // verifica o status atual e aplica a mudanca baseada no parametro
    if (bloquear) {
        if (cartao->getBloqueado()) {
            cout << "Cartao ja esta bloqueado.\n";
            confirmar();
            return;
        }
        cartao->setBloqueado(true);
        cout << "Cartao bloqueado com sucesso!\n";
    } else {
        if (!cartao->getBloqueado()) {
            cout << "Cartao ja esta desbloqueado.\n";
            confirmar();
            return;
        }
        cartao->setBloqueado(false);
        cout << "Cartao desbloqueado com sucesso!\n";
    }

    confirmar();
}

//realiza o mesmo processo, alterando apenas o valor de setBloqueado ao fim
void Banco::bloquear(){
    alterarStatusCartao(true);
}
void Banco::desbloquear(){
    alterarStatusCartao(false);
}

void Banco::alterarLimite() {
    clearTerminal();

    cout << "===== ALTERAR LIMITE DO CARTAO =====\n";

    //mostra os clientes 
    showVector(vecCliente, "");
    size_t id;
    if (!lerEntrada(id, "Informe o ID do cliente", ": "))
        return;
    Cliente *ptrCliente = pesquisaID(vecCliente, id);
    if (!ptrCliente) {
        cout << BOLD(RED("Cliente nao encontrado!\n"));
        confirmar();
        return;    
    }

    CartaoCredito *cartao = ptrCliente->getCartao();
    if (!cartao) {
        cout << "Cliente nao possui cartao de credito.\n";
        confirmar();
        return;
    }
    if(cartao->getBloqueado()) {
        cout << "Cartao esta bloqueado. Desbloqueie para alterar o limite.\n";
        confirmar();
        return;
    }

    string senha;
    if (!lerEntrada(senha, "Digite a senha do cliente", ": "))
        return;
    if (senha != ptrCliente->getCartao()->getSenha()) {
        cout << "Senha incorreta!\n";
        confirmar();
        return;
    }

    cout << "Limite atual: R$ " << cartao->getLimite() << endl;
    double limiteAntigo = cartao->getLimite();
    double novoLimite;
    while (true) {
        if (!lerEntrada(novoLimite, "Digite o novo limite", ": R$ "))
            return;
        if (novoLimite >= 0)
            break;

        cout << "Limite invalido!\n";
    }

    cartao->setDisponivel(cartao->getDisponivel() + novoLimite - cartao->getLimite());
    cartao->setLimite(novoLimite);

    cout << "\nLimite alterado com sucesso!\n";
    cout << "Limite alterado de R$ " << limiteAntigo << " para R$ " << novoLimite << endl;

    confirmar("Pressione ENTER para retornar...");
}

void Banco::pagamentoParcelado() {
    clearTerminal();

    cout << "===== PAGAMENTO PARCELADO COM CARTAO DE CREDITO =====\n";
    size_t id;

    showVector(vecCliente, "");
    if (!lerEntrada(id, "Informe o ID do cliente", ": "))
        return;

    Cliente *cliente = pesquisaID(vecCliente, id);

    if (!cliente) {
        cout << BOLD(RED("Cliente nao encontrado!\n"));
        confirmar();
        return;
    }

    CartaoCredito *cartao = cliente->getCartao();

    if (!cartao) {
        cout << "Cliente nao possui cartao.\n";
        confirmar();
        return;
    }

    if (cartao->getBloqueado()) {
        cout << "Cartão bloqueado. Não pode parcelar.\n";
        confirmar();
        return;
    }

    double valor;
    int parcelas;

    if (!lerEntrada(valor, "Valor da compra", ": R$ "))
        return;
        
    if(valor <= 0)
        cout << "Valor invalido.";
    if (valor > cartao->getDisponivel()) {
        cout << "Limite insuficiente.\n";
        confirmar();
        return;
    }

    if (!lerEntrada(parcelas, "Quantidade de parcelas", ": "))
        return;

    if (parcelas <= 0 || parcelas > MAXPARCELAS) {
        cout << "Quantidade de parcelas invalida.\n";
        confirmar();
        return;
    }
    string senha;
    if (!lerEntrada(senha, "Digite a senha do Cartão", ": "))
        return;

    if (senha != cartao->getSenha()) {
        cout << "Senha incorreta!\n";
        confirmar();
        return;
    }

    cartao->insereFaturas(valor, parcelas);
    cout << "\nCompra aprovada!\n";
    cout << "Valor total: R$ " << valor << endl;
    cout << "Parcelas: " << parcelas << "x de R$ " << valor / parcelas << endl;
    confirmar();
}

void Banco::pagarFatura() {
    clearTerminal();
    cout << BOLD(GREEN("===== PAGAR FATURA DO CARTAO DE CREDITO =====\n")) << endl;
    size_t id;
    showVector(vecCliente, "");

    if (!lerEntrada(id, "Informe o ID do cliente", ": "))
        return;

    Cliente *cliente = pesquisaID(vecCliente, id);
    if (!cliente) {
        cout << (BOLD(RED("Cliente nao encontrado.\n")));
        confirmar();
        return;
    }

    CartaoCredito *cartao = cliente->getCartao();
    if (!cartao) {
        cout << "Cliente nao possui cartao.\n";
        confirmar();
        return;
    }

    cout << "Fatura atual: R$ " << cartao->getFatura() << endl;

    double pagamento;

    while(1){
        if (!lerEntrada(pagamento, "Valor para pagamento",": R$ "))
            return;
        if(pagamento >= 0)
            break;
        cout << BOLD(YELLOW("ERRO: Valor de pagamento maior que o da fatura atual.\n")); 
    }

    if (pagamento <= 0) {
        cout << BOLD(RED("Valor invalido.\n"));
        confirmar();
        return;
    }

    if (pagamento > cliente->getSaldo()) {
        cout << BOLD(RED("Saldo insuficiente. Tente Novamente\n"));
        confirmar();
        return;
    }
    string senha;
    if (!lerEntrada(senha, BOLD("Digite a senha do Cartão"), ": "))
        return;

    if (senha != cliente->getCartao()->getSenha()) {
        cout << BOLD(RED("Senha incorreta!\n"));
        confirmar();
        return;
    }

    cartao->pagarFaturaAtual(pagamento);    
    confirmar();
}

Banco::~Banco(){}   