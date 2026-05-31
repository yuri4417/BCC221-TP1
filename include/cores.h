#ifndef __CORES_H__
#define __CORES_H__

#include <string> // Necessário para o uso de std::string

// cores e formato de texto (mantidos como macros/literais pois são constantes)
#define ANSI_RESET            "\x1b[0m"  // desativa os efeitos anteriores
#define ANSI_BOLD             "\x1b[1m"  // coloca o texto em negrito
#define ANSI_COLOR_BLACK      "\x1b[30m"
#define ANSI_COLOR_RED        "\x1b[31m"
#define ANSI_COLOR_GREEN      "\x1b[32m"
#define ANSI_COLOR_YELLOW     "\x1b[33m" 
#define ANSI_COLOR_BLUE       "\x1b[34m"
#define ANSI_COLOR_MAGENTA    "\x1b[35m"
#define ANSI_COLOR_CYAN       "\x1b[36m"
#define ANSI_COLOR_WHITE      "\x1b[37m"
#define ANSI_BG_COLOR_BLACK   "\x1b[40m"
#define ANSI_BG_COLOR_RED     "\x1b[41m"
#define ANSI_BG_COLOR_GREEN   "\x1b[42m"
#define ANSI_BG_COLOR_YELLOW  "\x1b[43m"
#define ANSI_BG_COLOR_BLUE    "\x1b[44m"
#define ANSI_BG_COLOR_MAGENTA "\x1b[45m"
#define ANSI_BG_COLOR_CYAN    "\x1b[46m"
#define ANSI_BG_COLOR_WHITE   "\x1b[47m"

// funções inline para facilitar o uso e permitir concatenação dinâmica
inline std::string BOLD(const std::string& str)       { return std::string(ANSI_BOLD) + str + ANSI_RESET; }
inline std::string BLACK(const std::string& str)      { return std::string(ANSI_COLOR_BLACK) + str + ANSI_RESET; }
inline std::string BLUE(const std::string& str)       { return std::string(ANSI_COLOR_BLUE) + str + ANSI_RESET; }
inline std::string RED(const std::string& str)        { return std::string(ANSI_COLOR_RED) + str + ANSI_RESET; }
inline std::string GREEN(const std::string& str)      { return std::string(ANSI_COLOR_GREEN) + str + ANSI_RESET; }
inline std::string YELLOW(const std::string& str)     { return std::string(ANSI_COLOR_YELLOW) + str + ANSI_RESET; }
inline std::string MAGENTA(const std::string& str)    { return std::string(ANSI_COLOR_MAGENTA) + str + ANSI_RESET; }
inline std::string CYAN(const std::string& str)       { return std::string(ANSI_COLOR_CYAN) + str + ANSI_RESET; }
inline std::string WHITE(const std::string& str)      { return std::string(ANSI_COLOR_WHITE) + str + ANSI_RESET; }

inline std::string BG_BLACK(const std::string& str)   { return std::string(ANSI_BG_COLOR_BLACK) + str + ANSI_RESET; }
inline std::string BG_BLUE(const std::string& str)    { return std::string(ANSI_BG_COLOR_BLUE) + str + ANSI_RESET; }
inline std::string BG_RED(const std::string& str)     { return std::string(ANSI_BG_COLOR_RED) + str + ANSI_RESET; }
inline std::string BG_GREEN(const std::string& str)   { return std::string(ANSI_BG_COLOR_GREEN) + str + ANSI_RESET; }
inline std::string BG_YELLOW(const std::string& str)  { return std::string(ANSI_BG_COLOR_YELLOW) + str + ANSI_RESET; }
inline std::string BG_MAGENTA(const std::string& str) { return std::string(ANSI_BG_COLOR_MAGENTA) + str + ANSI_RESET; }
inline std::string BG_CYAN(const std::string& str)    { return std::string(ANSI_BG_COLOR_CYAN) + str + ANSI_RESET; }
inline std::string BG_WHITE(const std::string& str)   { return std::string(ANSI_BG_COLOR_WHITE) + str + ANSI_RESET; }

// caracteres uteis para tabelas
#define TAB_HOR "\u2501" // ━ (horizontal)
#define TAB_VER "\u2503" // ┃ (vertical)
#define TAB_TL  "\u250F" // ┏ (top-left)
#define TAB_ML  "\u2523" // ┣ (middle-left)
#define TAB_BL  "\u2517" // ┗ (bottom-left)
#define TAB_TJ  "\u2533" // ┳ (top-join)
#define TAB_MJ  "\u254B" // ╋ (middle-join)
#define TAB_BJ  "\u253B" // ┻ (bottom-join)
#define TAB_TR  "\u2513" // ┓ (top-right)
#define TAB_MR  "\u252B" // ┫ (middle-right)
#define TAB_BR  "\u251B" // ┛ (bottom-right)

/* // * Funcao que imprime um exemplo de uso das cores e tabelas 
// */
//void example() {
//    // ATENÇÃO: Como as cores agora retornam std::string, se for usar 'printf'
//    // você deve extrair o C-string com .c_str() ou usar std::cout.
//    // Exemplo com std::cout:
//    // std::cout << BOLD(RED("vermelho negrito!")) << std::endl;
//    //
//    // Exemplo com printf:
//    // printf("%s\n", BOLD(RED("vermelho negrito!")).c_str());
//}
//
#endif