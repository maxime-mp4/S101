//
// Created by maxime on 1/6/25.
//

#include "../include/player_management.h"
#include "../include/grid_management.h"

#include <iostream>
#include <algorithm>

void createPlayers(const unsigned short PLAYERS, vector<Player> &vPlayer) {

    clearScreen();

    string input;

    for (size_t i = 0; i < PLAYERS; ++i) {

        cout << "Joueur " << (i+1) << endl;
        Player user;

        cout << "-> Entrez votre nom : ";
        cin >> user.name;


        cout << "-> Entrez votre token : ";
        cin >> input;

        for (Player u : vPlayer) {

            while (toupper(input[0]) == u.token) {
                cout << "Token déjà utilisé !" << endl << "-> Entrez votre token : ";
                cin >> input;
            }
        }

        user.token = toupper(input[0]);
        size_t j = 0;
        while (COLORS.find(user.color) == COLORS.end() || user.color == "RESET") {
            for (const auto&c : COLORS) {
                if (c.first == "RESET") continue;
                cout << c.first << "\t";
            }

            cout << (j > 0 ? "\nInvalide ! " : "\n") << "-> Entrez votre couleur : ";
            cin >> user.color;
            transform(user.color.begin(), user.color.end(), user.color.begin(), ::toupper);
            ++j;
        }

        clearScreen();
        vPlayer.push_back(user);
    }
}

void eliminatePlayer(const char& playerToken ,vector<Player>& users) {
    for (auto& user : users) {
        if (user.token == playerToken) {
            user.isAlive = false; // Le joueur est maintenant mort
            break; // Sortir dès qu'on a trouvé le joueur
        }
    }
}

char getWinner(vector<Player>& users) {
    for (const auto& user : users) {
        if (user.isAlive) {
            return user.token;
        }
    }

    return '\0';
}

