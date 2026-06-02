#include <iostream>
#include <filesystem>
using namespace std;
#include "Banco.h"
 
int main() {
    // verificacao da pasta de dados
    if (!filesystem::exists("./data/"))
        filesystem::create_directory("./data/");
    // Criação do objeto Banco e execução do menu
    Banco banco;
    banco.run();
    return 0;
}

