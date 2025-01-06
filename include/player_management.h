//
// Created by maxime on 1/6/25.
//

#ifndef PLAYER_MANAGEMENT_H
#define PLAYER_MANAGEMENT_H


#include "type.h"

struct Player {
    vector<vector<string>> inventory;
    char token ;
    string color;
    string name;
    GridCoordinates coordinates = {100,100};
    bool isAlive = true;
};

void createPlayers(const unsigned short PLAYERS, vector<Player> &vPlayer);
void eliminatePlayer(const char& playerToken ,vector<Player>& users);
char getWinner(vector<Player>& users);

#endif //PLAYER_MANAGEMENT_H
