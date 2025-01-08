#ifndef GRID_MANAGEMENT_H
#define GRID_MANAGEMENT_H

/*!
 * \file grid_management.h
 * \brief Ensemble de fonctions utiles pour la gestion de la grille.
 * \author maxime-mp4
 * \version 1.0
 * \date 8 janvier 2025
 */

#include "type.h"
#include "player_management.h" // Nos types

/*!
 * \brief Affiche la grille de jeu selon les paramètres donnés.
 *
 * Cette fonction affiche la grille de jeu en utilisant les joueurs à leur position actuelle.
 * Elle peut afficher ou non les numéros de ligne et les couleurs en fonction des options.
 *
 * \param[in] GAME_GRID La grille de jeu.
 * \param[in] USER_LIST Liste des joueurs avec leurs positions actuelles.
 */

void displayGrid (Grid &GAME_GRID, const std::vector<Player> &USER_LIST);

/*!
 * \brief Initialise la grille de jeu à partir de zéro.
 *
 * Cette fonction crée une grille vide avec les dimensions spécifiées, place les joueurs
 * à leur position initiale, et configure les paramètres de la grille selon les réglages du jeu.
 *
 * \param[out] gameGrid La grille à initialiser.
 * \param[in] rows Nombre de lignes de la grille.
 * \param[in] columns Nombre de colonnes de la grille.
 * \param[in, out] vPlayer Vecteur contenant les joueurs à positionner.
 * \param[in] SETTINGS Paramètres actuels du jeu.
 */
void initGrid (Grid & gameGrid, unsigned rows, unsigned columns,
               std::vector<Player> & vPlayer, const GameSettings &SETTINGS);

#endif // GRID_MANAGEMENT_H
