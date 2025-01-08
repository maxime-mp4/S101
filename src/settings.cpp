#include "../include/terminal_management.h"
#include "../include/settings.h"
#include "../include/game.h"

#include <string>
#include <yaml-cpp/yaml.h>
#include <iostream>
#include <fstream>


using namespace std;
using namespace YAML;

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
            if (VAL >= 5) {
                return true;
            }
        } catch (...) {
            return false;
        }

    } else if (KEY == "wallFrequency" || KEY == "bonusFrequency") {

        try {
            const size_t VAL = stoi(INPUT);
            if (VAL >= 70) {
                return false;
            }
            return true;
        } catch (...) {
            return false;
        }

    } else if (KEY == "canTeleport") {
        // Vérification si l'entrée est un booléen
        if (INPUT == "true" || INPUT == "false") {
            return true;
        } else {
            return false;
        }
    } else { return true; }
    return false;  // Si la clé ne correspond à aucune des cases définies
}


void editSettings(const string &CATEGORY) {
    YAML::Node settingsFile = YAML::LoadFile("settings.yml");
    YAML::Node settingsDefaultFile = YAML::LoadFile(".default.yml");

    string input;
    string settingsType;
    clearScreen();
    if (CATEGORY == "settings") {

        cout << "Modifier un paramètre : entrez le paramètre que vous souhaitez changer."
        << endl
        << "Pour le trouver, rendez-vous dans [Réglages] > [Afficher les réglages]. (Paramètre sensible à la casse)" << endl << "-> ";
        getline(cin,input);

             if (!input.empty() && settingsFile[CATEGORY][input]) {

                 clearScreen();
                 cout << "Entrez le paramètre pour " << input << endl;
                 if (input == "gridColumns" || input == "gridRows" || input == "wallFrequency" || input == "bonusFrequency") {
                     cout << "Attention: entrée sensible à la casse." << endl << "Type attendu: Nombre positif" << (input == "gridColumns" || input == "gridRows"  ? " supérieur ou égal a 5" : " inférieur ou égal à 70") << endl << (input == "wallFrequency" ? "Attention: plus le nombre s'approche de 100, plus il y a de chance que le jeu devienne impossible !\nNous vous recommandons de mettre une valeur entre 20 et 40\n" : "") << "-> ";
                 } else {
                     cout << "Attention: entrée sensible à la casse." << endl << "Type attendu: booleen (true/false)" << endl << "-> ";
                 }
                 getline(cin,settingsType);
                 if (!isValidType(input, settingsType)) {
                     cout << "Paramètre invalide. Modification annulée." << endl << "Appuyez sur entrer pour fermer...";
                     getline(cin,input);
                 } else {
                     settingsFile[CATEGORY][input] = settingsType;
                 }
             } else {
                 cout << (input.empty() ? "Annulation." : "Paramètre inexistant. Réessayez.") << endl
                 << "Appuyez sur entrer pour fermer... ";
                 getline(cin,input);
             }

    } else if (CATEGORY == "keyBinds") {
        GameSettings globalSettings = GameSettings();
        GameKeyBinds globalKeyBinds = GameKeyBinds();
        vector<char> vKeyBinds = loadSettings(globalKeyBinds, globalSettings);


        cout << "Modifier un paramètre : entrez le paramètre que vous souhaitez changer."
        << endl
        << "Pour le trouver, rendez-vous dans [Réglages] > [Afficher les réglages]. (Paramètre sensible à la casse)" << endl << "-> ";
        getline(cin,input);

        if (!input.empty() && settingsFile[CATEGORY][input]) {
            bool isKeyUsed = false;
            cout << "Entrez le paramètre pour " << input << endl
            << "Attention: entrée sensible à la casse." << endl << "Type attendu: caractère (la première entrée sera considérée comme)" << endl << "-> ";

            getline(cin,settingsType);

            clearScreen();
            for (const char& vKey : vKeyBinds) {
                if (vKey == toupper(settingsType[0])) {
                    cout << "La touche " << vKey << " est déjà utilisée (voir paramètres). Paramètre inchangé." << endl
                    << "Appuyez sur entrer pour fermer... ";
                    isKeyUsed = true;
                    getline(cin,input);
                    break;
                }
            }

            char outputKey = toupper(settingsType[0]);

            if (!isKeyUsed) {
                settingsFile[CATEGORY][input] = outputKey;
            }

        } else {
            cout << (input.empty() ? "Annulation." : "Paramètre inexistant. Réessayez.") << endl
            << "Appuyez sur entrer pour fermer... ";
            getline(cin,input);
        }


    } else {
        cerr << "Une erreur est surevenue lors de la modification des paramètes. Si vous désirez les modifier tout de même, vous pouvez manuellement en modifiant le fichier .settings.yml." << endl;
    }

    ofstream fOut("settings.yml");
    fOut << settingsFile;
    fOut.close();
}

void displaySettings(const YAML::Node& CATEGORY_NODE, const string &CATEGORY_NAME) {
    cout << "[" << CATEGORY_NAME << "]" << endl;
    for (const auto& setting : CATEGORY_NODE) {
        cout << setting.first.as<string>() << ": "
                   << setting.second.as<string>() << endl;
    }

}