#include "./menu.hpp"
#include "./menu_utils.hpp"
#include "../text/text.hpp"

#include <iostream>

using namespace AnsiTextLib;

void AnsiTextLib::menu(string title, int bgColor, vector<string> options, void (*handleOptionsFunc)(int selectedOption)){
    Text::disableInputBuffering();

    int numOfOptions = options.size();

    int max = 15;
    int selectedItem = 0;
    bool menuActive = true;

    // Add the necessary spaces
    for(int i = 0; i < options.size(); i++){
        options.at(i) = addSpaces(options.at(i), max);
    }

    while (menuActive) {
        Text::clearScreen();
        cout << title << endl;

        // Print the options
        for (int i = 0; i < numOfOptions; i++){
            printOption(selectedItem, i, bgColor, options.at(i));
        }
        
        // Handle user input
        int keyPressed = handleKeys();
        switch (keyPressed) {
            case UP:
                selectedItem = (selectedItem == 0) ? numOfOptions-1 : selectedItem - 1;
                break;
            case DOWN:
                selectedItem = (selectedItem == numOfOptions-1) ? 0 : selectedItem + 1;
                break;
            case ENTER:
                menuActive = false;
                Text::clearScreen();
                Text::enableInputBuffering();
                handleOptionsFunc(selectedItem);
                break;
        }

    }
    Text::enableInputBuffering();
}