#include <string>
#include <yaml-cpp/yaml.h>
#include <iostream>
#include "../include/settings.h"
#include "../include/game.h"

using namespace std;

vector<char> loadSettings (GameKeyBinds & keyBinds, GameSettings & settings) {

    YAML::Node settingsFile = YAML::LoadFile("settings.yml");

    keyBinds.keyUp = settingsFile["keyBinds"]["keyUp"].IsDefined() ? settingsFile["keyBinds"]["keyUp"].as<char>() : 'Z';
    keyBinds.keyDown = settingsFile["keyBinds"]["keyDown"].IsDefined() ? settingsFile["keyBinds"]["keyDown"].as<char>() : 'X';
    keyBinds.keyLeft = settingsFile["keyBinds"]["keyLeft"].IsDefined() ? settingsFile["keyBinds"]["keyLeft"].as<char>() : 'Q';
    keyBinds.keyRight = settingsFile["keyBinds"]["keyRight"].IsDefined() ? settingsFile["keyBinds"]["keyRight"].as<char>() : 'D';
    keyBinds.keyUpLeft = settingsFile["keyBinds"]["keyUpLeft"].IsDefined() ? settingsFile["keyBinds"]["keyUpLeft"].as<char>() : 'A';
    keyBinds.keyUpRight = settingsFile["keyBinds"]["keyUpRight"].IsDefined() ? settingsFile["keyBinds"]["keyUpRight"].as<char>() : 'E';
    keyBinds.keyDownLeft = settingsFile["keyBinds"]["keyDownLeft"].IsDefined() ? settingsFile["keyBinds"]["keyDownLeft"].as<char>() : 'W';
    keyBinds.keyDownRight = settingsFile["keyBinds"]["keyDownRight"].IsDefined() ? settingsFile["keyBinds"]["keyDownRight"].as<char>() : 'C';
    keyBinds.keyHelp = settingsFile["keyBinds"]["keyHelp"].IsDefined() ? settingsFile["keyBinds"]["keyHelp"].as<char>() : '/';
    keyBinds.keyInventory = settingsFile["keyBinds"]["keyInventory"].IsDefined() ? settingsFile["keyBinds"]["keyInventory"].as<char>() : 'I';

    settings.gridColumns = settingsFile["settings"]["gridColumns"].IsDefined() ? settingsFile["settings"]["gridColumns"].as<int>() : 10;
    settings.gridRows = settingsFile["settings"]["gridRows"].IsDefined() ? settingsFile["settings"]["gridRows"].as<int>() : 10;
    settings.wallFrequency = settingsFile["settings"]["wallFrequency"].IsDefined() ? settingsFile["settings"]["wallFrequency"].as<int>() : 30;
    settings.bonusFrequency = settingsFile["settings"]["bonusFrequency"].IsDefined() ? settingsFile["settings"]["bonusFrequency"].as<int>() : 10;
    settings.canTeleport = settingsFile["settings"]["canTeleport"].IsDefined() ? settingsFile["settings"]["canTeleport"].as<bool>() : false;
    settings.currentUserTurn = settingsFile["settings"]["currentUserTurn"].IsDefined() ? settingsFile["settings"]["currentUserTurn"].as<int>() : 1;

    vector<char> vKeybinds = {
        keyBinds.keyUp,
        keyBinds.keyDown,
        keyBinds.keyLeft,
        keyBinds.keyRight,
        keyBinds.keyUpLeft,
        keyBinds.keyUpRight,
        keyBinds.keyDownLeft,
        keyBinds.keyDownRight,
        keyBinds.keyHelp,
        keyBinds.keyInventory
    };

    return vKeybinds;
}

bool isValidKeyBind(const char key, vector<char> vKeyBinds) {
    YAML::Node settingsFile = YAML::LoadFile("settings.yml");

    for (char vKey : vKeyBinds) {
        if (toupper(key) == vKey) {
            return true;
        }
    }

    return false;
}
