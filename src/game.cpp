#include <iostream>

#include "../include/game.h"
#include "../include/settings.h"
#include "../include/gridmanagement.h"

#include <map>
using namespace std;


void MoveToken (Grid & Mat, const char & Move, GridCoordinates & Pos, GameKeybinds & keybinds)
{
    char car = Mat[Pos.first][Pos.second];
    Mat[Pos.first][Pos.second] = KEmpty;

    // Calcul des nouvelles positions potentielles
    unsigned new_row = Pos.first;
    unsigned new_col = Pos.second;

    if (Move == keybinds.KeyUpLeft) { // Haut-gauche
        new_row--;
        new_col--;
    }
    else if (Move == keybinds.KeyUp) { // Haut
        new_row--;
    }
    else if (Move == keybinds.KeyUpRight) { // Haut-droite
        new_row--;
        new_col++;
    }
    else if (Move == keybinds.KeyLeft) { // Gauche
        new_col--;
    }
    else if (Move == keybinds.KeyRight) { // Droite
        new_col++;
    }
    else if (Move == keybinds.KeyDownLeft) { // Bas-gauche
        new_row++;
        new_col--;
    }
    else if (Move == keybinds.KeyDown) { // Bas
        new_row++;
    }
    else if (Move == keybinds.KeyDownRight) { // Bas-droite
        new_row++;
        new_col++;
    }
    else {
        // Mouvement invalide, ne rien faire
    }


    // Vérifie si les nouvelles coordonnées sont valides
    if (new_row >= 0 && new_row < Mat.size() &&
        new_col >= 0 && new_col < Mat[0].size())
    {
        Pos.first = new_row;
        Pos.second = new_col;
    }

    // Replace le caractère à la nouvelle position
    Mat[Pos.first][Pos.second] = car;
} // MoveToken ()


int ppal ()
{

    GameKeybinds keybinds;
    GameSettings settings;
    loadSettings(keybinds, settings);

    const unsigned KSize (10);
    unsigned PartyNum (1);
    const unsigned KMaxPartyNum (100000000000000);
    Grid Mat;

    srand(time(0));
    int randomNum = rand() % 2;

    bool Player1Turn (randomNum);
    bool Victory (false);

    GridCoordinates CoordPlayer1, CoordPlayer2;


    InitGrid(Mat, 10, 30, CoordPlayer1, CoordPlayer2, settings);

    DisplayGrid (Mat, settings);

    while (PartyNum <= KMaxPartyNum && ! Victory)
    {

        cout << PartyNum  << (PartyNum == 1 ? "er" : "eme") << " tour." << endl << "Joueur "
             << (Player1Turn ? "1 (X)" : "2 (O)") << ", entrez un déplacement : " << endl;
        char Move;
        cin >> Move;

        Move = toupper (Move);
        MoveToken (Mat, Move, (Player1Turn ? CoordPlayer1: CoordPlayer2), keybinds);
        ClearScreen();
        DisplayGrid (Mat, settings);

        //Victiry test
        if (CoordPlayer1 == CoordPlayer2) Victory = true;

        //Increase party's number
        ++PartyNum;

        //Player changing
        Player1Turn = !Player1Turn;
    }//while (no victory)

    if (!Victory)
    {
        Color (KColor.find("KMAgenta")->second);
        cout << "Aucun vainqueur" << endl;
        return 1;
    }

    Color (KColor.find("KGreen")->second);
    cout << "Félicitations Joueur" << (Player1Turn ? '2' : '1')
         << " vous avez gagné :)" << endl;
    Color (KColor.find("KReset")->second);
    return 0;
} //ppal ()
