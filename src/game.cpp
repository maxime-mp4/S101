#include <iostream>
#include <bits/stdc++.h>

#include "../include/game.h"
#include "../include/settings.h"
#include "../include/grid_management.h"
#include "../include/player_management.h"

#include <map>
using namespace std;


void moveToken (Grid & gameGrid, char & movement, Player &currentPlayer, const GameKeyBinds &KEY_BINDS)
{

    char car = gameGrid[currentPlayer.coordinates.first][currentPlayer.coordinates.second];
    gameGrid[currentPlayer.coordinates.first][currentPlayer.coordinates.second] = EMPTY_CHAR;

    // Calcul des nouvelles positions potentielles
    size_t new_row = currentPlayer.coordinates.first;
    size_t new_col = currentPlayer.coordinates.second;

    if (movement == KEY_BINDS.keyUpLeft) { // Haut-gauche
        new_row--;
        new_col--;
    }
    else if (movement == KEY_BINDS.keyUp) { // Haut
        new_row--;
    }
    else if (movement == KEY_BINDS.keyUpRight) { // Haut-droite
        new_row--;
        new_col++;
    }
    else if (movement == KEY_BINDS.keyLeft) { // Gauche
        new_col--;
    }
    else if (movement == KEY_BINDS.keyRight) { // Droite
        new_col++;
    }
    else if (movement == KEY_BINDS.keyDownLeft) { // Bas-gauche
        new_row++;
        new_col--;
    }
    else if (movement == KEY_BINDS.keyDown) { // Bas
        new_row++;
    }
    else if (movement == KEY_BINDS.keyDownRight) { // Bas-droite
        new_row++;
        new_col++;
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

int ppal ()
{


    GameKeyBinds keyBinds{};
    GameSettings settings{};
    unsigned short players;
    vector<Player> vPlayers;

    unsigned roundNumber (0);
    constexpr unsigned maxRoundNumber (500);
    Grid gameGrid;

    bool isGameOver (false);


    const vector<char> vKeyBinds = loadSettings(keyBinds, settings);


    clearScreen();


    cout << "Bienvenue" << endl << "Entrez le nombre de joueurs : ";
    cin >> players;

    while (players < 2 || players > 4 || cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << endl << "Nombre de joueurs invalide. Il doit y avoir entre 2 et 4 joueurs." << endl << "Entrez le nombre de joueurs : ";
        cin >> players;
    }

    createPlayers(players, vPlayers);

    InitGrid(gameGrid, settings.gridRows, settings.gridColumns, vPlayers);

    DisplayGrid (gameGrid, vPlayers);

    while (roundNumber <= maxRoundNumber && !isGameOver ){


        unsigned short int playersAlive = 0;

        for (Player& v : vPlayers) {
            if (v.isAlive) ++playersAlive;
        }


        if (playersAlive == 1) {
            cout << "Game Over!";
            isGameOver = true;
        }
        cout << playersAlive << " vivants." << endl;

        ++settings.currentUserTurn;
        settings.currentUserTurn %= vPlayers.size();
        if (!vPlayers[settings.currentUserTurn].isAlive) continue;

        ++roundNumber;

        string input;
        char inputChar;
        int j = -1;

        cout << roundNumber  << (roundNumber == 1 ? "er" : "eme") << " tour." << endl << "Joueur "
<< vPlayers[settings.currentUserTurn].token << ", entrez un déplacement : " << endl;


        while (!isValidKeyBind(input[0],vKeyBinds)) {
            DisplayGrid (gameGrid, vPlayers);
            cout << (j > 0 ? "\nInvalide ! " : "\n")
            << roundNumber  << (roundNumber == 1 ? "er" : "eme") << " tour." << endl << "Joueur "
<< vPlayers[settings.currentUserTurn].token << ", entrez un déplacement : " << endl;
            getline(cin,input);
            ++j;
        }

        inputChar = toupper (input[0]);

        moveToken (gameGrid, inputChar, vPlayers[settings.currentUserTurn], keyBinds);
        clearScreen();
        DisplayGrid (gameGrid, vPlayers);

        for (Player &v : vPlayers) {
            if (v.token == vPlayers[settings.currentUserTurn].token) continue;
            if (vPlayers[settings.currentUserTurn].coordinates.first == v.coordinates.first && vPlayers[settings.currentUserTurn].coordinates.second == v.coordinates.second) {
                eliminatePlayer(v.token, vPlayers);
            }
        }

    }//while (no victory)

    if (!isGameOver) {
        color (COLORS.find("MAGENTA")->second);
        cout << "Aucun vainqueur" << endl;
    } else {
        color (COLORS.find("GREEN")->second);
        cout << "Félicitations Joueur "
             << getWinner(vPlayers)
             << " vous avez gagné :)" << endl;
        color (COLORS.find("RESET")->second);
    }


    return 0;
} //ppal ()
