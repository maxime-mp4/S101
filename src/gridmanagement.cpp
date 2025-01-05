#include <iostream>
#include <iomanip>
#include "../include/gridmanagement.h"

#include "../include/type.h" //nos types


using namespace std;



void clearScreen()
{
    cout << "\033[H\033[2J";
}// ClearScreen ()

void color (const string & COL)
{
    cout << "\033[" << COL.c_str () <<"m";
} // Color ()




void DisplayGrid (const Grid & GAME_GRID, const vector<User> & USER_LIST)
{
    const unsigned KNbLine = GAME_GRID.size ();
    const unsigned KNbCol  = GAME_GRID[0].size ();

    cout << " " << string (KNbCol , '-') << " " << endl;

    for (unsigned i (0); i < KNbLine; ++i)
    {
        cout << '|';

        for (char c : GAME_GRID[i])
        {

            if (c == ' ' || c == '#') {
                cout << c;
            }

            for (User u: USER_LIST) {
                   if (c != u.token) continue;
                    color(COLORS.find(u.color)->second); // Couleur pour le joueur 1
                    cout << c;
                    color(COLORS.find("RESET")->second);
                }
        }
        cout << '|' << endl;
    }
    cout << " " << string (KNbCol , '-') << " " << endl;
} // ShowGameGridrix ()


#include <cstdlib> // pour rand() et srand()
#include <ctime>   // pour time()

void InitGrid (Grid & gameGrid, unsigned rows, unsigned columns,
               vector<User> &USER_LIST) {
    // Initialisation de la grille avec des cases vides
    gameGrid.resize(rows);

    const GridRow KLine(columns, EMPTY_CHAR);

    for (GridRow & ALine : gameGrid) {
        ALine = KLine;
    }

    // Génération des murs aléatoires
    srand(static_cast<unsigned>(time(0))); // Initialisation du générateur de nombres aléatoires
    int nombre_murs = static_cast<int>((rows * columns) * 0.1); // 20% des cases sont des murs

    for (int i = 0; i < nombre_murs; ++i) {
        int x = rand() % rows;
        int y = rand() % columns;

        // Vérifie que la case est vide et n'est pas occupée par un joueur
        if (gameGrid[x][y] == EMPTY_CHAR) {
            gameGrid[x][y] = '#'; // KWall représente un mur
        } else if (gameGrid[x][y] != EMPTY_CHAR && gameGrid[x][y] != '#') {
            gameGrid[x][y] = 'P'; // KWall représente un mur
        } else {
            --i; // Réessayer si la case est déjà occupée
        }
    }

    // Placement des joueurs

    size_t index = 0;
    for (auto it = USER_LIST.begin(); it != USER_LIST.end(); ++it, ++index) {
        switch (index) {
            case 0:
                it->coordinates.first = 0;
            it->coordinates.second = 0;
            break;
            case 1:
                it->coordinates.first = 0;
            it->coordinates.second = columns - 1;
            break;
            case 2:
                it->coordinates.first = rows - 1;
            it->coordinates.second = columns - 1;
            break;
            case 3:
                it->coordinates.first = rows - 1;
            it->coordinates.second = 0;
            break;
        }
    }


    for (User u : USER_LIST) {
        gameGrid[u.coordinates.first][u.coordinates.second] = u.token;
    }
}
