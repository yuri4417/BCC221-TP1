#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <string>
#include <sstream>

#include "cores.h"
void clearTerminal();
void limpar_buffer();
int perguntaSN(std::string str);
void confirmar(std::string mensagem = BOLD(GREEN("Pressione ENTER para continuar...")));
template <typename T>
bool lerEntrada(T& variavel, const std::string& prompt = "", const std::string& postPrompt = "") {
    std::string entrada;
    
    while (true) {
        if (!prompt.empty()) 
            std::cout << prompt << BOLD(YELLOW(" ('q' para cancelar)")) << postPrompt;

        if (!std::getline(std::cin, entrada)) {
            std::cin.clear();
            std::cout << "\nErro de leitura.\n";
            return false;
        }
        if (entrada.empty())
            continue;
        if (entrada == "q")
            return false;

        std::stringstream ss(entrada);
        if (ss >> variavel) {
            std::string lixo;
            if (ss >> lixo) {
                std::cout << "Entrada invalida. Remova caracteres estranhos (" << lixo << ") e tente novamente.\n";
                continue;
            }
            return true; 
        } else {
            std::cout << "Tipo de entrada incompativel. Tente novamente.\n";
        }
    }
}

template <>
inline bool lerEntrada<std::string>(std::string& variavel, const std::string& prompt, const std::string& postPrompt) {
    if (!prompt.empty()) {
        std::cout << prompt << BOLD(YELLOW(" ('q' para cancelar)")) << ": " << postPrompt << std::endl;;
    }
    if (!std::getline(std::cin, variavel)) {
        std::cin.clear();
        std::cout << "\nErro de leitura.\n";
        return false;
    }
    if (variavel == "q\0")
        return false;
    return true;
}

#endif