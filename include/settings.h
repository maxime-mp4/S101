#ifndef SETTINGS_H
#define SETTINGS_H

/*!
 * \file settings.h
 * \brief Définition des paramètres et des fonctions associées.
 * \author maxime-mp4
 * \version 1.0
 * \date 8 janvier 2025
 */

#include "type.h"
#include <yaml-cpp/yaml.h>

/*!
 * \brief Charge les paramètres du jeu et les raccourcis clavier depuis un fichier YAML.
 * \param[out] keyBinds Structure contenant les raccourcis clavier du jeu.
 * \param[out] settings Structure contenant les paramètres du jeu.
 * \return Un vecteur contenant les raccourcis clavier chargés.
 */
std::vector<char> loadSettings (GameKeyBinds & keyBinds, GameSettings & settings);

/*!
 * \brief Vérifie si une touche donnée est valide pour les raccourcis clavier.
 * \param[in] KEY La touche à vérifier.
 * \param[in] V_KEY_BINDS Le vecteur contenant toutes les touches valides.
 * \return true si la touche est valide, false sinon.
 */
bool isValidKeyBind(const char &KEY, const std::vector<char> &V_KEY_BINDS);

/*!
 * \brief Vérifie si le type d'une valeur entrée correspond à celui attendu pour une clé donnée.
 * \param[in] KEY La clé du paramètre à vérifier.
 * \param[in] INPUT La valeur entrée par l'utilisateur.
 * \return true si le type est valide, false sinon.
 */
bool isValidType(const std::string& KEY, const std::string& INPUT);

/*!
 * \brief Permet de modifier les paramètres d'une catégorie donnée.
 * \param[in] CATEGORY Le nom de la catégorie à modifier.
 */
void editSettings(const std::string &CATEGORY);

/*!
 * \brief Affiche les paramètres d'une catégorie YAML donnée.
 * \param[in] CATEGORY_NODE Le nœud YAML contenant les paramètres de la catégorie.
 * \param[in] CATEGORY_NAME Le nom de la catégorie à afficher.
 */
void displaySettings(const YAML::Node &CATEGORY_NODE, const std::string &CATEGORY_NAME);

#endif // SETTINGS_H
