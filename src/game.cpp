#include <iostream>
#include <bits/stdc++.h>

#include "../include/game.h"
#include "../include/settings.h"
#include "../include/gridmanagement.h"

#include <map>
using namespace std;


void moveToken (Grid & gameGrid, const char & MOVEMENT, User &currentPlayer, const GameKeybinds &KEYBINDS)
{

    char car = gameGrid[currentPlayer.coordinates.first][currentPlayer.coordinates.second];
    gameGrid[currentPlayer.coordinates.first][currentPlayer.coordinates.second] = EMPTY_CHAR;

    // Calcul des nouvelles positions potentielles
    unsigned new_row = currentPlayer.coordinates.first;
    unsigned new_col = currentPlayer.coordinates.second;

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
    if (new_row >= 0 && new_row < gameGrid.size() &&
        new_col >= 0 && new_col < gameGrid[0].size())
    {
        if (gameGrid[new_row][new_col] != '#')
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

    GameKeybinds keybinds;
    GameSettings settings;
    loadSettings(keybinds, settings);
    size_t players;
    cout << "Bvn, entrez le nbr de joueur : ";
    cin >> players;
    vector<User> userList;

    if (players < 2 || players > 4) {
        cout << "Invalid number, please try again." << endl;
        exit(2);
    }


    for (size_t i = 0; i < players; ++i) {
        User user;
        cout << "Joueur " << i + 1 << " entrez votre token, color et name ";
        cin >> user.token >> user.color >> user.name;
        transform(user.color.begin(), user.color.end(), user.color.begin(),
              ::toupper);
        userList.push_back(user);
    }

    unsigned PartyNum (1);
    const unsigned KMaxPartyNum (500);
    Grid GameGrid;

    bool Victory (false);


    InitGrid(GameGrid, 10, 100, userList);

    DisplayGrid (GameGrid, userList);

    while (PartyNum <= KMaxPartyNum && ! Victory)
    {

        cout << PartyNum  << (PartyNum == 1 ? "er" : "eme") << " tour." << endl << "Joueur "
             << settings.currentUserTurn+1 << ", entrez un déplacement : " << endl;
        string input;
        char inputChar;
/*
        cout << keybinds.KeyUpLeft << " " << keybinds.KeyUp << " " << keybinds.KeyUpRight << endl;
        cout << keybinds.KeyLeft << "   " << keybinds.KeyRight << endl;
        cout << keybinds.KeyDownLeft << " " << keybinds.KeyDown << " " << keybinds.KeyDownRight << endl;*/
        getline(cin,input);

        inputChar = toupper (input[0]);

        moveToken (GameGrid, inputChar, userList[settings.currentUserTurn], keybinds);


        clearScreen();
        DisplayGrid (GameGrid, userList);

        //Victiry test
        //if (CoordPlayer1 == CoordPlayer2) Victory = true;

        //Increase party's number
        ++PartyNum;

        //Player changing

        ++settings.currentUserTurn;
        settings.currentUserTurn %= userList.size();

    }//while (no victory)

    if (!Victory)
    {
        color (COLORS.find("MAGENTA")->second);
        cout << "Aucun vainqueur" << endl;
    } else {
        color (COLORS.find("GREEN")->second);
        cout << "Félicitations Joueur" << (settings.currentUserTurn)
             << " vous avez gagné :)" << endl;
        color (COLORS.find("RESET")->second);
    }


    return 0;
} //ppal ()
