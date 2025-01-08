#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <yaml-cpp/yaml.h>

/*!
 * \file menu.h
 * \brief Contient les fonctions pour afficher et naviguer dans les différents menus du jeu.
 * \author maxime-mp4
 * \date 6 janvier 2025
 */

/*!
 * \brief Affiche les réglages d'une catégorie YAML donnée.
 *
 * Cette fonction permet d'afficher les paramètres d'une catégorie spécifique à partir d'un
 * nœud YAML.
 *
 * \param[in] CATEGORY_NODE Le nœud YAML contenant les réglages de la catégorie.
 * \param[in] CATEGORY_NAME Le nom de la catégorie à afficher.
 */
void displaySettings(const YAML::Node &CATEGORY_NODE, const std::string &CATEGORY_NAME);

/*!
 * \brief Affiche le menu des réglages.
 *
 * Permet à l'utilisateur de naviguer et de modifier les réglages du jeu. Affiche un message
 * supplémentaire en cas d'erreur ou d'invite optionnelle.
 *
 * \param[in] fallbackMessage Message supplémentaire à afficher (par défaut vide).
 */
void displaySettingsMenu(const std::string &fallbackMessage = "");

/*!
 * \brief Affiche le menu principal du jeu.
 *
 * Cette fonction présente les options principales du jeu et permet à l'utilisateur
 * d'accéder aux différentes sections du programme.
 *
 * \param[in] fallbackMessage Message supplémentaire à afficher (par défaut vide).
 */
void displayMenu(const std::string &fallbackMessage = "");

#endif //MENU_H
