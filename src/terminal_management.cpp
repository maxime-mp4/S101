#include "../include/terminal_management.h"

#include <iostream>
#include <unistd.h>

using namespace std;


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