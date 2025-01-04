#ifndef TYPE_H
#define TYPE_H

/*!
 * \file type.h
 * \brief Definition of usefull types or aliases for the project
 * \author Alain Casali
 * \author Marc Laporte
 * \version 1.0
 * \date 18 décembre 2018
 */

#include <string>
#include <vector>
#include <map>

using namespace std;

/**
 * @brief GridRow : alias to a line of the matrix
 */
typedef vector <char> GridRow;

/**
 * @brief Grid : alias to a game grid type
 * @typedef vector <GridRow> Grid;
 */
typedef vector <GridRow> Grid;

/**
 * @brief GridCoordinates : a pair gathering the coordinates in the grid
 */
typedef pair <unsigned, unsigned> GridCoordinates;



/**
 * @brief Struct containing all the authorized keys in the struct CMyParam
 */
struct AuthorizedKey {
    /** List of authorized key for the type char in a struct CMyParam*/
    const vector <string> VParamChar {"KeyUp", "KeyDown", "KeyLeft", "KeyRight", "TokenP1", "TokenP2"};
    /** List of authorized key for the type string in a struct CMyParam*/
    const vector <string> VParamString {"ColorP1", "ColorP2"};
    /** List of authorized key for the type unsigned in a struct CMyParam*/
    const vector <string> VParamUnsigned {"NbRow", "NbColumn"};
};

/**
 * @brief KAuthorizedKey
 */
const AuthorizedKey AUTHORIZED_KEY;

/**
  * @brief KColor : map between the "human" color and its correspondence for the Unix terminal
  */

const map <string, string> COLORS
{
  {"RESET", "0"},
  {"BLACK", "30"},
  {"RED", "31"},
  {"GREEN", "32"},
  {"YELLOW", "33"},
  {"BLUE", "34"},
  {"MAGENTA", "35"},
  {"CYAN", "36"},

};

/**
 * @brief KEmpty : character for an empty cell
 */
const char EMPTY_CHAR = ' ';

const vector<string> BONUS_LIST = {"TURN_STEALING", "THROUGH_WALLS", "MOVING_FASTER"};
const vector<string> CHEAT_LIST = {"HATECPP", "RACISM", "123456789"};

/**
 * @brief CMyParamV2 : structure of all settings

 */

struct GameKeybinds {
    char keyUp;         // Haut
    char keyDown;       // Bas
    char keyLeft;       // Gauche
    char keyRight;      // Droite
    char keyUpLeft;     // Haut-gauche
    char keyUpRight;    // Haut-droite
    char keyDownLeft;   // Bas-gauche
    char keyDownRight;  // Bas-droite
};

struct GameSettings {
    size_t gridColumns = 10;     // Nombre de colonnes dans la grille
    size_t gridRows = 30;        // Nombre de lignes dans la grille
    unsigned short int wallFrequency;
    unsigned short int bonusFrequency;
    unsigned short int currentUserTurn = 0;
};

struct User {
    unsigned short int currentBonus;
    char token;
    string color;
    string name;
    GridCoordinates coordinates = {100,100};
};


/**
 * @brief CMyParamV2 : structure of all settings

 */

#endif // TYPE_H
