#include <string>
#include "../include/settings.h"
#include "../include/game.h"

using namespace std;

void loadSettings (GameKeybinds & keybinds, GameSettings & settings) {
    // Move Keys
    keybinds.keyUp = 'Z';        // Haut
    keybinds.keyDown = 'X';      // Bas
    keybinds.keyLeft = 'Q';      // Gauche
    keybinds.keyRight = 'D';     // Droite
    keybinds.keyUpLeft = 'A';    // Haut-gauche
    keybinds.keyUpRight = 'E';   // Haut-droite
    keybinds.keyDownLeft = 'W';  // Bas-gauche
    keybinds.keyDownRight = 'C'; // Bas-droite

    settings.wallFrequency = 30;
    settings.bonusFrequency = 10;

    // Size of grid — suppose to be a rectangle
    settings.gridRows = 10;
    settings.gridColumns = 10;

}
