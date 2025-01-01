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
const AuthorizedKey KAuthorizedKey;

/**
  * @brief KColor : map between the "human" color and its correspondence for the Unix terminal
  */

const map <string, string> KColor
{
  {"KReset", "0"},
  {"KBlack", "30"},
  {"KRed", "31"},
  {"KGreen", "32"},
  {"KYellow", "33"},
  {"KBlue", "34"},
  {"KMagenta", "35"},
  {"KCyan", "36"},

};

/**
 * @brief KEmpty : character for an empty cell
 */
const char KEmpty = ' ';

#endif // TYPE_H
