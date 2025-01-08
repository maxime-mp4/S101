#ifndef PLAYER_MANAGEMENT_H
#define PLAYER_MANAGEMENT_H

#include "type.h"

/*!
 * \file player_management.h
 * \brief Gestion des joueurs dans le jeu.
 * \author maxime-mp4
 * \date 6 janvier 2025
 */

/*!
 * \struct Player
 * \brief Représente un joueur dans le jeu.
 *
 * Cette structure contient les informations essentielles pour chaque joueur,
 * y compris son inventaire, son symbole, ses coordonnées et son état.
 */
struct Player {
    std::vector<std::vector<std::string>> inventory; /*!< Inventaire du joueur */
    char token; /*!< Symbole représentant le joueur sur la grille */
    std::string color; /*!< Couleur associée au joueur */
    std::string name; /*!< Nom du joueur */
    GridCoordinates coordinates = {100,100}; /*!< Coordonnées du joueur sur la grille */
    bool isAlive = true; /*!< Indique si le joueur est encore en jeu */
};

/*!
 * \brief Crée les joueurs pour le jeu.
 *
 * Initialise un certain nombre de joueurs et les ajoute à un vecteur.
 *
 * \param[in] PLAYERS Nombre de joueurs à créer.
 * \param[out] vPlayer Vecteur contenant les joueurs initialisés.
 */
void createPlayers(const unsigned short &PLAYERS, std::vector<Player> &vPlayer);

/*!
 * \brief Élimine un joueur du jeu.
 *
 * Marque un joueur comme éliminé en fonction de son symbole et le retire de la liste active.
 *
 * \param[in] playerToken Le symbole du joueur à éliminer.
 * \param[out] users Vecteur contenant tous les joueurs.
 */
void eliminatePlayer(const char& playerToken, std::vector<Player>& users);

/*!
 * \brief Détermine le gagnant du jeu.
 *
 * Renvoie le joueur restant après que tous les autres aient été éliminés.
 *
 * \param[in] users Vecteur contenant tous les joueurs.
 * \return Le joueur gagnant.
 */
Player getWinner(std::vector<Player>& users);

#endif //PLAYER_MANAGEMENT_H
