#include <iostream>
#include <yaml-cpp/yaml.h>

#include "../include/game.h"
#include "../include/menu.h"
#include "../include/settings.h"
#include "../include/terminal_management.h"

using namespace std;

void displayMenu(const string &fallbackMessage) {

    unsigned char input;

    clearScreen();

    cout << "Menu Principal" << endl
    << "[1] Jouer" << endl
    << "[2] Réglages" << endl
    << "[3] Crédits" << endl
    << "[4] Lore" << endl
    << "[5] Quitter" << endl
    << fallbackMessage << endl
    << "Entrez votre choix : ";

    setNonCanonicalMode();

    input = getchar();
    unsigned char secondInput = 0;

    if (input >= 0xC0) {
        secondInput = getchar();
        /*
         * Point explication : pourquoi avoir fait ça ?
         * Le soucis avec le terminal, c'est qu'il fait la différence entre 2 et é (qui sont sur la même touche), sauf qu'ici, on veut un déplacement instantané dans les menus
         * Donc on veut éviter à l'utilisateur de faire shift+2 pour vraiment entrer le 2
         * On vérifie donc si il appuye sur é, sauf que la méthode pour procéder est différente :
         * On récupère d'abord le premier input en octet, et on vérifie sa taille, s'il excède 0xC0, c'est que c'est un char alphanumérique.
         * On récupère donc le deuxième octet du char, car la première partie est sa définiton en tant que caractère à accent, et sa deuxième partie est son "identifiant"
         * Donc 0xC0 0xA9 == é. Voilà, c'est pas autant complexe en fait !
         */
    }

    if (input == '1' || input == '&') {
        try {
            initGame();
        } catch (...) {
            cout << "Une erreur est survenue pendant le lancement du jeu. Vérifiez vos paramètres ou utilisez l'option --reset pour réinitialiser le jeu."
                 << " Astuce: Vous pouvez vérifier si des touches ne sont pas mises en double, ça peut arriver :)" << endl;
            input = getchar();
            displayMenu();
        }
    } else if (input == '2' || (input == 0xC3 && secondInput == 0xA9)) {
        displaySettingsMenu();
    } else if (input == '3' || input == '\"') {
        clearScreen();
        cout << "Crédits / Sources" << endl
             << "Vous pouvez cliquer sur le nom de chaque paquets utilisés pour être redirigé vers les pages" << endl << endl
             << "Fichiers de configuration : " << createHyperLink("https://github.com/jbeder/yaml-cpp", "yaml-cpp") << endl
             << "Source du projet : " << createHyperLink("https://ens.casali.me/", "Alain Casali") << endl << endl
             << "Appuyez sur une entrée pour sortir...";
        input = getchar();
        displayMenu();
    } else if (input == '4' || input == '\''){
        clearScreen();
        cout << "Bienvenue dans 'La Grille d'Alain Casali' !" << endl << endl
         << "Contexte :" << endl
         << "Dans un futur dystopique, Alain Casali, maître légendaire des gridwars, a organisé le 'Tournoi de la Singularité'." << endl
         << "Ce tournoi est l'ultime épreuve pour accéder au Kernel Cosmique, capable de réécrire les lois de la réalité..." << endl
         << "Mais surtout, de passer en root sur l'existence." << endl << endl
         << "Le tournoi :" << endl
         << "Des participants s'affrontent dans un chaos contrôlé." << endl
         << "Un seul gagnant peut émerger. Alain le rappelle à chaque tour :" << endl
         << endl <<"Un seul process peut rester dans le CPU !" << endl << endl << endl
         << "Objectif :" << endl
         << "Devenir le dernier joueur debout en éliminant tes adversaires, en manipulant la grille et en survivant aux caprices d'Alain." << endl
         << "Le vainqueur aura l'honneur d'accéder à une commande mystique pour recompiler l'univers." << endl << endl
         << "Mécaniques :" << endl
         << "1. Les Cycles Casaliens :" << endl
         << "\tChaque joueur agit à son tour, mais Alain peut passer ton tour si tu fais une faute syntaxique ou si tu l'ennuies." << endl
         << "2. Les Artefacts Glitchés :" << endl
         << "\tTrouve des artefacts pour téléporter, inverser les commandes ou invoquer Jean-Michel, l'erreur critique vivante." << endl
         << "3. Mode Duel Final :" << endl
         << "\tQuand il ne reste plus qu'un adversaire, combattez sous l'œil d'Alain, qui récitera des extraits de vieux fichiers de configuration." << endl
         << "\tAttention : une erreur et c'est le segfault assuré." << endl << endl
         << "Dernière note :" << endl
         << "Alain Casali cherche plus qu'un vainqueur. Il veut un champion digne d'entrer dans la légende des kernels !" << endl << endl
         << "Dernière dernière note : Ce lore a été VOLONTAIREMENT généré par chatGPT, pour ici faire référence au site du grand Casali. C'est un choix totalement assumé et le prompt était même de demander un lore totalement absurde."
         << endl << endl
         << "Appuyez sur une touche pour fermer..." << endl;
        input = getchar();
        displayMenu();
    } else if (input == '5' || input == 'q' || input == '(') {
        clearScreen();
        cout << "Merci aurevoir." << endl;
        exit(2);
    } else {
        displayMenu("\nChoix invalide !");
    }


} // displayMenu()

void displaySettingsMenu(const string &fallbackMessage) {

    YAML::Node settingsFile = YAML::LoadFile("settings.yml");

    unsigned char input;
    clearScreen();

    cout << "Réglages" << endl
    << "[1] Afficher les réglages" << endl
    << "[2] Modifier réglages du jeu" << endl
    << "[3] Modifier réglages des touches" << endl
    << "[4] Retour " << endl
    << fallbackMessage << endl
    << "Entrez votre choix : ";


    input = getchar();
    unsigned char secondInput = 0;

    if (input >= 0xC0) {
        secondInput = getchar();
    }

    if (input == '1' || input == '&') {
        clearScreen();

        displaySettings(settingsFile["keyBinds"], "keyBinds");

        cout << "Appuyez sur une touche pour afficher la suite... ";
        input = getchar();
        clearScreen();

        displaySettings(settingsFile["settings"], "settings");

        cout << "Appuyez sur une touche pour fermer... ";
        input = getchar();

        displaySettingsMenu();
    } else if (input == '2' || (input == 0xC3 && secondInput == 0xA9)) {
        clearScreen();
        editSettings("settings");
        displaySettingsMenu();
    } else if (input == '3' || input == '\"') {
        clearScreen();
        editSettings("keyBinds");
        displaySettingsMenu();
    } else if (input == '4' || input == 'q' || input == 'e') {
        displayMenu();
    } else {
        displaySettingsMenu("\nChoix invalide !");
    }

} // displaySettingsMenu()