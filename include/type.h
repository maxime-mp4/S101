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

/**
 * @brief GridRow : alias to a line of the matrix
 */
typedef std::vector <char> GridRow;

/**
 * @brief Grid : alias to a game grid type
 * @typedef vector <GridRow> Grid;
 */
typedef std::vector <GridRow> Grid;

/**
 * @brief GridCoordinates : a pair gathering the coordinates in the grid
 */
typedef std::pair <unsigned, unsigned> GridCoordinates;



/**
 * @brief Struct containing all the authorized keys in the struct CMyParam
 */
struct AuthorizedKey {
    /** List of authorized key for the type char in a struct CMyParam*/
    const std::vector <std::string> VParamChar {"KeyUp", "KeyDown", "KeyLeft", "KeyRight", "TokenP1", "TokenP2"};
    /** List of authorized key for the type string in a struct CMyParam*/
    const std::vector <std::string> VParamString {"ColorP1", "ColorP2"};
    /** List of authorized key for the type unsigned in a struct CMyParam*/
    const std::vector <std::string> VParamUnsigned {"NbRow", "NbColumn"};
};

/**
 * @brief KAuthorizedKey
 */
const AuthorizedKey AUTHORIZED_KEY;

/**
  * @brief KColor : map between the "human" color and its correspondence for the Unix terminal
  */

const std::map <std::string, std::string> COLORS
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
const char WALL_CHAR = '#';

const std::vector<std::string> BONUS_LIST = {"TURN_STEALING", "THROUGH_WALLS", "MOVING_FASTER"};
const std::vector<std::string> CHEAT_LIST = {"HATECPP", "RACISM", "123456789"};

/**
 * @brief CMyParamV2 : structure of all settings

 */

struct GameKeyBinds {
    char keyUp = 'Z';         // Haut
    char keyDown = 'X';       // Bas
    char keyLeft = 'Q';       // Gauche
    char keyRight = 'D';      // Droite
    char keyUpLeft = 'A';     // Haut-gauche
    char keyUpRight = 'E';    // Haut-droite
    char keyDownLeft = 'W';   // Bas-gauche
    char keyDownRight = 'C';  // Bas-droite
    char keyHelp = '/';
    char keyInventory = 'I';
};

struct GameSettings {
    size_t gridColumns = 10;
    size_t gridRows = 10;
    double wallFrequency = 0.1;
    double bonusFrequency = 0.2;
    unsigned short currentUserTurn = 1;
    bool canTeleport = false;
};


/**
 * @brief CMyParamV2 : structure of all settings
 */

#endif // TYPE_H
