#include "../include/terminal_management.h"

#include <iostream>
#include <unistd.h>
#include <termios.h>

using namespace std;

void setNonCanonicalMode() {
    struct termios t;

    // Récupère les paramètres actuels du terminal
    tcgetattr(STDIN_FILENO, &t);

    // Désactive le mode canonique et l'écho
    t.c_lflag &= ~(ICANON | ECHO);

    // Définit les nouveaux paramètres du terminal
    tcsetattr(STDIN_FILENO, TCSANOW, &t);
}

// Fonction pour restaurer les paramètres par défaut
void restoreDefaultMode() {
    struct termios t;

    // Récupère les paramètres actuels du terminal
    tcgetattr(STDIN_FILENO, &t);

    // Réactive le mode canonique et l'écho
    t.c_lflag |= (ICANON | ECHO);

    // Définit les paramètres par défaut
    tcsetattr(STDIN_FILENO, TCSANOW, &t);
}



string createHyperLink (const string &LINK, const string &TEXT){
	return "\033]8;;" + LINK + "\033\\" + TEXT + "\033]8;;\033\\";
 } // createHyperLink ()



void clearScreen()
{
    system("clear");
} // clearScreen ()

void setColor (const string & COL)
{
    cout << "\033[" << COL <<"m";
} // setColor ()