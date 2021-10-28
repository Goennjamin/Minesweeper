//
// Created by leonw on 05.01.2021.
//

#ifndef PRAKTIKUM4_MINESWEEPER_H
#define PRAKTIKUM4_MINESWEEPER_H
#include <iostream>
#include "time.h"

using namespace std;

enum Belegung {offen, mine, aufgedeckt};

struct Feld{
    Belegung b;
    int nachbar;
};

Feld f[144];

int getMinen(int i, int j){ // j = x; i = y


    int counter = 0;

    for(int b = -1; b <= 1; b++){ // geht vom feld aus nach links und nach rechts

        if(j + b >= 0 && j+b < 12){ //hier wird gecheckt ob die funktion noch innerhalb der x achse vom spielfeld arbeitet

            for(int h = -1; h <= 1; h++){ //geht vom feld aus von unten nach oben

                if(i + h >= 0 && i+h < 12){ //hier wird gecheckt ob die funktion noch innerhalb der y ache vom spielfeld arbeitet

                    if((f[i * 12 + j].b) != mine && !(b==0 && h == 0)){ //hier wird gecheckt ob das Feld keine Mine ist, und auch ob es nicht das feld ist von dem aus wir die anderen betrachten

                        if(f[(i+h)*12+(j+b)].b == mine) // zum schluss wird geschaut ob das feld nebendran eine mine ist, und der counter geht dann dementsprechend hoch oder nicht

                            counter ++;
                    }
                }
            }

        }

    }
return counter;
}



void initializieren(int minen) {

    for(int i = 0; i < 12; i++) {
        for (int j = 0; j < 12; j++) {          //Hier wird jedesfeld mit den standartwerten initialisiert
            f[i * 12 +j].b = offen;
            f[i *12 +j].nachbar = 0;
        }
    }

    srand(time(NULL));


    for(int i = 0; i < minen; i++){

            int randx = rand() % 12;
            int randy = rand() % 12;

            if (f[randx * 12 + randy].b == mine) {
               i--;                           //Hier wird gecheckt ob bereits minen auf einem Feld sind, und wenn ja wird ein Schleifen durchlauf abgezogen und das programm fortgesetzt
               continue;
           } else {
               f[randx *12 + randy].b = mine;
           }

    }


    for(int i = 0; i < 12; i++) {              //Hier wird die Funktion fürs Minen zählen aufgerufen
        for(int j = 0; j < 12; j++)
        f[i * 12 +j].nachbar = getMinen(i,j);

    }
}


void Darstellung(bool debug = false){


    bool index = true;      //Der Boolean sorgt dafür das am Anfang von jeder Zeile der index Ausgegeben wird
    int counter = 0;


    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 12; j++) {

            if(debug == true && f[i * 12 + j].b != aufgedeckt){ //Hier ist der fall falls der Debug modus an ist
                if(index){

                    if(i < 9){
                        cout << 0 << i+1 <<"|";
                        index = false;
                    }else{
                        cout << i+1 <<"|";
                        index = false;
                    }
                }
                if(f[i * 12 + j].b == mine){
                    cout << "X" << " ";         //Minen werden hier als X ausgegeben
                }else{
                    cout << "*" << " ";
                }


                counter ++;
                if (counter == 12) {
                    cout << "\n";
                    counter = 0;
                    index = true;
                }
                continue;
            }

            if(f[i * 12 + j].b != aufgedeckt && !debug){   //Das ist die ausgabe falls das Feld noch nicht aufgedeckt ist, und der Debug Modus aus ist


                if(index){

                    if(i < 9){                      //Hier wird damit es ein einheitliches Feld ist die Zahlen die kleiner als 10 sind mit einer 0 davor ausgegeben
                        cout << 0 << i+1 <<"|";
                        index = false;
                    }else{
                        cout << i+1 <<"|";          //Hier wird der Index dann normal ausgegeben
                        index = false;
                    }
                }

                cout << "*" << " ";

                counter ++;
                if (counter == 12) {
                    cout << "\n";
                    counter = 0;                    //Hier wird nach 12 Feldern das Spielfeld eingerückt
                    index = true;
                }
                continue;
            }else if(f[i * 12 + j].b == aufgedeckt && f[i * 12 + j].nachbar > 0){ //Hier ist der fall falls es aufgedeckt ist, und Minen als nachbarn hat

                if(index){

                    if(i < 9){
                        cout << 0 << i+1 <<"|";
                        index = false;
                    }else{
                        cout << i+1 <<"|";
                        index = false;
                    }
                }
                cout << f[i *12 +j].nachbar << " ";     //Hier wird die Anzahl der nachbarn anstatt eines zeichens ausgegeben
                counter ++;
                if (counter == 12) {
                    cout << "\n";
                    counter = 0;
                    index = true;
                }
                continue;
            }else (f[i *12 +j].b == aufgedeckt && f[i *12 +j].nachbar == 0);{ //Und hier der Fall falls es Aufgedeckt ist und keine Minen als Nachbarn hat

                if(index){

                    if(i < 9){
                        cout << 0 << i+1 <<"|";
                        index = false;
                    }else{
                        cout << i+1 <<"|";
                        index = false;
                    }
                }

                cout << "." << " ";
                counter ++;
                if (counter == 12) {
                    cout << "\n";
                    counter = 0;
                    index = true;
                }
                continue;
            }


        }
    }
        cout <<"   "<<"________________________"<<"\n";         //Hier ist der Index für die X-Achse, diesen hab ich Leider nicht von der Spielfeldgröße abhängig hinbekommen
        cout <<"   "<<"1 2 3 4 5 6 7 8 9 101112" << "\n";

}



bool Spielzug(){

    int xkoord;
    int ykoord;

cout << "Welches Feld moechtst du aufdecken? Erst x dann y Koordinate eingeben"<<"\n";

    cin >> xkoord;
    cin >> ykoord;

    if(xkoord < 1 || xkoord > 12||ykoord < 1||ykoord > 12){     //Hier wird auf Fehleingaben überprüft

        cout <<"Fehler, ungueltige eingabe"<<"\n";
        return false;

    }


    xkoord = xkoord -1;
    ykoord = ykoord -1;    //Hier werden die beiden eingegebenen werte um eins reduziert, da bei der dartellung im index zwar eine 1 steht, es aber in wahrheit das feld 0 ist

    if(f[ykoord * 12 +xkoord].b == mine){

        Darstellung(true);                  //Hier ist der Fall falls man eine Mine trifft, dabei wird das Spielfeld nochmal im Debug modus ausgegeben damit man alle Minen sieht
        cout << "Du hast eine Mine getroffen, Game Over!" << "\n";

        return false;
    }else if(f[ykoord * 12 +xkoord].b == aufgedeckt){
                                                                        //Hier ist der Fall, falls man ein bereits aufgedecktes Feld nochmal öffnen möchte
        cout << "Fehler, dieses Feld ist bereits aufgedeckt" << "\n";
        return false;

    }else{
        f[ykoord * 12 +xkoord].b = aufgedeckt;          //Falls alles gut ging wird nun das feld aufgedeckt

    }

return true;

}

void verbleibendeFeder(){
    int counter = 0;


    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 12; j++) {          //Das ist die Funktion für die verbleibenden Felder

            if (f[i * 12 + j].b == offen) {

                counter++;

            }

        }
    }

    cout << "Verbleibende Felder:" << " " << counter << "\n";
    Darstellung(true);

    if (counter == 0) {
        cout << "Du hast gewonnen!" << "\n";

    }
}


bool Harmlos() {

    for (int y = 0; y < 12; y++) {
        for (int i = 0; i < 12; i++) {
            for (int j = 0; j < 12; j++) {

                if (f[i * 12 + j].nachbar == 0 && f[i * 12 + j].b == aufgedeckt) {

                    if (i == 0 && j == 0) {               //Ein Fall für die Ecke oben links

                        if(f[i * 12 + (j + 1)].b != aufgedeckt){
                            f[i * 12 + (j + 1)].b = aufgedeckt;
                        }
                        if(f[(i + 1) * 12 + j].b != aufgedeckt){
                            f[(i + 1) * 12 + j].b = aufgedeckt;
                        }
                        if(f[(i + 1) * 12 + (j + 1)].b != aufgedeckt){
                            f[(i + 1) * 12 + (j + 1)].b = aufgedeckt;
                        }
                        continue;

                    } else if (i == 0 && j == 11) {              //Oben rechts

                        if(f[i * 12 + (j - 1)].b != aufgedeckt){
                            f[i * 12 + (j - 1)].b = aufgedeckt;
                        }
                        if(f[(i + 1) * 12 + (j - 1)].b != aufgedeckt){
                            f[(i + 1) * 12 + (j - 1)].b = aufgedeckt;
                        }
                        if(f[(i + 1) * 12 + j].b != aufgedeckt){
                            f[(i + 1) * 12 + j].b = aufgedeckt;
                        }
                        continue;

                    } else if (i == 11 && j == 0) {            //Unten links

                        if(f[(i - 1) * 12 + j].b != aufgedeckt){
                            f[(i - 1) * 12 + j].b = aufgedeckt;
                        }
                        if(f[(i - 1) * 12 + (j + 1)].b != aufgedeckt){
                            f[(i - 1) * 12 + (j + 1)].b = aufgedeckt;
                        }
                        if(f[i * 12 + (j + 1)].b != aufgedeckt){
                            f[i * 12 + (j + 1)].b = aufgedeckt;
                        }
                        continue;

                    } else if (i == 11 && j == 11) {           //Unten rechts

                        if(f[i * 12 + (j - 1)].b != aufgedeckt){
                            f[i * 12 + (j - 1)].b = aufgedeckt;
                        }
                        if(f[(i - 1) * 12 + (j - 1)].b != aufgedeckt){
                            f[(i - 1) * 12 + (j - 1)].b = aufgedeckt;
                        }
                        if(f[(i - 1) * 12 + j].b != aufgedeckt){
                            f[(i - 1) * 12 + j].b = aufgedeckt;
                        }
                        continue;

                    } else if (i > 0 && i < 11 && j == 0) {     //Linke Reihe

                        if(f[(i - 1) * 12 + j].b != aufgedeckt){
                            f[(i - 1) * 12 + j].b = aufgedeckt;
                        }
                        if(f[(i + 1) * 12 + j].b != aufgedeckt){
                            f[(i + 1) * 12 + j].b = aufgedeckt;
                        }
                        if(f[(i - 1) * 12 + (j + 1)].b != aufgedeckt){
                            f[(i - 1) * 12 + (j + 1)].b = aufgedeckt;
                        }
                        if(f[(i + 1) * 12 + (j + 1)].b != aufgedeckt){
                            f[(i + 1) * 12 + (j + 1)].b = aufgedeckt;
                        }
                        if(f[i * 12 + (j + 1)].b != aufgedeckt){
                            f[i * 12 + (j + 1)].b = aufgedeckt;
                        }
                        continue;

                    } else if (i > 0 && i < 11 && j == 11) {  //Rechte Reihe

                        if(f[(i - 1) * 12 + j].b != aufgedeckt){
                            f[(i - 1) * 12 + j].b = aufgedeckt;
                        }
                        if(f[(i - 1) * 12 + (j - 1)].b != aufgedeckt){
                            f[(i - 1) * 12 + (j - 1)].b = aufgedeckt;
                        }
                        if(f[i * 12 + (j - 1)].b != aufgedeckt){
                            f[i * 12 + (j - 1)].b = aufgedeckt;
                        }
                        if(f[(i + 1) * 12 + j].b != aufgedeckt){
                            f[(i + 1) * 12 + j].b = aufgedeckt;
                        }
                        if(f[(i + 1) * 12 + (j - 1)].b != aufgedeckt){
                            f[(i + 1) * 12 + (j - 1)].b = aufgedeckt;
                        }
                        continue;
                    } else if (i == 0 && j > 0 && j < 11) {  //Obere Reihe

                        if(f[i * 12 + (j - 1)].b != aufgedeckt){
                            f[i * 12 + (j - 1)].b = aufgedeckt;
                        }
                        if(f[i * 12 + (j + 1)].b != aufgedeckt){
                            f[i * 12 + (j + 1)].b = aufgedeckt;
                        }
                        if(f[(i + 1) * 12 + j].b != aufgedeckt){
                            f[(i + 1) * 12 + j].b = aufgedeckt;
                        }
                        if(f[(i + 1) * 12 + (j - 1)].b != aufgedeckt){
                            f[(i + 1) * 12 + (j - 1)].b = aufgedeckt;
                        }
                        if(f[(i + 1) * 12 + (j + 1)].b != aufgedeckt){
                            f[(i + 1) * 12 + (j + 1)].b = aufgedeckt;
                        }
                        continue;
                    } else if (i == 11 && j > 0 && j < 11) { //Untere Reihe

                        if(f[(i - 1) * 12 + j].b != aufgedeckt){
                            f[(i - 1) * 12 + j].b = aufgedeckt;
                        }
                        if(f[(i - 1) * 12 + (j - 1)].b != aufgedeckt){
                            f[(i - 1) * 12 + (j - 1)].b = aufgedeckt;
                        }
                        if(f[(i - 1) * 12 + (j + 1)].b != aufgedeckt){
                            f[(i - 1) * 12 + (j + 1)].b = aufgedeckt;
                        }
                        if(f[i * 12 + (j - 1)].b != aufgedeckt){
                            f[i * 12 + (j - 1)].b = aufgedeckt;
                        }
                        if(f[i * 12 + (j + 1)].b != aufgedeckt){
                            f[i * 12 + (j + 1)].b = aufgedeckt;
                        }
                        continue;
                    } else {
                        if(f[i * 12 + (j - 1)].b != aufgedeckt){
                            f[i * 12 + (j - 1)].b = aufgedeckt;
                        }
                        if(f[i * 12 + (j + 1)].b != aufgedeckt){
                            f[i * 12 + (j + 1)].b = aufgedeckt;
                        }
                        if(f[(i - 1) * 12 + j].b != aufgedeckt){
                            f[(i - 1) * 12 + j].b = aufgedeckt;
                        }
                        if(f[(i - 1) * 12 + (j + 1)].b != aufgedeckt){
                            f[(i - 1) * 12 + (j + 1)].b = aufgedeckt;
                        }
                        if(f[(i - 1) * 12 + (j - 1)].b != aufgedeckt){
                            f[(i - 1) * 12 + (j - 1)].b = aufgedeckt;
                        }
                        if(f[(i + 1) * 12 + j].b != aufgedeckt){
                            f[(i + 1) * 12 + j].b = aufgedeckt;
                        }
                        if(f[(i + 1) * 12 + (j - 1)].b != aufgedeckt){
                            f[(i + 1) * 12 + (j - 1)].b = aufgedeckt;
                        }
                        if(f[(i + 1) * 12 + (j + 1)].b != aufgedeckt){
                            f[(i + 1) * 12 + (j + 1)].b = aufgedeckt;
                        }
                    }

/*

                f[i*12+(j-1)].b = aufgedeckt;
                f[i*12+(j+1)].b = aufgedeckt;
                f[(i-1)*12+j].b = aufgedeckt;
                f[(i-1)*12+(j+1)].b = aufgedeckt;
                f[(i-1)*12+(j-1)].b = aufgedeckt;
                f[(i+1)*12+j].b = aufgedeckt;
                f[(i+1)*12+(j-1)].b = aufgedeckt;
                f[(i+1)*12+(j+1)].b = aufgedeckt;
*/

                }

            }
        }

    }

    return true;
}






#endif //PRAKTIKUM4_MINESWEEPER_H



