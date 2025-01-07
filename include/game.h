#ifndef GAME_H
#define GAME_H

/*!
 * \file game.h
 * \brief Set of usefull functions for the game
 * \author Alain Casali
 * \author Marc Laporte
 * \version 1.0
 * \date 18 décembre 2018
 */

#include "type.h"
#include "player_management.h"

/*!
 * \brief Move the current token according to the character in the 2nd parameter
 * \param[in, out] Mat the matrix before and after the move
 * \param[in] movement the key pressed by the user
 * \param[in, out] Pos the player's position before and after the move
 */

void moveToken (Grid & gameGrid, char & movement, Player &currentPlayer, const GameKeyBinds &KEY_BINDS);

/**
 * @brief new main
 * @return 0 if everything is OK
 * @fn int ppal ();
 */
int initGame ();

#endif // GAME_H
