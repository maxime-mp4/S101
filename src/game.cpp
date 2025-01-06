#include <iostream>
#include <bits/stdc++.h>

#include "../include/game.h"
#include "../include/settings.h"
#include "../include/gridmanagement.h"

#include <map>
using namespace std;


void moveToken (Grid & gameGrid, char & movement, User &currentPlayer, const GameKeyBinds &KEY_BINDS)
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

            cout << (j > 0 ? "\nInvalide ! " : "\n") << "-> Entrez votre couleur : ";
            cin >> user.color;
            transform(user.color.begin(), user.color.end(), user.color.begin(), ::toupper);
            ++j;
        }

        clearScreen();
        vPlayer.push_back(user);
    }
}

void eliminatePlayer(const char& playerToken ,vector<User>& users) {
    for (auto& user : users) {
        if (user.token == playerToken) {
            user.isAlive = false; // Le joueur est maintenant mort
            break; // Sortir dès qu'on a trouvé le joueur
        }
    }
}

char getWinner(vector<User>& users) {
    for (const auto& user : users) {
        if (user.isAlive) {
           return user.token;
        }
    }

    return '\0';
}


int ppal ()
{


    GameKeyBinds keyBinds{};
    GameSettings settings{};
    unsigned short players;
    vector<User> vPlayers;

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

        for (User& v : vPlayers) {
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

        for (User &v : vPlayers) {
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
