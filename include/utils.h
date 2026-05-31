#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <string>
#include <sstream>
#include "cores.h"

// Declaração de funções utilitárias para o projeto
void clearTerminal();
void limpar_buffer();
int perguntaSN(std::string str);

// Função para confirmar ação do usuário, com mensagem personalizada
void confirmar(std::string mensagem = BOLD(GREEN("Pressione ENTER para continuar...")));

// Template para ler entrada do usuário, com tratamento de erros e opção de cancelamento
// Retorna true se a leitura for bem-sucedida, false se o usuário cancelar ou ocorrer um erro
template <typename T>
bool lerEntrada(T& variavel, const std::string& prompt = "", const std::string& postPrompt = "") {
    std::string entrada;
    
    while (true) {
        if (!prompt.empty()) 
            std::cout << prompt << BOLD(YELLOW("('q' para cancelar)")) << postPrompt;

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
        } else
            std::cout << "Tipo de entrada incompativel. Tente novamente.\n";
    }
}

// Especialização para std::string, permitindo espaços e sem necessidade de conversão
template <>
inline bool lerEntrada<std::string>(std::string& variavel, const std::string& prompt, const std::string& postPrompt) {
    if (!prompt.empty())
        std::cout << prompt << BOLD(YELLOW(" ('q' para cancelar)")) << postPrompt;

    if (!std::getline(std::cin, variavel)) {
        std::cin.clear();
        std::cout << "\nErro de leitura.\n";
        return false;
    }
    if (variavel == "q\0")
        return false;
    return true;
}

std::string printDinheiro(double valor);

#endif