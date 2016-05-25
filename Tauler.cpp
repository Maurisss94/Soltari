//
// Created by mauro on 3/05/16.
//

#include "Tauler.h"
#include <iostream>

using namespace std;
Tauler::Tauler(){
    a_mat = NULL;
    a_nf = 7;
    a_ncMax = NULL;
    a_mida = NULL;
    inicialitza();

}
void Tauler::allibera() {
    // alliberament de cadascuna de les files
    for(int i=0; i<a_nf; i++)
        delete [] a_mat[i];

// alliberament del vector de punters
    delete [] a_mat;
    delete [] a_mida;
}
void Tauler::reserva() {
    a_mat = new Carta*[a_nf*a_nf];

}
void Tauler::inicialitza() {

    a_mat= new Carta*[7];
    a_mida= new int[7];
    a_ncMax = new int[13];
    reserva();

    for(int i=0; i<7; i++){
        a_mat[i]= new Carta[13+i];
        a_mida[i]= i+1;
        a_ncMax[i] = 13 + i;
    }

}
int Tauler::getColumna(int pos) const{
    return a_mida[pos];
}
int Tauler::getFiles() const {
    return a_nf;
}
void Tauler::afageixCarta(Carta nova, int i, int j) {
    a_mat[i][j] = nova;
}
Carta Tauler::getCarta(int i, int j) const {
    return a_mat[i][j];
}