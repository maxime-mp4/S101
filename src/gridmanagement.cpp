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


void DisplayGrid (const Grid & Mat)
{
    const unsigned KNbLine = Mat.size ();
    const unsigned KNbCol  = Mat[0].size ();
    cout << string (KNbCol + 2 , '-') << endl;
    for (unsigned i (0); i < KNbLine; ++i)
    {
        cout << '|';
        for (char c : Mat[i])
        {

            switch (c)
            {
            case KEmpty:
                cout << c;
                break;
            case 'X':
                Color (KColor.find("KBlue")->second);
                cout << c;
                Color (KColor.find("KReset")->second);
                break;
            case 'O':
                Color (KColor.find("KBlue")->second);
                cout << c;
                Color (KColor.find("KReset")->second);
                break;

            }
        }
        cout << '|' << endl;
    }
    cout << string (KNbCol + 2 , '-') << endl;
}// ShowMatrix ()


void InitGrid (Grid & Mat, unsigned NbLine, unsigned NbColumn, GridCoordinates & PosPlayer1, GridCoordinates & PosPlayer2)
{
    Mat.resize (NbLine);
    const GridRow KLine (NbColumn, KEmpty);
    for (GridRow &ALine : Mat)
        ALine = KLine;

    PosPlayer1.first = 0;
    PosPlayer1.second = NbColumn - 1;
    Mat [PosPlayer1.first][PosPlayer1.second] = 'X';
    PosPlayer2.first = NbLine - 1;
    PosPlayer2.second =0;
    Mat [PosPlayer2.first][PosPlayer2.second]   = 'O';
}//InitMat ()
