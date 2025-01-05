/*!
 * \file   main.cpp
 * \authors Alain Casali, Marc Laporte
 * \date december 8 2016
 * \brief   Terminal's color management
 *          beginning of the project titled "catch me if you can"
 */

#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <yaml-cpp/yaml.h>

#include "include/game.h"
#include "include/settings.h"

using namespace std;


void setRawMode(bool enable, struct termios& oldt) {
    struct termios newt;

    if (enable) {
        // Obtenir les paramètres actuels du terminal
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;

        // Désactiver le mode canonique et l'écho
        newt.c_lflag &= ~(ICANON | ECHO);

        // Appliquer les nouveaux paramètres
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    } else {
        // Restaurer les paramètres originaux
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    }
}

/**
 * @brief main
 * @return return 0 iff everything is OK, 1 if we have an exception, 2 if we can't load the params' file
 */
int main()
{
    struct termios oldt;

    //setRawMode(true, oldt);

        testVoid();
        //return ppal ();

    //setRawMode(false, oldt);
} //main ()



