#ifndef GAME_H
#define GAME_H

/*!
 * \file game.h
 * \brief Ensemble de fonctions utiles pour le jeu.
 * \author maxime-mp4
 * \version 1.0
 * \date 8 janvier 2025
 */

#include "type.h"
#include "player_management.h"

/*!
 * \brief Déplace le jeton du joueur sur la grille selon la touche pressée.
 *
 * Cette fonction met à jour la position du joueur sur la grille en fonction de la touche
 * pressée. Elle gère également la téléportation si cette fonctionnalité est activée
 * dans les réglages.
 *
 * \param[in, out] gameGrid La grille du jeu avant et après le déplacement.
 * \param[in] movement La touche pressée par l'utilisateur pour indiquer la direction.
 * \param[in, out] currentPlayer Le joueur dont le jeton est déplacé.
 * \param[in] KEY_BINDS Les raccourcis clavier pour les mouvements du joueur.
 * \param[in] SETTINGS Les réglages actuels du jeu, y compris les règles de téléportation.
 * \param[in] ROUND_NUMBER Le numéro actuel du tour, utilisé pour limiter la téléportation
 * au début du jeu.
 */

void moveToken (Grid & gameGrid, char & movement, Player & currentPlayer,
                const GameKeyBinds & KEY_BINDS, const GameSettings & SETTINGS,
                const unsigned & ROUND_NUMBER);

/*!
 * \brief Initialise le jeu et lance la boucle principale.
 *
 * Cette fonction configure le jeu, initialise les composants nécessaires et
 * démarre la séquence de jeu principale.
 *
 * \return 0 si le jeu s'est initialisé et exécuté correctement, ou un code d'erreur sinon.
 */
int initGame ();

#endif // GAME_H
