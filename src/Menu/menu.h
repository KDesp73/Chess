#pragma once

namespace Menu{
    void ChessMenu();
    void SettingsSubMenu();
    void MaterialSettingsSubMenu();
    void MovesSettingsSubMenu();
    void PlayingAsSettingsSubMenu();
    void PromptTypeSettingsSubMenu();
    void InterfaceTypeSettingsSubMenu();
};

namespace MenuHandles{
    void handleMenuOptions(int option);
    void handleSettingsOptions(int option);
    void handleMaterialOptions(int option);
    void handleMovesOptions(int option);
    void handlePerspectiveOptions(int option);
    void handleInputOptions(int option);
    void handleInterfaceOptions(int option);
};