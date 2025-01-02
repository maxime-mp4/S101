#include <string>
#include "../include/settings.h"
#include "../include/game.h"

using namespace std;

void loadSettings(GameKeybinds &keybinds, GameSettings &settings) {
    // Move Keys
    keybinds.KeyUp = 'Z';        // Haut
    keybinds.KeyDown = 'X';      // Bas
    keybinds.KeyLeft = 'Q';      // Gauche
    keybinds.KeyRight = 'D';     // Droite
    keybinds.KeyUpLeft = 'A';    // Haut-gauche
    keybinds.KeyUpRight = 'E';   // Haut-droite
    keybinds.KeyDownLeft = 'W';  // Bas-gauche
    keybinds.KeyDownRight = 'C'; // Bas-droite

    // Tokens for players
    settings.tokenP1 = 'F';
    settings.tokenP2 = 'D';

    // Size of grid — suppose to be a rectangle
    settings.NbColumn = 10;

    // Display Colors
    settings.ColorP1 = "KRed";
    settings.ColorP2 = "KBlue";
}
