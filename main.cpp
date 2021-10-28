#include <iostream>
#include "minesweeper.h"
using namespace std;

bool gewonnen(int counter){
    if (counter == 0) {
        cout << "Du hast gewonnen!" << "\n";  //Die Gewinnbedingung
        return true;
    }
    return false;
}


int main() {

    initializieren(15);


    Darstellung();



    while (Spielzug()) {

        Harmlos();


        int counter = 0;


        for (int i = 0; i < 12; i++) {
            for (int j = 0; j < 12; j++) {          //Das ist die Funktion für die verbleibenden Felder

                if (f[i * 12 + j].b == offen) {

                    counter++;

                }

            }
        }

        cout << "Verbleibende Felder:" << " " << counter << "\n";
        Darstellung();

        if (gewonnen(counter)) {
            break;
        }
    }

}

