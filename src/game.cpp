#include <iostream>

#include "../include/game.h"
#include "../include/params.h"
#include "../include/gridmanagement.h"

#include <map>
using namespace std;


void MoveToken (Grid & Mat, const char & Move, GridCoordinates & Pos)
{
    char car = Mat [Pos.first][Pos.second];
    Mat [Pos.first][Pos.second] = KEmpty;

    switch (Move)
    {
    case 'A':
        if(Mat[Pos.first].size() <= Pos.first - 1 || Mat[Pos.second].size() <= Pos.second - 1) break;
        -- Pos.first;
        -- Pos.second;
        break;
    case 'Z':
        if(Mat[Pos.first].size() <= Pos.first - 1) break;
        --Pos.first;
        break;
    case 'E':
        if(Mat[Pos.first].size() <= Pos.first - 1 || Mat[Pos.second].size() <= Pos.second + 1) break;
        --Pos.first;
        ++Pos.second;
        break;
    case 'Q':
        if(Mat[Pos.second].size() <= Pos.second - 1) break;
        --Pos.second;
        break;
    case 'D':
        if(Mat[Pos.second].size() <= Pos.second + 1) break;
        ++Pos.second;
        break;
    case 'W':
        if(Mat[Pos.first].size() <= Pos.first + 1 || Mat[Pos.second].size() <= Pos.second - 1) break;
        ++Pos.first;
        --Pos.second;
        break;
    case 'X':
        if(Mat[Pos.first].size() <= Pos.first + 1) break;
        ++Pos.first;
        break;
    case 'C':
        if(Mat[Pos.first].size() <= Pos.first + 1 || Mat[Pos.second].size() <= Pos.second + 1) break;
        ++Pos.first;
        ++Pos.second;
        break;
    }
    Mat [Pos.first][Pos.second] = car;
} //MoveToken ()


int ppal (void)
{

    const unsigned KSize (10);
    unsigned PartyNum (1);
    const unsigned KMaxPartyNum (KSize * KSize);
    Grid Mat;

    bool Player1Turn (true);
    bool Victory (false);

    GridCoordinates PosPlayer1, PosPlayer2;


    InitGrid(Mat, 10, 10, PosPlayer1, PosPlayer2);

    DisplayGrid (Mat);

    while (PartyNum <= KMaxPartyNum && ! Victory)
    {

        cout << "tour numero : " << PartyNum << ", Joueur"
             << (Player1Turn ? '1' : '2') << ", entrez un déplacement : ";
        cout << Mat[PosPlayer2.first].size() << Mat[PosPlayer2.second].size();
        char Move;
        cin >> Move;

        Move = toupper (Move);
        MoveToken (Mat, Move, (Player1Turn ? PosPlayer1: PosPlayer2));
        ClearScreen();
        DisplayGrid (Mat);

        //Victiry test
        if (PosPlayer1 == PosPlayer2) Victory = true;

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
