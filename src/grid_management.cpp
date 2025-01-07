#include <iostream>
#include <iomanip>
#include "../include/grid_management.h"
#include "../include/terminal_management.h"

#include "../include/type.h" //nos types


using namespace std;






void displayGrid (const Grid & GAME_GRID, const vector<Player> & USER_LIST)
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

            for (Player u: USER_LIST) {
                   if (c != u.token) continue;
                    setColor(COLORS.find(u.color)->second); // Couleur pour le joueur 1
                    cout << c;
                    setColor(COLORS.find("RESET")->second);
                }
        }
        cout << '|' << endl;
    }
    cout << " " << string (KNbCol , '-') << " " << endl;
} // ShowGameGridrix ()


#include <cstdlib> // pour rand() et srand()
#include <ctime>   // pour time()


void initGrid (Grid & gameGrid, unsigned rows, unsigned columns,
               vector<Player> & vPlayer, const GameSettings &SETTINGS) {
    // Initialisation de la grille avec des cases vides
    gameGrid.resize(rows);

    const GridRow KLine(columns, EMPTY_CHAR);

    for (GridRow & ALine : gameGrid) {
        ALine = KLine;
    }

    // Génération des murs aléatoires
    srand(static_cast<unsigned>(time(0))); // Initialisation du générateur de nombres aléatoires
    int nombre_murs = static_cast<int>((rows * columns) * double(SETTINGS.wallFrequency)/100.0); // 20% des cases sont des murs

    for (int i = 0; i < nombre_murs; ++i) {
        int x = rand() % rows;
        int y = rand() % columns;

        // Vérifie que la case est vide et n'est pas occupée par un joueur
        if (gameGrid[x][y] == EMPTY_CHAR) {
            gameGrid[x][y] = WALL_CHAR; // KWall représente un mur
        } else if (gameGrid[x][y] != EMPTY_CHAR && gameGrid[x][y] != WALL_CHAR) {
            gameGrid[x][y] = 'P'; // KWall représente un mur
        } else {
            --i; // Réessayer si la case est déjà occupée
        }
    }

    // Placement des joueurs

    size_t index = 0;
    for (auto it = vPlayer.begin(); it != vPlayer.end(); ++it, ++index) {
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


    for (Player v : vPlayer) {
        gameGrid[v.coordinates.first][v.coordinates.second] = v.token;
    }
}
