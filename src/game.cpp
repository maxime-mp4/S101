#include <iostream>
#include <bits/stdc++.h>

#include "../include/game.h"
#include "../include/settings.h"
#include "../include/player_management.h"
#include "../include/terminal_management.h"
#include "../include/grid_management.h"

#include <map>
using namespace std;


void moveToken (Grid & gameGrid, char & movement, Player &currentPlayer, const GameKeyBinds &KEY_BINDS, const GameSettings &SETTINGS, const
                unsigned &ROUND_NUMBER)
{
    char car = gameGrid[currentPlayer.coordinates.first][currentPlayer.coordinates.second];
    gameGrid[currentPlayer.coordinates.first][currentPlayer.coordinates.second] = EMPTY_CHAR;

    size_t newRow = currentPlayer.coordinates.first;
    size_t newCol = currentPlayer.coordinates.second;

    if (movement == KEY_BINDS.keyUpLeft) {
        newRow--;
        newCol--;
    }
    else if (movement == KEY_BINDS.keyUp) {
        newRow--;
    }
    else if (movement == KEY_BINDS.keyUpRight) {
        newRow--;
        newCol++;
    }
    else if (movement == KEY_BINDS.keyLeft) {
        newCol--;
    }
    else if (movement == KEY_BINDS.keyRight) {
        newCol++;
    }
    else if (movement == KEY_BINDS.keyDownLeft) {
        newRow++;
        newCol--;
    }
    else if (movement == KEY_BINDS.keyDown) {
        newRow++;
    }
    else if (movement == KEY_BINDS.keyDownRight) {
        newRow++;
        newCol++;
    }

    if (SETTINGS.canTeleport && ROUND_NUMBER >= 5) {
        newRow = (newRow + gameGrid.size()) % gameGrid.size();
        newCol = (newCol + gameGrid[0].size()) % gameGrid[0].size();
        /*
         * Point explication : pourquoi avoir fait ça ?
         * On utilise ici en premier lieux l'addition pour avoir constamment un résultat valide, (dans le cas ou on se déplace vers un index négatif)
         * Ensuite, on ramène au modulo si la taille de la grille est dépassée par newRow/newCol. (soit, 0)
         * C'était un peu dur à faire mais Internet est là pour nous sauver !
         */
    }

    if (newRow < gameGrid.size() &&
        newCol < gameGrid[0].size())
    {
        if (gameGrid[newRow][newCol] != WALL_CHAR)
        {
            currentPlayer.coordinates.first = newRow;
            currentPlayer.coordinates.second = newCol;
        }
    }

    gameGrid[currentPlayer.coordinates.first][currentPlayer.coordinates.second] = car;
} // moveToken ()

int initGame ()
{
    GameKeyBinds keyBinds{};
    GameSettings settings{};
    string playersSize;
    size_t i = 0;
    vector<Player> vPlayers;
    unsigned roundNumber (1);
    unsigned short playerCount = 0;
    constexpr unsigned maxRoundNumber (500);
    Grid gameGrid;
    bool isGameOver (false);
    const vector<char> vKeyBinds = loadSettings(keyBinds, settings);



    while (playerCount == 0 || playerCount < 2 || playerCount > 4) {
        clearScreen();
        cout << (i > 0 ? "Nombre de joueurs invalide. Il doit y avoir entre 2 et 4 joueurs.\n" : "") << "Entrez le nombre de joueurs : ";
        getline(cin, playersSize);
        try {
            playerCount = stoi(playersSize);
        } catch (...) {
            cout << "Erreur : il faut entrer un nombre valide." << endl;
        }
        ++i;
    }

    vPlayers.resize(playerCount);
    createPlayers(playerCount, vPlayers);

    initGrid(gameGrid, settings.gridRows, settings.gridColumns, vPlayers, settings);

    displayGrid (gameGrid, vPlayers);

    while (roundNumber <= maxRoundNumber && !isGameOver ){
        unsigned short int playersAlive = 0;

        for (const Player& v : vPlayers) {
            if (v.isAlive) ++playersAlive;
        }

        if (playersAlive == 1) {
            isGameOver = true;
            continue;
        }

        ++settings.currentUserTurn;
        settings.currentUserTurn %= vPlayers.size();
        if (!vPlayers[settings.currentUserTurn].isAlive) continue;
        string input;
        char inputChar;



        int j = 0;
        while (!isValidKeyBind(input[0],vKeyBinds)) {
            clearScreen();
            displayGrid (gameGrid, vPlayers);
            cout
            << (j > 0 ? "\nInvalide ! " : "\n")
            << roundNumber  << (roundNumber == 1 ? "er" : "eme")
            << " tour." << (roundNumber >= 5 && settings.canTeleport ? " (TELEPORTATION ACTIVEE)" : (settings.canTeleport ? " (TELEPORATION DESACTIVEE)" : ""))
            << endl
            << "Joueur "
            << vPlayers[settings.currentUserTurn].token << ", entrez un déplacement : "
            << endl;

            getline(cin,input);

            if (input.empty()) {
                continue;
            }
            ++j;
        }

        inputChar = toupper (input[0]);

        if (toupper(input[0]) == keyBinds.keyHelp) {
            cout << "Touches disponibles. Pour plus d'informations, referez vous a la section [Aide] du menu ou lancez ce programme avec l'option --keybinds." << endl;
            for (const char &c : vKeyBinds) {
                cout << c << "\t";
            }
            cout << endl;
            getline(cin,input);
            continue;
        }
        if (toupper(input[0]) == keyBinds.keyInventory) {
            if (vPlayers.empty()) {
                cout << "Inventaire vide !" << endl;
                getline(cin,input);
                continue;
            }
            for (const vector<string> &v: vPlayers[settings.currentUserTurn].inventory ) {
                for (const string &k: v) {
                    cout << k << "\t";
                }
            }
        }



        moveToken (gameGrid, inputChar, vPlayers[settings.currentUserTurn], keyBinds, settings, roundNumber);
        displayGrid (gameGrid, vPlayers);
        ++roundNumber;

        for (Player &v : vPlayers) {
            if (v.token == vPlayers[settings.currentUserTurn].token) continue;
            if (vPlayers[settings.currentUserTurn].coordinates.first == v.coordinates.first && vPlayers[settings.currentUserTurn].coordinates.second == v.coordinates.second) {
                eliminatePlayer(v.token, vPlayers);
            }
        }

    }

    clearScreen();
    if (!isGameOver) {
        setColor (COLORS.find("MAGENTA")->second);
        cout << "Aucun vainqueur" << endl;
    } else {
        setColor (COLORS.find("GREEN")->second);
        cout << "Félicitations "
        << getWinner(vPlayers).name
        << " (" << getWinner(vPlayers).token << ")"
             << " vous avez gagné :)" << endl;
        setColor (COLORS.find("RESET")->second);
    }


    return 0;
} // initGame()
