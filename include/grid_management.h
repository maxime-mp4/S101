#ifndef GRID_MANAGEMENT_H
#define GRID_MANAGEMENT_H

/*!
 * \file grid_management.h
 * \brief Set of usefull functions for the grid management
 * \author Alain Casali
 * \author Marc Laporte
 * \version 1.0
 * \date 18 décembre 2018
 */

#include "type.h"
#include "player_management.h" //nos types


/**
 * @brief Display the grid according to the parameters
 * @param[in] Mat : Game grid
 * @param[in] Params : : List of usefull parameters
 * @param USER_LIST
 * @fn void DisplayGrid (const Grid & Mat, const CMyParam & Params, bool ShowLineNumber = true, bool ShowColor = true);
 */
void displayGrid (const Grid & GAME_GRID, const std::vector<Player> &USER_LIST);


/*!
 * \brief Initialization of the Matrix from scratch
 * \param[out] Mat the matrix to be initialized
 * \param[in] Parms Set of game's parameters
 * \param USER_LIST
 * @fn void InitGrid (Grid & Mat, const CMyParam & Params, GridCoordinates & CoordPlayer1, GridCoordinates & CoordPlayer2);
 */

void initGrid (Grid & gameGrid, unsigned rows, unsigned columns,
               std::vector<Player> & vPlayer, const GameSettings &SETTINGS);

#endif // GRID_MANAGEMENT_H
