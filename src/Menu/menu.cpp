#include "game_menu.h"
#include "cli_kit.h"

using namespace CliKit;


void GameMenu::ChessMenu(){
    CliKit::Menu::menu(Text::red + "Chess" + Text::normal, 1, vector<string>{"Play", "Play from FEN", "Run PGN", "Settings", "Exit"}, &MenuHandles::handleMenuOptions);
}

void GameMenu::SettingsSubMenu(){
    CliKit::Menu::menu(Text::blue + "Settings" + Text::normal, 4, vector<string>{"Interface", "Material", "Moves", "Perspective", "Input", "Window Size", "Themes", "Return"}, &MenuHandles::handleSettingsOptions);
}

void GameMenu::InterfaceTypeSettingsSubMenu(){
    CliKit::Menu::menu(Text::blue + "Choose Interface" + Text::normal, 4, vector<string>{"CLI", "GUI", "Return"}, &MenuHandles::handleInterfaceOptions);
}

void GameMenu::MaterialSettingsSubMenu(){
    CliKit::Menu::menu(Text::blue + "Show Material" + Text::normal, 4, vector<string>{"Yes", "No", "Return"}, &MenuHandles::handleMaterialOptions);
}

void GameMenu::MovesSettingsSubMenu(){
    CliKit::Menu::menu(Text::blue + "Show Moves" + Text::normal, 4, vector<string>{"Yes", "No", "Return"}, &MenuHandles::handleMovesOptions);
}

void GameMenu::PlayingAsSettingsSubMenu(){
    CliKit::Menu::menu(Text::blue + "Play As" + Text::normal, 4, vector<string>{"White", "Black", "Return"}, &MenuHandles::handlePerspectiveOptions);
}

void GameMenu::PromptTypeSettingsSubMenu(){
    CliKit::Menu::menu(Text::blue + "Prompt Type" + Text::normal, 4, vector<string>{"Seperate lines", "One line", "Return"}, &MenuHandles::handleInputOptions);
}

void GameMenu::WindowSizeSettingsSubMenu(){
    CliKit::Menu::menu(Text::blue + "Window Size" + Text::normal, 4, vector<string>{"240", "320", "400", "480", "560", "640", "720", "800", "Return"}, &MenuHandles::handleSizeOptions);
}

void GameMenu::PieceThemeSettingsSubMenu(){
    CliKit:: Menu::menu(Text::blue + "Piece Themes" + Text::normal, 4, vector<string>{"Wiki", "Staunty", "Merida", "Return"}, &MenuHandles::handleThemeOptions);
}
