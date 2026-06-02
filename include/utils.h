#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <string>
#include <sstream>
#include "cores.h"

// Declaração de funções utilitárias para o projeto
void clearTerminal();
int perguntaSN(std::string str);

// Função para confirmar ação do usuário, com mensagem personalizada
void confirmar(std::string mensagem = BOLD(GREEN("Pressione ENTER para continuar...")));

std::string printDinheiro(double valor);

// Template para ler entrada do usuário, com tratamento de erros e opção de cancelamento
// Retorna true se a leitura for bem-sucedida, false se o usuário cancelar ou ocorrer um erro
template <typename T>
bool lerEntrada(T& variavel, const std::string& prompt = "", const std::string& postPrompt = "") {
    std::string entrada;
    
    while (true) {
        if (!prompt.empty()) 
            std::cout << prompt << BOLD(YELLOW(" ('q' para cancelar)")) << postPrompt;

        std::getline(std::cin, entrada);

         if (!std::cin) 
            return false;
        if (entrada.empty())
            continue;
        if (entrada == "q")
            return false;

        std::stringstream ss(entrada);
        if (ss >> variavel) {
            std::string lixo;
            if (!(ss >> lixo))
                return true;
        } 
        else
            std::cout << BOLD(RED("Tipo de entrada incompatível. Tente novamente.\n"));
    }
}

// Especialização para std::string, permitindo espaços e sem necessidade de conversão
template <>
inline bool lerEntrada<std::string>(std::string& variavel, const std::string& prompt, const std::string& postPrompt) {
    if (!prompt.empty())
        std::cout << BOLD(prompt) << BOLD(YELLOW(" ('q' para cancelar)")) << postPrompt;

    std::getline(std::cin, variavel);
    if (variavel == "q\0")
        return false;
    return true;
}


#endif