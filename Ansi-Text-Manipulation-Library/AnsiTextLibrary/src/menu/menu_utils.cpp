
#ifdef _WIN32
    #include <conio.h>  
    #include <windows.h>
#else
    #include <termios.h>
    #include <unistd.h>
#endif

#include <iostream>

#include "./menu.hpp"
#include "./menu_utils.hpp"
#include "../text/text.hpp"

using namespace std;
using namespace AnsiTextLib;


void Text::enableInputBuffering(){
    #ifdef _WIN32
        // Enable console input buffering
        DWORD mode;
        HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
        SetConsoleMode(hInput, mode);
    #else
        termios term;
        tcgetattr(STDIN_FILENO, &term);
        term.c_lflag |= (ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &term);

    #endif
    cout << "\e[?25h"; // Show the cursor
}

void Text::disableInputBuffering(){
    #ifdef _WIN32
        // Disable console input buffering
        DWORD mode;
        HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
        GetConsoleMode(hInput, &mode);
        SetConsoleMode(hInput, mode & ~ENABLE_ECHO_INPUT & ~ENABLE_LINE_INPUT);
    #else
        termios term;
        tcgetattr(STDIN_FILENO, &term);
        term.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &term);

    #endif
    cout << "\e[?25l"; // Hide the cursor
}

int handleKeys() {
    #ifdef _WIN32
        switch (_getch()) {
            case 13:
                return ENTER;
            case 72:
                return UP;
            case 80:
                return DOWN;
            default:
                return -1;
        }
    #else
        switch (getchar()){
            case '\n': return ENTER;
            case 65: return UP;
            case 66: return DOWN;
            default: return -1;
        }
    #endif
}

string addSpaces(string word, int length) {
    if (length < word.size()) return "WRONG";

    while (word.size() < length) {
        word += " ";
    }
    return word;
}

void printOption(int selectedItem, int index, int color, string option) {
    std::cout << (selectedItem == index ? Text::color("bg", color) +
                                              option + Text::normal
                                        : option)
              << std::endl;
}