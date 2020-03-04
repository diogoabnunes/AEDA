// Tokyo2020 | ProjetoParte1

#include <iostream>
#include "Comitiva.h"
#include "Medalhas.h"
#include "menu.h"
using namespace std;

int main() {
    cout << "\nDelegacao Olimpica de Portugal - Toquio 2020" << endl << endl;

    string pais = "portugal";
    string medals = "medalhas";

    Comitiva comitiva(pais); //creates a comitiva of class Comitiva with info in file portugal.txt
    Medalhas medalhas(medals); //creates a medal talbe with info in file medalhas.txt

    paginaInicial(comitiva, medalhas);

    comitiva.refreshComitiva(pais);
    medalhas.refreshMedalhas(medals);

    cout << "\nTHE END!" << endl;
    return 0;
}