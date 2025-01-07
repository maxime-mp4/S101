//
// Created by maxime on 1/6/25.
//

#include "../include/terminal_management.h"
#include <termios.h>
#include <iostream>
#include <unistd.h>

using namespace std;

static struct termios oldt;  // Déclaration globale pour stocker les paramètres du terminal

void setRawMode(bool enable) {
    struct termios newt;

    if (enable) {
        // Obtenir les paramètres actuels du terminal et les stocker dans oldt
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;

        // Désactiver le mode canonique (ICANON), l'écho (ECHO), et d'autres comportements de traitement de ligne
        newt.c_lflag &= ~(ICANON | ECHO | ISIG); // Désactive le mode canonique, l'écho et les signaux

        // Désactiver les tampons de lecture (ne pas attendre Enter pour valider une ligne)
        newt.c_cc[VMIN] = 1;  // Lire un caractère à la fois
        newt.c_cc[VTIME] = 0; // Pas de timeout

        // Appliquer les nouveaux paramètres
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    } else {
        // Restaurer les paramètres originaux
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    }
}

string createHyperLink (const string &LINK, const string &TEXT){

	return "\033]8;;" + LINK + "\033\\" + TEXT + "\033]8;;\033\\";
  }



void clearScreen()
{
    system("clear");
}// ClearScreen ()

void setColor (const string & COL)
{
    cout << "\033[" << COL <<"m";
} // Color ()