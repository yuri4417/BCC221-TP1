#include "utils.h"
#include <iostream>
#include <thread>
#include <chrono>

using namespace std;
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

void delay_ms(int ms) {
    this_thread::sleep_for(chrono::milliseconds(ms));
}