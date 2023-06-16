#include <iostream>

#include "ansi_lib.hpp"


void handleOptions(int option){
    switch (option){
    case 0:
        cout << "Option 1 selected" << endl;
        break;
    case 1:
        cout << "Option 2 selected" << endl;
        break;
    case 3:
        cout << "Option 3 selected" << endl;
        break;
    default:
        break;
    }
}

int main(){
    AnsiTextLib::menu(4, vector<string>{"Option 1", "Option 2", "Option 3"}, &handleOptions);

    cout << AnsiTextLib::Text::b_blue + "Text" + AnsiTextLib::Text::normal << endl;


    return 0;
}