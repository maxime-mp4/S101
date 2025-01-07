//
// Created by maxime on 1/6/25.
//

#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <yaml-cpp/yaml.h>

void displaySettings(const YAML::Node &CATEGORY_NODE, const std::string &CATEGORY_NAME);
void displaySettingsMenu(const std::string &fallbackMessage = "");
void displayMenu(const std::string &fallbackMessage = "");

#endif //MENU_H
