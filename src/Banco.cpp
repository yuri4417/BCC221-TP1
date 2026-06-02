#include <iostream>
#include <iomanip>
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

// ============================
// PRIVADOS
// ============================
bool Banco::verificaSenha(const string& senhaCorreta, const string& prompt) {
    string verify;
    for(int i = 4; i > 0; i--) {
        if (!lerEntrada(verify, prompt)) {
            return false;
        }
        if (verify == senhaCorreta) {
            cout << BOLD(GREEN("Senha validada com sucesso!")) << endl;
            return true;
        }
        if (i > 1) {
            cout << BOLD(YELLOW("Senha inválida! Você tem " + to_string(i-1) + " tentativas!")) << endl;
        }
    }
    cout << BOLD(RED("Excesso de tentativas atingido! Cancelando operação"));
    confirmar(BOLD(RED("Pressione ENTER para retornar")));
    return false;
}

void cancelaTransacao(Transacao *t) {
    delete t;
    confirmar(BOLD(RED("Transação CANCELADA. Pressione ENTER para retornar ao menu... ")));
}



// ===========================
// PUBLICOS
// ===========================
Banco::Banco(int qtdC, int qtdG):
    qtdClientes(qtdC), qtdGerentes(qtdG){ carregaDados(); }
Banco::~Banco(){
    for (auto transacao : vecTransacao)
        delete transacao;
    for (auto gerente : vecGerente)
        delete gerente;
    for (auto cliente : vecCliente)
        delete cliente;
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
        cout << BOLD(MAGENTA("=================================================")) <<endl;
        int opt;
        if (!lerEntrada(opt, BOLD(GREEN("Escolha uma opção")), ": "))
            return;
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
                if (perguntaSN(BOLD(RED("Tem certeza que deseja sair? (S/N): "))))
                    return;
                break;
            default:
               cout << BOLD(YELLOW("Opcao inválida. Tente novamente.")) << endl;
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

    // Associar o cliente a um gerente
    cout << BOLD(GREEN("\n ===== Associando o Cliente a um Gerente =====")) << endl;
    showVector(vecGerente, BOLD(GREEN("====== Selecione o ID do gerente para associar ao cliente ======")));
    Gerente *ptrGerente = pesquisaPessoa(vecGerente, "Escolha o ID do gerente");
    if (!ptrGerente) {
        delete novoCliente;
        return;
    }
    novoCliente->setGerenteAssociadoID(ptrGerente->getID());
    ptrGerente->setCliente(novoCliente);
    qtdClientes++;
    vecCliente.push_back(novoCliente);
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

void Banco::criarTransacao() {
    Transacao* novaTransacao = new(nothrow) Transacao;
    if (!novaTransacao)
        return;
    int tipoTransacao;
    int quant = 0;
    double valor;
    string data;
    string horario;
    
    clearTerminal();
    cout << BOLD(GREEN(" ===== Iniciando Transacao =====")) << endl;
    
    cout << BOLD(YELLOW("Informe o tipo de transação: ")) << endl;
    cout << BOLD("1. Transferência") << endl;
    cout << BOLD("2. Depósito" ) << endl;
    cout << BOLD("3. Saque") << endl;
    cout << endl << BOLD(GREEN("================================")) << endl;
    
    while(1) {
        if (!lerEntrada(tipoTransacao, "Escolha uma opção", ": ")) {
            cancelaTransacao(novaTransacao);
            return;
        }
        if(tipoTransacao >= 1 && tipoTransacao <= 3)
            break;
        cout << BOLD(RED("Opção inválida. Tente novamente")) << endl;
    }

    if (!lerEntrada(data, "Informe a data", ": "))  {
        cancelaTransacao(novaTransacao);
        return;
    }

    if (!lerEntrada(horario, "Informe o horário", ": ")) {
        cancelaTransacao(novaTransacao);
        return;
    }

    novaTransacao->setData(data);
    novaTransacao->setHorario(horario);
    novaTransacao->setTipo(tipoTransacao);

    showVector(vecCliente, BOLD(GREEN("====== Clientes Cadastrados ======")));
    Cliente *ptrRemetente = pesquisaPessoa(vecCliente, "Selecione o ID do cliente (remetente) para realizar a ação");
    if (!ptrRemetente) {
        cancelaTransacao(novaTransacao);
        return;
    }

    switch (tipoTransacao) {
        case 1: 
        {
            size_t idDestinatario;
            while(1) {
                if (!lerEntrada(quant, "Informe a quantidade de destinatários para o pagamento", ": ")) {
                    cancelaTransacao(novaTransacao);
                    return;
                }
                if (quant >= 1 && quant < qtdClientes)
                    break;
                cout << BOLD(YELLOW("Quantidade inválida, digite novamente.")) << endl;
            }

            if (!lerEntrada(valor, "Informe o valor que será transferido para cada destinatário", ": ")) {
                cancelaTransacao(novaTransacao);
                return;
            }
            if(valor <= 0) {
                cout << BOLD(RED("Valor inválido")) << endl;
                cancelaTransacao(novaTransacao);
                return;
            }
            
            novaTransacao->setValor(valor);
            novaTransacao->pushClienteEnvolvido(ptrRemetente);
            
            for(int i = 0; i < quant; i++){
                do{
                    if (!lerEntrada(idDestinatario, "Informe o ID do destinatário", ": ")) {
                        cancelaTransacao(novaTransacao);
                        return;
                    }
                    if(idDestinatario < 1 || idDestinatario > vecCliente.size() || idDestinatario == ptrRemetente->getID())
                        cout << BOLD(YELLOW("ID inválido. Digite novamente.")) << endl;
                    
                } while(idDestinatario < 1 || idDestinatario > vecCliente.size() || idDestinatario == ptrRemetente->getID());
                
                Cliente *ptrDestinatario = pesquisaID(vecCliente, idDestinatario);
                if(ptrDestinatario)
                    novaTransacao->pushClienteEnvolvido(ptrDestinatario);
            }
            
            if (!verificaSenha(ptrRemetente->getSenha(), "Digite a sua senha para finalizar a transacao")) {
                cancelaTransacao(novaTransacao);
                return;
            }
            while (!novaTransacao->acao(novaTransacao->getClientes(), valor)) {
                if (!lerEntrada(valor, "Insira outro valor", ": R$ ")) {
                    cancelaTransacao(novaTransacao);
                    return;
                }
                novaTransacao->setValor(valor);
            }
            
            ptrRemetente->pushTransacao(novaTransacao);
            for(auto cliente : novaTransacao->getClientes()) 
                if(cliente != ptrRemetente)
                    cliente->pushTransacao(novaTransacao);
            cout << BOLD(GREEN("Transferência concluída com sucesso!")) << endl;
            confirmar("Pressione ENTER para retornar ao menu...");
        }    
            break;
        case 2:
        {
            Cliente *clienteDeposito = ptrRemetente;
            if (!lerEntrada(valor, "Informe o valor do depósito", ": R$ ")) {
                cancelaTransacao(novaTransacao);
                return;
            }
            if (!verificaSenha(ptrRemetente->getSenha(), "Digite a sua senha para finalizar a transacao")) {
                cancelaTransacao(novaTransacao);
                return;
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
            Cliente *clienteSaque = ptrRemetente;
           
            while (1) {
                if (!lerEntrada(valor, "Digite o valor a ser sacado", ": R$ ")) {
                    cancelaTransacao(novaTransacao);
                    return;
                }
                if (valor <= clienteSaque->getSaldo())
                    break;
                cout << BOLD(YELLOW("Valor inválido. Digite novamente: "));
            }
            if (!verificaSenha(ptrRemetente->getSenha(), "Digite a sua senha para finalizar a transacao")) {
                cancelaTransacao(novaTransacao);
                return;
            }
            cout << BOLD(GREEN("Valor sacado: ")) << printDinheiro(valor) << endl;
            novaTransacao->setValor(valor); 
            
            if(novaTransacao->acao(clienteSaque, -valor)) {
                novaTransacao->pushClienteEnvolvido(clienteSaque);
                clienteSaque->pushTransacao(novaTransacao);
            }
            confirmar("Pressione ENTER para retornar ao menu...");
        }
        break;
        default:
            cout << BOLD(RED("Opção inválida. Tente novamente.")) << endl;       
            break;        
    }
    vecTransacao.push_back(novaTransacao);
}

void Banco::exibirExtrato() {
    clearTerminal();
    cout << BOLD(GREEN("===== Exibindo Extrato de Um Cliente =====")) << endl;
    for(auto clientes: vecCliente)
        cout << BOLD("ID: " + to_string(clientes->getID()) + " | Nome: " + clientes->getNome()) << endl;    
    Cliente* clienteExtrato = pesquisaPessoa(vecCliente, "Informe o ID do cliente para exibir o extrato");
    if (!clienteExtrato)
        return;

    cout << BOLD(CYAN("\n===== EXTRATO DE " + clienteExtrato->getNome() + " =====")) << endl;
    for(auto transacao : clienteExtrato->getTransacoes()) {
        size_t idRemetente = transacao->getClientes()[0]->getID();
        string nomeRemetente = transacao->getClientes()[0]->getNome();

        cout << BOLD(GREEN("Data: " + transacao->getData())) << endl;
        cout << BOLD(GREEN("Horário: " + transacao->getHorario())) << endl;
        cout << BOLD(GREEN("Tipo: ")) << (transacao->getTipo() == 1 ? BOLD(GREEN("Transferência")) : (transacao->getTipo() == 2 ? BOLD(GREEN("Depósito")) : BOLD(GREEN("Saque")))) << endl;
        cout << BOLD(GREEN("Valor: R$ ")) << printDinheiro(transacao->getValor()) << endl;

        if(transacao->getTipo() == 1) {
            if(idRemetente == clienteExtrato->getID())
                cout << BOLD(RED("Transação para o(s) Cliente(s): ")) << endl;
            else{
                cout << BOLD(GREEN("Transação recebida de " + nomeRemetente)) << endl;
                continue;
            }
            for(auto cliente : transacao->getClientes())
                if(cliente->getID() != clienteExtrato->getID())
                    cout << BOLD("ID: " + to_string(cliente->getID()) + " | Nome: " + cliente->getNome()) << endl;
        }
        cout << endl;
        cout << BOLD(CYAN("==================================\n"));
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
    
    Gerente *novoGerente = pesquisaPessoa(vecGerente, "Escolha o ID do gerente");
    if (!novoGerente)
        return;
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
            cout << BOLD("ID: " + to_string(cliente->getID()) + " | Nome: " + cliente->getNome()) << endl;
    }
    
    for(int i = 0; i < qtd; i++) {
        size_t idGerenteAntigo;
        Cliente *ptr = pesquisaPessoa(vecCliente, "Digite o ID do cliente");
        if (!ptr)
            return;

        if (ptr->getGerenteAssociadoID() == novoGerente->getID()) {
            cout << BOLD(YELLOW("O cliente " + ptr->getNome() + " já está associado a este gerente. Nenhuma alteração feita.")) << endl;
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
        
        else {
            cout<< BOLD(YELLOW("Cliente não encontrado. Tente novamente.")) << endl;
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
    if (!lerEntrada(nome, "Informe o nome do Cliente",": "))
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
        cout << BOLD(RED("Cliente não encontrado!")) << endl;
    confirmar(BOLD(GREEN("Pressione qualquer tecla para voltar ao menu...")));
}

void Banco::listarGerentes() {
    string nome;
    clearTerminal();
    cout << BOLD(GREEN("===== Iniciando Listagem de Gerente =====")) << endl;
    for(auto gerentes: vecGerente)
        cout << *gerentes;
    if (!lerEntrada(nome, "Informe o nome do Gerente",  ": "))
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

void Banco::listarCartao(){   
    clearTerminal();
    cout << BOLD(GREEN("===== Iniciando Listagem do Cartão de Cliente =====")) << endl;
    for(auto clientes: vecCliente)
        cout << *clientes;
    Cliente *pCliente = pesquisaPessoa(vecCliente, "Informe o id do Cliente");
    if (!pCliente)
        return;

    if(pCliente->getCartao() != nullptr) {
        cout << BOLD(GREEN("\n===== CARTÃO ENCONTRADO =====\n"));
        cout << *pCliente;
        cout << *(pCliente->getCartao());
    }
    else
        cout << BOLD(YELLOW("=== Cliente não possui cartão de crédito ===\n"));
    confirmar(BOLD(GREEN("Pressione qualquer tecla para voltar ao menu...")));
}

void Banco::carregaDados() {
    // Carregamento dos clientes
    // nome,login,senha,dataNasc,trabalho,id,gerenteID,remuneracao,tipoConta,taxaRendimento,saldo,{numCartao;senhaCartao;limite;bloqueado;[fatura0:fatura1:...]}
    fstream clientes;   
    string linha;
    clientes.open("./data/clientes.csv", ios::in);
    if (!clientes){
        cout << BOLD(RED("Arquivos não identificados. Iniciando banco de dados vazio.")) << endl;
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

                novoCartao->setNumero((size_t) stoull(dadosCartao[0]));
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
        cout << BOLD(RED("Erro ao abrir o arquivo. Tente novamente.\n"));
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
}

//simula um "ciclo" de rendimento da poupanca 
void Banco::cadernetaDePoupanca() {

    clearTerminal();
    cout << BOLD(CYAN(" ===== Calculando rendimento da caderneta de poupança =====" )) << endl;
    bool rendimento = false;
    for(auto cliente: vecCliente) {
        //realiza o rendimento apenas para os clientes que possuem a conta do tipo poupanca
        if(cliente->getTipoDeConta() == "Poupanca") {
            double valorRend = cliente->getSaldo() * (cliente->getRendimento()/100.0);
            cout << BOLD("Valor do Rendimento: ") << printDinheiro(valorRend) 
            << BOLD(" | " "Cliente:" + cliente->getNome() + " | " "ID: " + to_string(cliente->getID()))  << endl;
            cliente->rendimento();
            rendimento = true;
        }
    }
    //se ninguem teve rendimento, imprime que nenhum possui poupanca
    if(!rendimento)
        cout << BOLD(YELLOW("Nenhum cliente possui conta poupança!")) << endl;
    cout << endl;

    confirmar(BOLD(GREEN("Pressione ENTER para retornar ao menu...")));
}

void Banco::cartaoCredito(){

    //imprime o menu das operacoes envolvendo o cartao de credito
    while(1) {
        clearTerminal();
        int opt;
        cout << BOLD(CYAN(" ===== Gerenciamento de Cartões de Crédito =====")) << endl;
        cout << BOLD(GREEN("1. Criar cartão de crédito")) << endl;
        cout << BOLD(GREEN("2. Pagar fatura")) << endl;
        cout << BOLD(GREEN("3. Desbloquear cartão")) << endl;
        cout << BOLD(CYAN("4. Listar cartões de crédito")) << endl;
        cout << BOLD(YELLOW("5. Alterar limite do cartão de crédito")) << endl;
        cout << BOLD(YELLOW("6. Pagamento parcelado")) << endl;
        cout << BOLD(RED("7. Bloquear cartão")) << endl;
        cout << BOLD(RED("8. Voltar ao menu principal")) << endl;
        cout << BOLD(CYAN("==================================================")) << endl;
        if (!lerEntrada(opt, "Escolha uma opção", ": "))
                return;
        switch(opt){
            case 1:
                criarCartao();
                break;
            case 2:
                pagarFatura();
                break;
            case 3:
                alterarStatusCartao(false);
                break;
            case 4:
                listarCartao();
                break;
            case 5:
                alterarLimite();
                break;
            case 6:
                pagamentoParcelado();
                break;
            case 7:
                alterarStatusCartao(true);
                break;
            case 8:
                return;
            default:
                confirmar(BOLD(RED("Opção Desconhecida. Pressione enter para tentar novamente")));
                break;
        }        
    }
}

void Banco::criarCartao() {

    //imprime cabecalho
    clearTerminal();
    cout << BOLD(CYAN("===== Criando Cartão de Crédito =====")) << endl;

    //mostra todos os gerentes cadastrados no banco
    showVector(vecGerente, "");

    //ids para busca e senha para confirmacao
    size_t idCliente;
    string senhaGerente;
    //busca gerente responsavel pela criacao do cartao
    Gerente* GerenteResponsavel = pesquisaPessoa(vecGerente, "Informe o ID do gerente responsável pela criação do cartão");
    if (!GerenteResponsavel)
        return;
    Cliente *ptrCliente = nullptr;
    //mostra clientes associados ao gerente
    cout << BOLD(CYAN("===== Clientes Associados =====")) << endl;
    auto vec = GerenteResponsavel->getClientes();
    showVector(vec, "");


    //loop para escolher um cliente (dentre os associados ao gerente)
    while(1) {
        if (!lerEntrada(idCliente, "Informe o ID do cliente para criar um cartão de crédito", ": "))
            return;
        ptrCliente = pesquisaID(vecCliente, idCliente);
        if(ptrCliente == nullptr)
            cout << BOLD(RED("Cliente não encontrado. Tente novamente.")) << endl;
        else 
            if(ptrCliente->getGerenteAssociadoID() != GerenteResponsavel->getID())
                cout << BOLD(YELLOW("Esse cliente não está associado a esse gerente.")) << endl;
            else
                break;
    }
    
    if(ptrCliente->getCartao() != nullptr){
        cout << BOLD(YELLOW("O cliente já possui um cartão.")) << endl;
        return;
    }

    //cria um novo cartão
    CartaoCredito *novoCartao = new(nothrow) CartaoCredito;
    if (!novoCartao)
        return;

    //limite inicial eh igual a 60% da renda do cliente
    double limite = 0.6 * ptrCliente->getRemuneracao();
    cout << BOLD(GREEN("Limite inicial de ")) << printDinheiro(limite) << "\n";

    //senha para o cartao
    std::string senha;
    if (!lerEntrada(senha, "Digite a senha para o cartão", ":")){
        delete novoCartao;
        return;
    }


    //exige senha do gerente para confirmacao do processo 
    if (!verificaSenha(GerenteResponsavel->getSenha(), "Digite a senha do gerente responsável para finalizar")) {
        delete novoCartao;
        return;
    }

    //preenche cartao com informacoes adquiridas
    novoCartao->setLimite(limite);
    novoCartao->setSenha(senha);
    novoCartao->setNumero(novoCartao->gerarNumeroCartao(idCliente));
    novoCartao->associarCliente(ptrCliente);
    novoCartao->setDisponivel(limite);
    
    cout << endl;
    ptrCliente->setCartao(novoCartao);
    cout << BOLD(GREEN("Cartão de crédito criado com sucesso para o cliente " + ptrCliente->getNome() + "!")) << endl;
    confirmar(BOLD(GREEN("Pressione ENTER para retornar ao menu...")));
}

void Banco::alterarStatusCartao(bool bloquear) {
    // imprime cabecalho dinamico
    clearTerminal();
    if (bloquear)
        cout << BOLD(RED("===== BLOQUEAR CARTAO =====")) << endl;
    else
        cout << BOLD(GREEN("===== DESBLOQUEAR CARTAO =====\n")) << endl;

    // mostra os clientes cadastrados no banco
    showVector(vecCliente, "");

    // realiza a leitura do id
    size_t id;
    if (!lerEntrada(id, "Informe o ID do cliente", ": "))
        return;

    // busca o cliente desejado pelo id
    Cliente *ptrCliente = pesquisaID(vecCliente, id);
    if (!ptrCliente) {
        cout << BOLD(RED("Cliente não encontrado!\n"));
        confirmar();
        return;
    }

    // pega o cartao do cliente desejado
    CartaoCredito *cartao = ptrCliente->getCartao();
    if (!cartao) {
        cout << BOLD(RED("Este cliente nao possui cartão de crédito.")) << endl;
        confirmar();
        return;
    }

    // Busca o gerente associado ao cliente
    Gerente *gerente = pesquisaID(vecGerente, ptrCliente->getGerenteAssociadoID());

    // verifica a senha (padronizado com loop para ambas as acoes)
    string senha;
    while (true) {
        if (!lerEntrada(senha, "Digite a senha do Cartão (Caso for o Gerente, digite a senha do gerente)", ": "))
            return;
        
        if (senha == cartao->getSenha()){
            cout << BOLD(GREEN("Operação autorizada pelo cliente!")) << endl;
            break;
        }
                    
        if(gerente && senha == gerente->getSenha()) {
            cout << BOLD(GREEN("Operação autorizada pelo gerente associado!")) << endl;
            break;
        }
        cout << BOLD(RED("Senha incorreta!")) << endl;
    }

    // verifica o status atual e aplica a mudanca baseada no parametro
    if (bloquear) {
        if (cartao->getBloqueado()) {
            cout << BOLD(YELLOW("Cartão ja está bloqueado.")) << endl;
            confirmar();
            return;
        }
        cartao->setBloqueado(true);
        cout << BOLD(GREEN("Cartão bloqueado com sucesso!")) << endl;
    } else {
        if (!cartao->getBloqueado()) {
            cout << BOLD(YELLOW("Cartão ja esta desbloqueado.")) << endl;
            confirmar();
            return;
        }
        cartao->setBloqueado(false);
        cout << BOLD(GREEN("Cartão desbloqueado com sucesso!"));
    }
    confirmar();
}

void Banco::alterarLimite() {
    clearTerminal();
    cout << BOLD(CYAN("===== ALTERAR LIMITE DO CARTAO =====")) << endl;

    //mostra os clientes 
    showVector(vecCliente, "");
    Cliente *ptrCliente = pesquisaPessoa(vecCliente, "Informe o ID do cliente");
    if (!ptrCliente) {
        return;    
    }

    CartaoCredito *cartao = ptrCliente->getCartao();
    if (!cartao) {
        cout << BOLD(RED("Cliente não possui cartão de crédito.")) << endl;
        confirmar();
        return;
    }
    if(cartao->getBloqueado()) {
        cout << BOLD(RED("Cartão está bloqueado. Desbloqueie para alterar o limite."));
        confirmar();
        return;
    }

    if (!verificaSenha(cartao->getSenha(), "Digite a senha do cartão do cliente")) 
        return;
    
    cout << BOLD(GREEN("Limite atual: ")) << printDinheiro(cartao->getLimite()) << endl;
    double limiteAntigo = cartao->getLimite();
    double novoLimite;
    while (true) {
        if (!lerEntrada(novoLimite, "Digite o novo limite", ": R$ "))
            return;
        if (novoLimite >= 0)
            break;

        cout << BOLD(RED("Limite inválido! Tente novamente."));
    }

    cartao->setDisponivel(cartao->getDisponivel() + novoLimite - cartao->getLimite());
    cartao->setLimite(novoLimite);

    cout << BOLD(GREEN("Limite alterado com sucesso!")) << endl;
    cout << BOLD("Limite alterado de ") << printDinheiro(limiteAntigo) << BOLD(" para ") << printDinheiro(novoLimite) << endl;
    confirmar("Pressione ENTER para retornar...");
}

void Banco::pagamentoParcelado() {
    clearTerminal();
    cout << BOLD(CYAN("==== PAGAMENTO PARCELADO ====")) << endl;

    Transacao* novaTransacao = new(nothrow) Transacao;
    if (!novaTransacao)
        return;

    int quant = 0;
    double valor;
    int parcelas;
    string temp;
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
    showVector(vecCliente, BOLD(GREEN("====== Clientes Cadastrados ======")));
    Cliente *ptrRemetente = pesquisaPessoa(vecCliente, "Selecione o ID do cliente (remetente) para realizar a ação");
    if (!ptrRemetente) {
        cancelaTransacao(novaTransacao);
        return;
    }

    CartaoCredito *cartao = ptrRemetente->getCartao();
    if(cartao == nullptr){
        cout << BOLD(RED("Cliente não possui cartão.")) << endl;
        cancelaTransacao(novaTransacao);
        return;
    }
        
    if (cartao->getBloqueado()) {
        cout << BOLD(RED("Cartão bloqueado. Não pode parcelar."));
        confirmar();
        cancelaTransacao(novaTransacao);
        return;
    }
    size_t idDestinatario;
    novaTransacao->setTipo(1);
    novaTransacao->pushClienteEnvolvido(ptrRemetente);
    while(1) {
        if (!lerEntrada(quant, "Informe a quantidade de destinatários para o pagamento", ": ")) {
            cancelaTransacao(novaTransacao);
            return;
        }
        if (quant >= 1 && quant < qtdClientes)
            break;
        cout << BOLD(YELLOW("Quantidade inválida, digite novamente.")) << endl;
    }

    if (!lerEntrada(valor, "Informe o valor que será transferido para cada destinatário", ": ")) {
        cancelaTransacao(novaTransacao);
        return;
    }
    if(valor <= 0) {
        cout << BOLD(RED("Valor inválido\n"));
        cancelaTransacao(novaTransacao);
        return;
    }
    novaTransacao->setValor(valor);
    // Lê destinatário(s) e os adiciona no vetor clientesEnvolvidos.
    for(int i = 0; i < quant; i++){
        do{
            if (!lerEntrada(idDestinatario, "Informe o ID do destinatário", ": ")) {
                cancelaTransacao(novaTransacao);
                return;
            }
            if(idDestinatario < 1 || idDestinatario > vecCliente.size() || idDestinatario == ptrRemetente->getID())
                cout << BOLD(RED("ID inválido. Digite novamente.")) << endl;
            
        } while(idDestinatario < 1 || idDestinatario > vecCliente.size() || idDestinatario == ptrRemetente->getID());
        
        Cliente *ptrDestinatario = pesquisaID(vecCliente, idDestinatario);
        if(ptrDestinatario)
            novaTransacao->pushClienteEnvolvido(ptrDestinatario);
    }

    while(1){
        if (!lerEntrada(parcelas, "Quantidade de parcelas", ": ")) {
            cancelaTransacao(novaTransacao);
            return;
        }
    
        if (parcelas <= 0 || parcelas > MAXPARCELAS) {
            cout << BOLD(YELLOW("Quantidade de parcelas inválida. Deve ser de no máximo " + to_string(MAXPARCELAS) + " parcelas!")) << endl;
            confirmar();
            cancelaTransacao(novaTransacao);
            return;
        }
        else 
            break;
        
    }
    if (!verificaSenha(cartao->getSenha(), "Digite a sua senha para finalizar a transacao")) {
        cancelaTransacao(novaTransacao);
        return;
    }
    while (!novaTransacao->transferenciaCredito(novaTransacao->getClientes(), valor)) {
        if (!lerEntrada(valor, "Insira outro valor", ": R$ ")) {
            cancelaTransacao(novaTransacao);
            return;
        }
        novaTransacao->setValor(valor);
    }
    
    cartao->insereFaturas(valor, parcelas);
    cout << BOLD(GREEN("Compra aprovada!"));
    cout << BOLD("Valor total: ") << printDinheiro(valor) << endl;
    cout << BOLD("Parcelas: " + to_string(parcelas) + "x de ") << printDinheiro(valor / parcelas);
    confirmar();
    ptrRemetente->pushTransacao(novaTransacao);
    for(auto cliente : novaTransacao->getClientes()) 
        if(cliente != ptrRemetente)
            cliente->pushTransacao(novaTransacao);
    cout << BOLD(GREEN("Transferência concluída com sucesso!")) << endl;
    confirmar(BOLD(GREEN("Pressione ENTER para retornar ao menu...")));
}

void Banco::pagarFatura() {
    clearTerminal();
    cout << BOLD(CYAN("===== PAGAR FATURA DO CARTAO DE CREDITO =====")) << endl;
    showVector(vecCliente, "");

    Cliente *cliente = pesquisaPessoa(vecCliente, "Informe o ID do cliente");
    if (!cliente) 
        return;
    
    CartaoCredito *cartao = cliente->getCartao();
    if (!cartao) {
        cout << BOLD(RED("Cliente nao possui cartao."));
        confirmar();
        return;
    }

    cout << BOLD("Fatura atual: ") << printDinheiro(cartao->getFatura()) << endl;
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
    if (!verificaSenha(cartao->getSenha(), BOLD("Digite a senha do Cartão"))) 
        return;
    
    cartao->pagarFaturaAtual(pagamento);    
    confirmar();
}