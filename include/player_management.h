//
// Created by maxime on 1/6/25.
//

#ifndef PLAYER_MANAGEMENT_H
#define PLAYER_MANAGEMENT_H


#include "type.h"


struct Player {
    std::vector<std::vector<std::string>> inventory;
    char token ;
    std::string color;
    std::string name;
    GridCoordinates coordinates = {100,100};
    bool isAlive = true;
};

void createPlayers(const unsigned short PLAYERS, std::vector<Player> &vPlayer);
void eliminatePlayer(const char& playerToken ,std::vector<Player>& users);
Player getWinner(std::vector<Player>& users);

#endif //PLAYER_MANAGEMENT_H
