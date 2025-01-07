//
// Created by maxime on 1/6/25.
//

#include "../include/player_management.h"
#include "../include/grid_management.h"
#include "../include/terminal_management.h"

#include <bits/stdc++.h>
#include <iostream>
#include <algorithm>

void createPlayers(const unsigned short PLAYERS, vector<Player> &vPlayer) {
  clearScreen();
	cout << "Players: " << PLAYERS << endl;

    string input;

    // Boucle pour chaque joueur
    for (size_t i = 0; i < PLAYERS; ++i) {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Joueur " << (i+1) << endl;
        Player user;

        // Demander le nom du joueur
        cout << "-> Entrez votre nom : ";

        getline(cin, user.name);  // Utilisation de getline pour permettre des noms avec des espaces

        // Demander le token du joueur
        cout << "-> Entrez votre token : ";
        cin >> input;  // Utilisation de getline pour récupérer le token

        // Vérification si le token est déjà utilisé
if (i > 0) {
    // Recherche d'un token déjà utilisé dans vPlayer
    while (std::find_if(vPlayer.begin(), vPlayer.end(), [&input](const Player& u) {
        return toupper(input[0]) == u.token;
    }) != vPlayer.end()) {
        cout << "Token déjà utilisé !" << endl << "-> Entrez votre token : ";
        cin >> input;
    }
}


        user.token = toupper(input[0]);  // On prend uniquement la première lettre du token, en majuscule

        size_t j = 0;
        // Vérification de la couleur
        while (COLORS.find(user.color) == COLORS.end() || user.color == "RESET") {

            // Affichage des couleurs disponibles
            for (const auto& c : COLORS) {
                if (c.first == "RESET") continue;  // Exclure "RESET"
                cout << c.first << "\t";  // Afficher le nom des couleurs
            }

            // Si c'est la deuxième tentative ou plus, afficher "Invalide !"
            cout << (j > 0 ? "\nInvalide ! " : "\n") << "-> Entrez votre couleur : ";

            // Demander la couleur
            cin >> user.color;
            transform(user.color.begin(), user.color.end(), user.color.begin(), ::toupper);  // Convertir en majuscules
            ++j;  // Incrémenter le compteur de tentatives
        }
	clearScreen();
  // Nettoyer l'écran après chaque création de joueur
        vPlayer[i] = user;  // Ajouter le joueur créé à la liste
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

Player getWinner(vector<Player>& users) {
    for (const auto& user : users) {
        if (user.isAlive) {
            return user;
        }
    }

    return Player();
}

