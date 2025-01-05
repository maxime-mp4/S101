#include <iostream>
#include <bits/stdc++.h>

#include "../include/game.h"
#include "../include/settings.h"
#include "../include/gridmanagement.h"

#include <map>
using namespace std;


void moveToken (Grid & gameGrid, const char & MOVEMENT, User &currentPlayer, const GameKeyBinds &KEYBINDS)
{

    char car = gameGrid[currentPlayer.coordinates.first][currentPlayer.coordinates.second];
    gameGrid[currentPlayer.coordinates.first][currentPlayer.coordinates.second] = EMPTY_CHAR;

    // Calcul des nouvelles positions potentielles
    size_t new_row = currentPlayer.coordinates.first;
    size_t new_col = currentPlayer.coordinates.second;

    if (MOVEMENT == KEYBINDS.keyUpLeft) { // Haut-gauche
        new_row--;
        new_col--;
    }
    else if (MOVEMENT == KEYBINDS.keyUp) { // Haut
        new_row--;
    }
    else if (MOVEMENT == KEYBINDS.keyUpRight) { // Haut-droite
        new_row--;
        new_col++;
    }
    else if (MOVEMENT == KEYBINDS.keyLeft) { // Gauche
        new_col--;
    }
    else if (MOVEMENT == KEYBINDS.keyRight) { // Droite
        new_col++;
    }
    else if (MOVEMENT == KEYBINDS.keyDownLeft) { // Bas-gauche
        new_row++;
        new_col--;
    }
    else if (MOVEMENT == KEYBINDS.keyDown) { // Bas
        new_row++;
    }
    else if (MOVEMENT == KEYBINDS.keyDownRight) { // Bas-droite
        new_row++;
        new_col++;
    }
    else {
        // Mouvement invalide, ne rien faire
    }


    // Vérifie si les nouvelles coordonnées sont valides
    if (new_row < gameGrid.size() &&
        new_col < gameGrid[0].size())
    {
        if (gameGrid[new_row][new_col] != WALL_CHAR)
            {
            currentPlayer.coordinates.first = new_row;
            currentPlayer.coordinates.second = new_col;
        }
    }

    // Replace le caractère à la nouvelle position
    gameGrid[currentPlayer.coordinates.first][currentPlayer.coordinates.second] = car;
} // MoveToken ()

void createPlayers(const unsigned short PLAYERS, vector<User> &vPlayer) {

    clearScreen();

    string input;

    for (size_t i = 0; i < PLAYERS; ++i) {

        cout << "Joueur " << (i+1) << endl;

        User user;

        cout << "-> Entrez votre nom : ";
        cin >> user.name;


        cout << "-> Entrez votre token : ";
        cin >> input;

        for (User u : vPlayer) {

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

            cout << (j > 0 ? "\n Invalide ! " : "\n") << "-> Entrez votre couleur : ";
            cin >> user.color;
            transform(user.color.begin(), user.color.end(), user.color.begin(), ::toupper);
            ++j;
        }

        clearScreen();
        vPlayer.push_back(user);
    }



}


int ppal ()
{

    GameKeyBinds keyBinds;
    GameSettings settings;
    unsigned short players;
    vector<User> vPlayer;

    unsigned roundNumber (0);
    const unsigned maxRoundNumber (500);
    Grid GameGrid;

    bool isGameOver (false);

    loadSettings(keyBinds, settings);

    clearScreen();


    cout << "Bienvenue" << endl << "Entrez le nombre de joueurs : ";
    cin >> players;

    while (players < 2 || players > 4 || cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << endl << "Nombre de joueurs invalide. Il doit y avoir entre 2 et 4 joueurs." << endl << "Entrez le nombre de joueurs : ";
        cin >> players;
    }

    createPlayers(players, vPlayer);

    InitGrid(GameGrid, 10, 100, vPlayer);

    DisplayGrid (GameGrid, vPlayer);

    while (roundNumber <= maxRoundNumber && !isGameOver){
        cout << roundNumber  << (roundNumber == 1 ? "er" : "eme") << " tour." << endl << "Joueur "
             << vPlayer[settings.currentUserTurn].token << ", entrez un déplacement : " << endl;
        string input;
        char inputChar;

        getline(cin,input);

        inputChar = toupper (input[0]);

        moveToken (GameGrid, inputChar, vPlayer[settings.currentUserTurn], keyBinds);
        clearScreen();
        DisplayGrid (GameGrid, vPlayer);

        ++roundNumber;
        ++settings.currentUserTurn;
        settings.currentUserTurn %= vPlayer.size();

        for (const User &u : vPlayer) {
            if (u.token == vPlayer[settings.currentUserTurn].token) continue;
            if (vPlayer[settings.currentUserTurn].coordinates.first == u.coordinates.first && vPlayer[settings.currentUserTurn].coordinates.second == u.coordinates.second) {
                isGameOver = true;
            }
        }

    }//while (no victory)

    if (!isGameOver) {
        color (COLORS.find("MAGENTA")->second);
        cout << "Aucun vainqueur" << endl;
    } else {
        color (COLORS.find("GREEN")->second);
        cout << "Félicitations Joueur "
             << (vPlayer[settings.currentUserTurn].token)
             << " vous avez gagné :)" << endl;
        color (COLORS.find("RESET")->second);
    }


    return 0;
} //ppal ()
