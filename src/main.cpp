#include <iostream>
using namespace std;
#include "Banco.h"
 
#ifdef _WIN32
#include <direct.h>
#else
#include <sys/stat.h>
#include <sys/types.h>
#endif

void criarPasta() {
#ifdef _WIN32
    _mkdir("data");
#else
    mkdir("data", 0755);
#endif
}


int main() {
    criarPasta();
    // Criação do objeto Banco e execução do menu
    Banco banco;
    banco.run();
    return 0;
}

