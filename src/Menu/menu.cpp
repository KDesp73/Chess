#include "menu.h"
#include "../../Ansi-Text-Manipulation-Library/AnsiTextLibrary/src/ansi_lib.hpp"

using namespace AnsiTextLib;


void Menu::ChessMenu(){
	menu(Text::red + "Chess" + Text::normal, 1, vector<string>{"Play", "Play from FEN", "Settings", "Exit"}, &MenuHandles::handleMenuOptions);
}

void Menu::SettingsSubMenu(){
    menu(Text::blue + "Settings" + Text::normal, 4, vector<string>{"Interface", "Material", "Moves", "Perspective", "Input", "Return"}, &MenuHandles::handleSettingsOptions);
}

void Menu::InterfaceTypeSettingsSubMenu(){
    menu(Text::blue + "Choose Interface" + Text::normal, 4, vector<string>{"CLI", "GUI", "Return"}, &MenuHandles::handleInterfaceOptions);
}

void Menu::MaterialSettingsSubMenu(){
    menu(Text::blue + "Show Material" + Text::normal, 4, vector<string>{"Yes", "No", "Return"}, &MenuHandles::handleMaterialOptions);
}

void Menu::MovesSettingsSubMenu(){
    menu(Text::blue + "Show Moves" + Text::normal, 4, vector<string>{"Yes", "No", "Return"}, &MenuHandles::handleMovesOptions);
}

void Menu::PlayingAsSettingsSubMenu(){
    menu(Text::blue + "Play As" + Text::normal, 4, vector<string>{"White", "Black", "Return"}, &MenuHandles::handlePerspectiveOptions);
}

void Menu::PromptTypeSettingsSubMenu(){
    menu(Text::blue + "Prompt Type" + Text::normal, 4, vector<string>{"Seperate lines", "One line", "Return"}, &MenuHandles::handleInputOptions);
}
