#include <iostream>
#include <algorithm>

#include "../include/player_management.h"
#include "../include/grid_management.h"
#include "../include/terminal_management.h"

using namespace std;


void createPlayers(const unsigned short& PLAYERS, vector<Player> &vPlayer) {
    clearScreen();
    cout << "Players: " << PLAYERS << endl;

    string input;

    for (size_t i = 0; i < PLAYERS; ++i) {
        cout << "Joueur " << (i + 1) << endl;
        Player user;

        cout << "-> Entrez votre nom : ";
        getline(cin, user.name);

        bool tokenUsed;
        do {
            cout << "-> Entrez votre token : ";
            getline(cin, input);

            tokenUsed = false;
            for (const Player& u : vPlayer) {
                if (toupper(input[0]) == u.token) {
                    tokenUsed = true;
                    break;
                }
            }

            if (tokenUsed) {
                cout << "Token déjà utilisé !" << endl;
            }
        } while (tokenUsed);

        user.token = toupper(input[0]);

        size_t j = 0;
        while (COLORS.find(user.color) == COLORS.end() || user.color == "RESET") {
            for (const auto& c : COLORS) {
                if (c.first == "RESET") continue;
                cout << c.first << "\t";
            }

            cout << (j > 0 ? "\nInvalide ! " : "\n") << "-> Entrez votre couleur : ";
            getline(cin, user.color);
            transform(user.color.begin(), user.color.end(), user.color.begin(), ::toupper);
            ++j;
        }

        clearScreen();
        vPlayer[i] = user;
    }
} // createPlayers()


void eliminatePlayer(const char& playerToken ,vector<Player>& users) {
    for (auto& user : users) {
        if (user.token == playerToken) {
            user.isAlive = false; // Le joueur est maintenant mort
            break; // Sortir dès qu'on a trouvé le joueur
        }
    }
} // eliminatePlayer()

Player getWinner(vector<Player>& users) {
    for (const auto& user : users) {
        if (user.isAlive) {
            return user;
        }
    }

    return Player();
} // getWinner()

