#include <iostream>
#include <yaml-cpp/yaml.h>

#include "../include/game.h"
#include "../include/menu.h"
#include "../include/settings.h"
#include "../include/terminal_management.h"

using namespace std;

void displayMenu(const string &fallbackMessage) {

    string input;

    clearScreen();

    cout << "Menu Principal" << endl
    << "[1] Jouer" << endl
    << "[2] Réglages" << endl
    << "[3] Crédits" << endl
    << "[4] Quitter" << endl
    << fallbackMessage << endl
    << "Entrez votre choix : ";

    getline(cin, input);

    switch (tolower(input[0])) {

        case '1':
        case '&':

            try {
                initGame();
            } catch (...) {
                cout << "Une erreur est survenue pendant le lancement du jeu. Vérifiez vos paramètres ou utilisez l'option --reset pour réinitialiser le jeu." << "Astuce: Vous pouvez vérifier si des touches ne sont pas mises en double, ça peut arriver :)" << endl;
                getline(cin, input);
                displayMenu();
            }

        break;

        case '2':
            displaySettingsMenu();
        break;

        case '3':
            case '\"':
        clearScreen();
            cout << "Crédits / Sources" << endl
                << "Vous pouvez cliquer sur le nom de chaque paquets utilisés pour être redirigé vers les pages" << endl << endl
                << "Fichiers de configuration : " << createHyperLink("https://github.com/jbeder/yaml-cpp", "yaml-cpp") << endl
                << "Source du projet : " << createHyperLink("https://ens.casali.me/", "Alain Casali") << endl << endl
                << "Appuyez sur une entrée pour sortir...";
        getline(cin, input);
        displayMenu();

        break;

        case '4':
        case 'q':
        case '\'':
            clearScreen();
            cout << "Merci aurevoir." << endl;
            exit(2);

        default:
            displayMenu("\nChoix invalide !");
    }
} // displayMenu()

void displaySettingsMenu(const string &fallbackMessage) {

    YAML::Node settingsFile = YAML::LoadFile("settings.yml");

    clearScreen();

    cout << "Réglages" << endl
    << "[1] Afficher les réglages" << endl
    << "[2] Modifier réglages du jeu" << endl
    << "[3] Modifier réglages des touches" << endl
    << "[4] Retour " << endl
    << fallbackMessage << endl
    << "Entrez votre choix : ";


    string input;
    getline(cin, input);

    switch (tolower(input[0])) {

        case '1':

            clearScreen();

            displaySettings(settingsFile["keyBinds"], "keyBinds");

            cout << "Appuyez sur une entrer pour afficher la suite... ";
            getline(cin, input);
            clearScreen();

            displaySettings(settingsFile["settings"], "settings");

            cout << "Appuyez sur une entrer pour fermer... ";
            getline(cin, input);

            displaySettingsMenu();

        break;
        case '2':
            clearScreen();
            editSettings("settings");
            displaySettingsMenu();

        break;

        case '3':
            clearScreen();
            editSettings("keyBinds");
            displaySettingsMenu();

        break;

        case '4':
        case 'q':
        case 'e':
            displayMenu();
        break;

        default:
            displaySettingsMenu("\nChoix invalide !");
    }
} // displaySettingsMenu()