#include "utils.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <sstream>
#include <iomanip>
using namespace std;

// Limpa o terminal usando códigos de escape ANSI
void clearTerminal() {
    cout << "\033[H\033[2J"; 
}
// Pergunta ao usuário uma resposta sim ou não, retornando 1 para sim e 0 para não
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
        cout << BOLD(RED("Opção Inválida! Tente novamente (Responda com S/N)"));
    }
}

// Exibe uma mensagem e espera o usuário pressionar Enter para continuar
void confirmar(string mensagem) {
    cout << mensagem;
    string lixo;
    getline(cin, lixo);
}

string printDinheiro(double valor) {
    ostringstream oss;
    oss << fixed << setprecision(2) << valor;
    return BOLD(GREEN("R$ " + oss.str()));
}