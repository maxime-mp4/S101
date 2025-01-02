#include <iostream>
#include <iomanip>
#include "../include/gridmanagement.h"

#include "../include/type.h" //nos types


using namespace std;



void ClearScreen()
{
    cout << "\033[H\033[2J";
}// ClearScreen ()

void Color (const string & Col)
{
    cout << "\033[" << Col.c_str () <<"m";
} // Color ()


void DisplayGrid (const Grid & Mat, const GameSettings & settings)
{
    const unsigned KNbLine = Mat.size ();
    const unsigned KNbCol  = Mat[0].size ();
    cout << string (KNbCol + 2 , '-') << endl;
    for (unsigned i (0); i < KNbLine; ++i)
    {
        cout << '|';
        for (char c : Mat[i])
        {

            if (c == settings.tokenP1) {
                Color(KColor.find("KBlue")->second); // Couleur pour le joueur 1
                cout << c;
                Color(KColor.find("KReset")->second); // Réinitialiser la couleur
            } else if (c == settings.tokenP2) {
                Color(KColor.find("KRed")->second); // Couleur pour le joueur 2
                cout << c;
                Color(KColor.find("KReset")->second); // Réinitialiser la couleur
            } else {
                cout << c; // Cas par défaut, afficher sans couleur
            }


        }
        cout << '|' << endl;
    }
    cout << string (KNbCol + 2 , '-') << endl;
}// ShowMatrix ()


void InitGrid (Grid & Mat, unsigned NbLine, unsigned NbColumn, GridCoordinates & CoordPlayer1, GridCoordinates & CoordPlayer2, const GameSettings & settings)
{
    Mat.resize (NbLine);
    const GridRow KLine (NbColumn, KEmpty);
    for (GridRow &ALine : Mat)
        ALine = KLine;

    CoordPlayer1.first = 0;
    CoordPlayer1.second = NbColumn - 1;
    Mat [CoordPlayer1.first][CoordPlayer1.second] = settings.tokenP1;
    CoordPlayer2.first = NbLine - 1;
    CoordPlayer2.second =0;
    Mat [CoordPlayer2.first][CoordPlayer2.second]   = settings.tokenP2;
}//InitMat ()
