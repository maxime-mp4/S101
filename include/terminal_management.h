//
// Created by maxime on 1/6/25.
//

#ifndef TERMINAL_MANAGEMENT_H
#define TERMINAL_MANAGEMENT_H

#include <iostream>


void setRawMode(bool enable);

/**
 * @brief Clear the current terminal
 * @fn void ClearScreen ();
 */

void clearScreen ();

/**
 * @brief Set the color of the future input in the terminal
 * @param COL
 * @fn void Color (const string & Col);
 */

void setColor (const std::string &COL);

std::string createHyperLink (const std::string &LINK, const std::string &TEXT);


#endif //TERMINAL_MANAGEMENT_H
