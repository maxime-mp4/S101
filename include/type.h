#ifndef TYPE_H
#define TYPE_H

/*!
 * \file type.h
 * \brief Definition of useful types or aliases for the project
 * \author Alain Casali
 * \author Marc Laporte
 * \version 1.0
 * \date 18 December 2018
 */

#include <string>
#include <vector>
#include <map>

/**
 * @brief GridRow : Alias for a line in the matrix.
 *
 * Represents a row in a game grid, defined as a vector of characters.
 */
typedef std::vector <char> GridRow;

/**
 * @brief Grid : Alias for a game grid type.
 *
 * Represents a game grid as a 2D vector of GridRow, forming the complete matrix.
 */
typedef std::vector <GridRow> Grid;

/**
 * @brief GridCoordinates : Pair representing coordinates in the grid.
 *
 * Stores the row and column coordinates in the grid as an unsigned pair.
 */
typedef std::pair <unsigned, unsigned> GridCoordinates;

/**
 * @brief KColor : Map between human-readable color names and their Unix terminal equivalents.
 *
 * This map provides a correspondence between common color names and their corresponding escape codes for terminal output.
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
 * @brief KEmpty : Character representing an empty cell in the grid.
 *
 * This constant defines the character used to represent empty spaces in the game grid.
 */

const char EMPTY_CHAR = ' ';

/**
 * @brief KWall : Character representing a wall in the grid.
 *
 * This constant defines the character used to represent walls or obstacles in the game grid.
 */

const char WALL_CHAR = '#';

/**
 * @brief BONUS_LIST : List of available bonuses in the game.
 *
 * This list contains all the possible bonus types that players can obtain during the game.
 */

const std::vector<std::string> BONUS_LIST = {"TURN_STEALING", "THROUGH_WALLS", "MOVING_FASTER"};

/**
 * @brief CHEAT_LIST : List of cheat codes available in the game.
 *
 * This list contains all the cheat codes that can be used to alter the game's behavior.
 */

const std::vector<std::string> CHEAT_LIST = {"HATECPP", "RACISM", "123456789"};

/**
 * @brief GameKeyBinds : Structure containing the key bindings for game controls.
 *
 * This structure holds the key bindings for various actions in the game, such as movement and inventory access.
 */

struct GameKeyBinds {
    char keyUp = 'Z';         ///< Key to move up
    char keyDown = 'X';       ///< Key to move down
    char keyLeft = 'Q';       ///< Key to move left
    char keyRight = 'D';      ///< Key to move right
    char keyUpLeft = 'A';     ///< Key to move up-left
    char keyUpRight = 'E';    ///< Key to move up-right
    char keyDownLeft = 'W';   ///< Key to move down-left
    char keyDownRight = 'C';  ///< Key to move down-right
    char keyHelp = '/';       ///< Key to open help
    char keyInventory = 'I';  ///< Key to open inventory
};

/**
 * @brief GameSettings : Structure containing the game settings.
 *
 * This structure holds all the settings related to the game grid, turn management, and gameplay features.
 */
struct GameSettings {
    size_t gridColumns = 10;          ///< Number of columns in the game grid
    size_t gridRows = 10;             ///< Number of rows in the game grid
    double wallFrequency = 0.1;       ///< Frequency of wall placement
    double bonusFrequency = 0.2;      ///< Frequency of bonus placement
    unsigned short currentUserTurn = 1; ///< Current user's turn
    bool canTeleport = false;         ///< Whether teleportation is allowed
};

#endif // TYPE_H
