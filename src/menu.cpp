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
        if (!lerEntrada(id, BOLD("Escolha o ID do gerente"), ":")) {
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
    cout << " ========== Gerente cadastrado com sucesso! ==========" << endl;

    cout << BOLD(YELLOW()) << endl;
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
        if (!lerEntrada(tipoTransacao, "Escolha uma opção: ")) {
            cancelaTransacao(novaTransacao);
            return;
        }
        if(tipoTransacao >= 1 && tipoTransacao <= 3)
            break;
        cout << "Opção inválida. Tente novamente" << endl;
    }

    // Fazer verificação de alguma forma
    if (!lerEntrada(temp, "Informe a data: "))  {
        cancelaTransacao(novaTransacao);
        return;
    }
    novaTransacao->setData(temp);


    if (!lerEntrada(temp, "Informe o horário: ")) {
        cancelaTransacao(novaTransacao);
        return;
    }
    novaTransacao->setHorario(temp);

    // Seleciona o cliente a realizar o saque, deposito, transferencia
    showVector(vecCliente, "====== Clientes Cadastrados ======");
    Cliente *ptrRemetente;
    while(1) {
        if (!lerEntrada(id, "Selecione o ID do cliente (remetente) para realizar a ação: ")) {
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
                if (!lerEntrada(quant, "Informe a quantidade de destinatários para o pagamento: ")) {
                    cancelaTransacao(novaTransacao);
                    return;
                }
                if (quant >= 1 && quant < qtdClientes)
                    break;
                cout << BOLD(YELLOW("Quantidade inválida, digite novamente."));
            }

            if (!lerEntrada(valor, "Informe o valor que será transferido para cada destinatário")) {
                cancelaTransacao(novaTransacao);
                return;
            }
            novaTransacao->setValor(valor);
            // Lê destinatário(s) e os adiciona no vetor clientesEnvolvidos
            for(int i = 0; i < quant; i++){
                do{
                    if (!lerEntrada(idDestinatario, "Informe o ID do destinatário: ")) {
                        cancelaTransacao(novaTransacao);
                        return;
                    }
                    if(id < 1 || idDestinatario > vecCliente.size())
                        cout << endl << "ID inválido. Digite novamente." << endl;
                } while(idDestinatario < 1 || idDestinatario > vecCliente.size());
                
                Cliente *ptrDestinatario = pesquisaID(vecCliente, idDestinatario);
                if(ptrDestinatario)
                    novaTransacao->pushClienteEnvolvido(ptrDestinatario);
            }
            
            for(int i=4 ;i>0; i--) {    
                if (!lerEntrada(verify, "Digite a sua senha para finalizar a transacao: ")) {
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
                if (!lerEntrada(valor, "\nInsira outro valor (ou digite 0 para cancelar): ")) {
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
                if (!lerEntrada(verify,"Digite a sua senha para finalizar a transacao", ":")) {
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
                if (!lerEntrada(verify, "Digite a sua senha para finalizar a transacao: ")) {
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
        if (!lerEntrada(id, "Informe o ID do cliente para exibir o extrato"))
            return;
        if (id >= 1 && id <= vecCliente.size())
            break;
        cout << "ID inválido. Digite novamente: ";
    }
    
    Cliente* clienteExtrato = pesquisaID(vecCliente, id);
    cout << "\n===== EXTRATO DE " << clienteExtrato->getNome() << " =====\n";
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
    confirmar();
}

void Banco::associarGerenteCliente() {
    clearTerminal();
    cout << BOLD(GREEN("===== Associando um Gerente a Cliente =====\n")) << endl;
    int qtd;
    
    for (auto gerente : vecGerente) 
        cout << gerente->getID() << " | " << gerente->getNome() << endl;
    cout << BOLD(YELLOW("Selecione um gerente para associar clientes\n"));
    size_t ID;  
    
    while (1) {
        if (!lerEntrada(ID, BOLD(YELLOW("Escolha o ID do gerente")), ":"))
            return;
        if (ID >= 1 && ID <= vecGerente.size())
            break;
        cout << BOLD(RED("ERRO: ID não encontrado. Tente novamente: "));
    }

    Gerente *novoGerente;
    for (auto g : vecGerente) 
        if (g->getID() == ID)
            novoGerente = g;

    while(1) {
        if (!lerEntrada(qtd,"Digite quantos clientes deseja vincular", ":"))
            return;
        if (qtd >= 1 && qtd <= qtdClientes)
            break;
        cout << BOLD(RED("ERRO: Quantidade inválida!")); 
    }

    cout << BOLD(GREEN("=== CLIENTES DISPONIVEIS PARA ALTERAR ===\n"));
    for(auto cliente : vecCliente){
        if(cliente->getGerenteAssociadoID() != novoGerente->getID())
            cout << "ID: " << cliente->getID() << " | Nome: " << cliente->getNome() << endl;
    }
    
    for(int i = 0; i < qtd; i++) {
        size_t idCliente;
        if (!lerEntrada(idCliente, "Digite o ID do cliente", ":"))
            return;
        Cliente *ptr = pesquisaID(vecCliente, idCliente);
        if (ptr) {
            if (ptr->getGerenteAssociadoID() != 0){
                // Desassociar 
            }
            ptr->setGerenteAssociadoID(novoGerente->getID());
            novoGerente->setCliente(ptr);
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
    if (!lerEntrada(nome, "Informe o nome do Cliente: "))
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
    if (!lerEntrada(nome, "Informe o nome do Gerente: "))
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
    if (!lerEntrada(id, BOLD("Informe o id do Cliente"), ":"))
        return;

    bool encontrou = false;
    for(auto cliente : vecCliente) {
        if(cliente->getID() == id) {
            if(cliente->getCartao() != nullptr){
                cout << BOLD(GREEN("\n===== CARTAO ENCONTRADO =====\n"));
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
    // nome,login,senha,dataNasc,trabalho,id,gerenteID,remuneracao,tipoConta,taxaRendimento,saldo
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
        qtdClientes++;
    }

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
    clientes.close();
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
    clientes << "nome,login,senha,dataNasc,trabalho,ID,gerenteID,remuneracao,tipoConta,taxaRendimento,saldo\n";
    // nome,login,senha,dataNasc,trabalho,id,gerenteID,remuneracao,tipoConta,taxaRendimento,saldo
    for (auto ptrCliente : vecCliente) {
        clientes <<  ptrCliente->getNome() << "," << ptrCliente->getLogin() << "," <<
            ptrCliente->getSenha() << "," << ptrCliente->getDataNasc() << "," <<
            ptrCliente->getTrabalho() << "," << ptrCliente->getID() << "," <<
            ptrCliente->getGerenteAssociadoID() << "," << ptrCliente->getRemuneracao() << "," <<
            ptrCliente->getTipoDeConta() << "," << ptrCliente->getRendimento() << "," <<
            ptrCliente->getSaldo() << "\n";
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

void Banco::cadernetaDePoupanca() {
    clearTerminal();
    cout << " ===== Calculando rendimento da caderneta de poupança =====" << endl << endl;
    bool rendimento = false;
    for(auto cliente: vecCliente) {
        if(cliente->getTipoDeConta() == "Poupanca") {
            double valorRend = cliente->getSaldo() * (cliente->getRendimento()/100);
            cout << "Valor do Rendimento R$:" << valorRend << " | " "Cliente:" 
                 << cliente->getNome() << " | " "ID:" << cliente->getID() << endl;
            cliente->rendimento();
            rendimento = true;
        }
    }
    if(!rendimento)
        cout << "Nenhum cliente possui conta poupança!" << endl;
    cout << endl;
    confirmar("Pressione ENTER para retornar ao menu...");
}

void Banco::cartaoCredito(){

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
        if (!lerEntrada(opt, "Escolha uma opção", ":"))
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
    clearTerminal();
    cout << " ===== Criando Cartão de Crédito =====" << endl;

    showVector(vecCliente, "");

    size_t id;
    
    while(1) {
        if (!lerEntrada(id, "Informe o ID do cliente para criar um cartão de crédito"))
            return;
        if (id >= 1 && id <= vecCliente.size())
            break;
        cout << "ID inválido. Digite novamente: ";
    }
    Cliente *ptrCliente = pesquisaID(vecCliente, id);
    CartaoCredito *novoCartao = new(nothrow) CartaoCredito;
    if (!novoCartao)
        return;
    double limite = 0.6 * ptrCliente->getRemuneracao();
    cout << BOLD(GREEN("Limite inicial de R$ " << limite << "!\n"));
    std::string senha;
    if (!lerEntrada(senha, "Digite a senha para o cartão", ":"))
        return;

    novoCartao->setLimite(limite);
    novoCartao->setSenha(senha);
    novoCartao->setFatura(0);
    novoCartao->setBloqueado(false);
    
    novoCartao->setNumero(id);
    
    cout << endl;
    ptrCliente->setCartao(novoCartao);
    cout << "Cartão de crédito criado com sucesso para o cliente " << ptrCliente->getNome() << "! " << endl;
    confirmar("Pressione ENTER para retornar ao menu...");
}

void Banco::bloquear(){
    clearTerminal();

    cout << "===== BLOQUEAR CARTAO =====\n";

    showVector(vecCliente, "");

    size_t id;

    if (!lerEntrada(id, "Informe o ID do cliente"))
        return;

    Cliente *ptrCliente = pesquisaID(vecCliente, id);

    if (!ptrCliente) {
        cout << BOLD(RED("Cliente nao encontrado!\n"));
        confirmar();
        return;
    }

    CartaoCredito *cartao = ptrCliente->getCartao();

    if (!cartao) {
        cout << "Este cliente nao possui cartao de credito.\n";
        confirmar();
        return;
    }

    string senha;

    if (!lerEntrada(senha, "Digite a senha do Cartão"))
        return;

    if (senha != ptrCliente->getCartao()->getSenha()) {
        cout << "Senha incorreta!\n";
        confirmar();
        return;
    }

    if (cartao->getBloqueado()) {
        cout << "Cartao ja esta bloqueado.\n";
        confirmar();
        return;
    }

    cartao->setBloqueado(true);

    cout << "Cartao bloqueado com sucesso!\n";
    confirmar();
}
void Banco::desbloquear(){
    clearTerminal();

    cout << "===== DESBLOQUEAR CARTAO =====\n";

    showVector(vecCliente, "");

    size_t id;

    if (!lerEntrada(id, "Informe o ID do cliente"))
        return;

    Cliente *ptrCliente = pesquisaID(vecCliente, id);

    if (!ptrCliente) {
        cout << BOLD(RED("Cliente nao encontrado!\n"));
        confirmar();
        return;
    }

    CartaoCredito *cartao = ptrCliente->getCartao();

    if (!cartao) {
        cout << "Este cliente nao possui cartao de credito.\n";
        confirmar();
        return;
    }

    string senha;

    if (!lerEntrada(senha, "Digite a senha do Cartão"))
        return;

    if (senha != ptrCliente->getCartao()->getSenha()) {
        cout << "Senha incorreta!\n";
        confirmar();
        return;
    }
    
    if (!cartao->getBloqueado()) {
        cout << "Cartao ja esta desbloqueado.\n";
        confirmar();
        return;
    }

    cartao->setBloqueado(false);

    cout << "Cartao desbloqueado com sucesso!\n";
    confirmar();    
}

void Banco::alterarLimite() {
    clearTerminal();

    cout << "===== ALTERAR LIMITE DO CARTAO =====\n";

    showVector(vecCliente, "");

    size_t id;

    if (!lerEntrada(id, "Informe o ID do cliente"))
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

    if (!lerEntrada(senha, "Digite a senha do cliente"))
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
    if (!lerEntrada(id, "Informe o ID do cliente"))
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

    if (!lerEntrada(parcelas, "Quantidade de parcelas"))
        return;

    if (valor <= 0 || parcelas <= 0) {
        cout << "Valores invalidos.\n";
        confirmar();
        return;
    }

    double disponivel = cartao->getLimite() - cartao->getFatura();

    if (valor > disponivel) {
        cout << "Limite insuficiente.\n";
        confirmar();
        return;
    }


    string senha;

    if (!lerEntrada(senha, "Digite a senha do Cartão"))
        return;

    if (senha != cliente->getCartao()->getSenha()) {
        cout << "Senha incorreta!\n";
        confirmar();
        return;
    }
    cartao->setFatura(cartao->getFatura() + valor);

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

    if (!lerEntrada(id, "Informe o ID do cliente"))
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
        if(pagamento >= 0 && pagamento <= cartao->getFatura())
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
    if (!lerEntrada(senha, BOLD("Digite a senha do Cartão")))
        return;

    if (senha != cliente->getCartao()->getSenha()) {
        cout << BOLD(RED("Senha incorreta!\n"));
        confirmar();
        return;
    }

    cliente->setSaldo(cliente->getSaldo() - pagamento);

    double novaFatura = cartao->getFatura() - pagamento;
    cartao->setFatura(novaFatura);
    cout << "\nPagamento realizado com sucesso!\n";
 
    cout << "Fatura restante: R$ " << cartao->getFatura() << endl;
    confirmar();
}

Banco::~Banco(){}   