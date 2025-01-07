#ifndef PARAMS_H
#define PARAMS_H

/**
 * \file settings.h
 * \brief Paramters' definition and associated functions
 * \author Alain Casali
 * \author Marc Laporte
 * \version 1.0
 * \date 18 décembre 2018
 */

#include "type.h"
#include <yaml-cpp/yaml.h>

std::vector<char> loadSettings (GameKeyBinds & keyBinds, GameSettings & settings);

bool isValidKeyBind(const char &KEY, const std::vector<char> &V_KEY_BINDS);

bool isValidType(const std::string& KEY, const std::string& INPUT);

void editSettings(const std::string &CATEGORY);

void displaySettings(const YAML::Node &CATEGORY_NODE, const std::string &CATEGORY_NAME);

/**
 * @brief Initialize the set of parameters from scratch
 * @param[out] Param : List of usefull parameters
 * @fn void InitParams (CMyParam & Param);
 */


/**
 * @brief Load the set of parameters from a YAML file
 * @param[out] Param : List of usefull parameters
 * @param[in] FileName : Path to the file to load
 * @fn void LoadParams (CMyParam & Param);
 * @return 0 if everything is OK, return 2 if it can't load the file
 */

#endif // PARAMS_H
