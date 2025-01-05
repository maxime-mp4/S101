#include <string>
#include <yaml-cpp/yaml.h>
#include <iostream>

#include "../include/settings.h"
#include "../include/game.h"

using namespace std;

void testVoid(){
    YAML::Node set = YAML::LoadFile("config.yml");

    for(YAML::const_iterator it=set.begin();it!=set.end();++it) {
        cout << it->first.as<std::string>() << "  " << it->second.as<std::string>() << "\n";
    }
    try{

    cout << set["keyUp"].as<std::string>() << "\n";
    }
    catch(...){
      cout << "Inexistant. Fichier défaut prendre.";
    }
}

void loadSettings (GameKeyBinds & keyBinds, GameSettings & settings) {


/*
    keyBinds.keyUp = 'Z';        // Haut
    keyBinds.keyDown = 'X';      // Bas
    keyBinds.keyLeft = 'Q';      // Gauche
    keyBinds.keyRight = 'D';     // Droite
    keyBinds.keyUpLeft = 'A';    // Haut-gauche
    keyBinds.keyUpRight = 'E';   // Haut-droite
    keyBinds.keyDownLeft = 'W';  // Bas-gauche
    keyBinds.keyDownRight = 'C'; // Bas-droite
    keyBinds.keyHelp = '/';
    keyBinds.keyInventory = 'I';

    settings.gridColumns = 10;
    settings.gridRows = 10;
    settings.wallFrequency = 30;
    settings.bonusFrequency = 10;
    settings.canTeleport = false;
    settings.currentUserTurn  = 1;*/


}
