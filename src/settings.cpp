#include <string>
#include <yaml-cpp/yaml.h>
#include <iostream>
#include <fstream>

#include "../include/settings.h"
#include "../include/game.h"

using namespace std;

vector<char> loadSettings (GameKeyBinds & keyBinds, GameSettings & settings) {

    YAML::Node settingsFile = YAML::LoadFile("settings.yml");

    keyBinds.keyUp = settingsFile["keyBinds"]["keyUp"].IsDefined() ? settingsFile["keyBinds"]["keyUp"].as<char>() : keyBinds.keyUp;
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

    vector<char> vKeyBinds = {
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

    return vKeyBinds;
}


bool isValidKeyBind(const char &KEY, const std::vector<char> &V_KEY_BINDS) {

    YAML::Node settingsFile = YAML::LoadFile("settings.yml");

    for (const char& vKey : V_KEY_BINDS) {
        if (toupper(KEY) == vKey) {
            return true;
        }
    }

    return false;
}

bool isValidType(const string& KEY, const string& INPUT) {
    if (INPUT.empty()) { return true; }

    if (KEY == "gridColumns" || KEY == "gridRows") {

        try {
            const size_t VAL = stoi(INPUT);
            if (VAL) {
                return true;
            }
        } catch (...) {
            cout << "Erreur : l'entrée pour " << KEY << " doit être un entier positif." << endl;
            return false;
        }

    } else if (KEY == "wallFrequency" || KEY == "bonusFrequency") {

        try {
            const size_t VAL = stoi(INPUT);
            if (VAL > 100) {
                cout << "Erreur : l'entrée pour " << KEY << " doit être un nombre décimal." << endl;
                return false;
            }
            return true;
        } catch (...) {
            cout << "Erreur : l'entrée pour " << KEY << " doit être un nombre décimal." << endl;
            return false;
        }

    } else if (KEY == "canTeleport") {
        // Vérification si l'entrée est un booléen
        if (INPUT == "true" || INPUT == "false") {
            return true;
        } else {
            cout << "Erreur : l'entrée pour " << KEY << " doit être 'true' ou 'false'." << endl;
            return false;
        }
    } else { return true; }
    return false;  // Si la clé ne correspond à aucune des cases définies
}


void editSettings(const string &CATEGORY) {
    YAML::Node settingsFile = YAML::LoadFile("settings.yml");
    YAML::Node settingsDefaultFile = YAML::LoadFile(".default.yml");
    string input;
    char currentManipulatedKey;

    if (CATEGORY == "settings") {

        for (const auto& SETTING : settingsFile[CATEGORY]) {
            cout << "Modification de : " << SETTING.first.as<string>() << endl
            << "Valeur actuelle : " << SETTING.second  << endl
            << "Valeur par défaut : " << settingsDefaultFile[CATEGORY][SETTING.first.as<string>()] << endl
            << "Laissez vide si vous souhaitez réinitialiser le paramètre." << endl << "-> ";
            getline(cin, input);
        }

    } else if (CATEGORY == "keyBinds") {

        for (const auto& SETTING : settingsFile[CATEGORY]) {
            cout << "Modification de : " << SETTING.first.as<string>() << endl
            << "Valeur actuelle : " << SETTING.second << endl
            << "Valeur par défaut : " << settingsDefaultFile[CATEGORY][SETTING.first.as<string>()] << endl
            << "Laissez vide si vous souhaitez réinitialiser le paramètre." << endl << "-> ";
            getline(cin, input);
        }

    } else {
        cerr << "Une erreur est surevenue lors de la modification des paramètes. Si vous désirez les modifier tout de même, vous pouvez manuellement en modifiant le fichier .settings.yml." << endl;
    }
    /*
    map<char, string> usedKeys; // Map des touches utilisées avec le nom de la propriété associée

    // Initialisation des touches déjà utilisées
    for (auto setting : settingsFile[CATEGORY]) {
        string currentKey = setting.second.as<string>();
        if (currentKey.length() == 1) {
            usedKeys[toupper(currentKey[0])] = setting.first.as<string>();
        }
    }

    for (auto setting : settingsFile[CATEGORY]) {
        cout << setting.first.as<string>() << endl
             << "(actuel[écrivez]:" << setting.second
             << ",defaut[entrée vide]:" << settingsDefaultFile[CATEGORY][setting.first.as<string>()] << ") : ";

        getline(cin, input);

        if (CATEGORY == "keyBinds") {
            if (input.empty()) {
                // Utilise la valeur par défaut si aucune entrée n'est fournie
                input = settingsDefaultFile[CATEGORY][setting.first.as<string>()].as<string>();
            }

            if (input.length() != 1) {
                cout << "Erreur : la touche doit être un seul caractère." << endl;
                continue;
            }

            char newKey = toupper(input[0]);

            // Vérifie si la touche est déjà utilisée
            if (usedKeys.count(newKey)) {
                string conflictingSetting = usedKeys[newKey];
                cout << "La touche '" << newKey << "' est déjà assignée à '" << conflictingSetting << "'." << endl;
                cout << "Permutation des touches entre '" << setting.first.as<string>() << "' et '" << conflictingSetting << "'." << endl;

                // Permutation des touches
                string temp = settingsFile[CATEGORY][conflictingSetting].as<string>();
                settingsFile[CATEGORY][conflictingSetting] = setting.second.as<string>();
                setting.second = temp;
            } else {
                // Mise à jour de la touche si elle n'est pas déjà utilisée
                usedKeys[newKey] = setting.first.as<string>();
                setting.second = string(1, newKey);
            }
        } else {
            // Vérification des autres types avec isValidType
            if (isValidType(setting.first.as<string>(), input)) {
                if (!input.empty()) {
                    setting.second = input;
                } else {
                    setting.second = settingsDefaultFile[CATEGORY][setting.first.as<string>()];
                }
            } else {
                cout << "Type invalide pour " << setting.first.as<string>() << ", modification ignorée." << endl << endl;
            }
        }
    }

    cout << "Appuyez sur entrer pour valider..." << endl;
    getline(cin, input);

    ofstream fout("settings.yml");
    fout << settingsFile;
    fout.close();
    */
}

void displaySettings(const YAML::Node& CATEGORY_NODE, const string &CATEGORY_NAME) {
    cout << "[" << CATEGORY_NAME << "]" << endl;
    for (const auto& setting : CATEGORY_NODE) {
        cout << setting.first.as<string>() << ": "
                   << setting.second.as<string>() << endl;
    }

}