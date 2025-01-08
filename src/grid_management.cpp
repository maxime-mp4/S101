#include <iostream>
#include <cstdlib>
#include <ctime>

#include "../include/grid_management.h"
#include "../include/terminal_management.h"
#include "../include/type.h"

using namespace std;

void displayGrid (Grid & GAME_GRID, const vector<Player> & USER_LIST)
{
    const unsigned NUMBER_LINE = GAME_GRID.size ();
    const unsigned NUMBER_COLUMN  = GAME_GRID[0].size ();
    cout << " " << string (NUMBER_COLUMN , '-') << " " << endl;

    for (unsigned i (0); i < NUMBER_LINE; ++i)
    {
        cout << '|';

        for (char c : GAME_GRID[i])
        {

            if (c == ' ' || c == '#' || c == 'T') {
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
    cout << " " << string (NUMBER_COLUMN , '-') << " " << endl;
} // displayGrid ()




void initGrid (Grid & gameGrid, unsigned rows, unsigned columns,
               vector<Player> & vPlayer, const GameSettings &SETTINGS) {
    gameGrid.resize(rows);

    const GridRow KLine(columns, EMPTY_CHAR);

    for (GridRow & ALine : gameGrid) {
        ALine = KLine;
    }

    srand(static_cast<unsigned>(time(0)));
    int nombre_murs = static_cast<int>((rows * columns) * double(SETTINGS.wallFrequency) / 100.0);

    for (int i = 0; i < nombre_murs; ++i) {

        int x = rand() % rows;
        int y = rand() % columns;

        if (gameGrid[x][y] == EMPTY_CHAR) {
            gameGrid[x][y] = WALL_CHAR;
        } else {
            --i;
        }
    }

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
} // initGrid()
