//
// Created by mauro on 3/05/16.
//

#include "Joc.h"
#include <iostream>

using namespace std;
//Pre:Baralla a repartir no pot esser buida.
//Post: Inici del joc, es crean totes les piles la ma i el tauler inicial, es reparteixen les cartes de manera que quedin com en el joc del solitari
// i les cartes restants s'afageixen a la ma.
Joc::Joc(Baralla b) {
    ma = pilaCartes();
    descartades = pilaCartes();
    coll1 = pilaCartes();
    coll2 = pilaCartes();
    coll3 = pilaCartes();
    coll4 = pilaCartes();

    int fila = 0;
    int cont2 = 0;
    int i = 0;
    for(i;i<tauler.getFiles();i++){
        Carta nova = b.agafaCarta();
        if(i==cont2){
            nova.setVisible();
        }
        tauler.afageixCarta(nova, i, fila);
        if(i == tauler.getFiles()-1){
            fila++;
            i = cont2++;
        }
    }

    int cartesSobrants = b.getMida();
    for(int i=0;i<=cartesSobrants;i++){
        Carta sobrant = b.repartirSobrants(i);
        ma.empila(sobrant);
    }



}
//Pre:--;
//Post: Es mostra el joc, amb les piles de colls el tauler la ma i la pila de descartades, de manera que les columnes siguin estatiques, i que les
// files hagin de decreixer o creixer segons el numero maxim de cartes d'una fila.
void Joc::mostrar() const{

    cout << "ESTAT DEL JOC" << endl;
    coll1.cim().mostrar();
    coll2.cim().mostrar();
    coll3.cim().mostrar();
    coll4.cim().mostrar();
    cout << "   ";
    ma.cim().mostrar();
    descartades.cim().mostrar();
    cout << endl;
    int gran = tauler.getColumna(0);
    for(int i=1;i<=tauler.getFiles();i++){
        cout << "c" << i << " ";
        if(gran < tauler.getColumna(i)){
            gran = tauler.getColumna(i);
        }
    }
    cout << endl;
    int files = 7, cont = 0, i=0;
    while(cont < gran){
        for(i;i<files;i++){
            Carta agafada = tauler.getCarta(i,cont);
            agafada.mostrar();
        }
        cout << "f" <<cont+1 <<  endl;
        i = 0;
        cont++;
    }
}
//Pre:--;
//Post: Metode que si la ma es buida vol dir que ja hem mirat totes les cartes, es fa una copia de la pila de descartades cap a la ma.
// en canvi si la ma no es buida llavors s'agafa una carta de la ma i es posa a la pila de descartades.
void Joc::obreCarta() {
    if(ma.esBuida()){
        reciclar();
    }else {
        Carta agafada = ma.desempila();
        agafada.setVisible();
        descartades.empila(agafada);
    }

}
void Joc::reciclar() {
    while(!descartades.esBuida()){
        Carta desempilada = descartades.desempila();
        desempilada.setAmagada();
        ma.empila(desempilada);
    }
}
bool Joc::descartadesBuida() const {
    return descartades.esBuida();
}
void Joc::posarAlTauler(int colum) {
    if(colum != -1){
        int ultimaFila = tauler.getColumna(colum-1);
        Carta agafada = descartades.desempila();
        Carta anterior = tauler.getCarta(colum-1, ultimaFila-1);
        if(agafada.casen(anterior)){
            tauler.afageixCarta(agafada, colum-1, ultimaFila);
        }else{
            cout << "LA CARTA NO ES POT POSAR A LA COLUMNA " << colum << endl;
            descartades.empila(agafada);
        }
    }

}
//Pre:--;
//Post: Metode que insereix a la pila de colls la carta agafada de la pila de descartades, comprova el seu pal i automaticament la insereix a la pila pertinent.
void Joc::posarAlaPila() {

    Carta agafada = descartades.cim();

    if(agafada.getPal() == 'c'){
        if(coll2.esBuida() and agafada.getValor() == 'A'){
            coll2.empila(descartades.desempila());
        }else {
            if(agafada.esMesPetita(coll2.cim())){
                coll2.empila(descartades.desempila());
            }else{
                mostraError();
            }
        }
    }
    if(agafada.getPal() == 'P'){
        if(coll1.esBuida() and agafada.getValor() == 'A'){
            coll1.empila(descartades.desempila());
        }else{
            if(agafada.esMesPetita(coll1.cim())){
                coll1.empila(descartades.desempila());
            }else{
                mostraError();
            }
        }
    }
    if(agafada.getPal() == 'd'){
        if(coll3.esBuida() and agafada.getValor() == 'A'){
            coll3.empila(descartades.desempila());
        }else {
            if(agafada.esMesPetita(coll3.cim())){
                coll3.empila(descartades.desempila());
            }else{
                mostraError();
            }
        }
    }
    if(agafada.getPal() == 'T'){
        if(coll4.esBuida() and agafada.getValor() == 'A'){
            coll4.empila(descartades.desempila());
        }else {
            if(agafada.esMesPetita(coll4.cim())){
                coll4.empila(descartades.desempila());
            }else{
                mostraError();
            }
        }
    }
}
void Joc::mostraError() {
    cout << "NO ES POT APILAR LA CARTA" << endl;
}
//Pre: Columna i fila entrades per l'usuari siguin les correctes.
//Post: Retorna true si la columna o fila son valides i en el tauler l'ultima carta es visible.
bool Joc::comprovaSituacio(int colum, int fila) const{
    if((colum < 1 or colum > 7) or (fila < 1 or fila > tauler.getColumna(colum-1)) or (!tauler.getCarta(colum-1, fila-1).getVisible())){
        return false;
    }else{
        return true;
    }
}
void Joc::mouCarta(int colum, int fila, int desti) {
    colum = colum -1;
    fila = fila -1;
    desti = desti -1;
    Carta cartaMoure = tauler.getCarta(colum, fila);
    Carta ultimaVisible = tauler.getUltimaCartaVisible(desti);
    if(cartaMoure.casen(ultimaVisible)){
        int max = tauler.getColumna(colum);
        for(int i=0;i<max;i++){
            if(tauler.getCarta(colum, i).getVisible() and tauler.getCarta(colum, i).casen(ultimaVisible)){
                Carta extreta = tauler.extreuCarta(colum, i);
                tauler.afageixCartaFinal(extreta, desti);
                ultimaVisible = extreta;
            }
        }
        girarUltima(colum);

    }else{
        cout << "LA CARTA NO ES POT POSAR A LA COLUMNA " << desti+1 << endl;
    }
}
void Joc::mouCartaPila(int desti) {
    int aux = desti -1, cont = 0;
    if(!(aux < 0 or aux > 6) or tauler.getColumna(aux) != 0){
        Carta darrera = tauler.getUltimaCartaVisible(aux);
        if(primeraInsercio(darrera, aux, cont)){
            girarUltima(aux);
        }else{
            if(darrera.getPal() == 'P' and darrera.esMesPetita(coll1.cim())){
                coll1.empila(darrera);
                tauler.extreuDarrera(aux);
                girarUltima(aux);
                cont++;
            }
            if(darrera.getPal() == 'c' and darrera.esMesPetita(coll2.cim())){
                coll2.empila(darrera);
                tauler.extreuDarrera(aux);
                girarUltima(aux);
                cont++;
            }
            if(darrera.getPal() == 'd' and darrera.esMesPetita(coll3.cim())){
                coll3.empila(darrera);
                tauler.extreuDarrera(aux);
                girarUltima(aux);
                cont++;
            }
            if(darrera.getPal() == 'T' and darrera.esMesPetita(coll4.cim())){
                coll4.empila(darrera);
                tauler.extreuDarrera(aux);
                girarUltima(aux);
                cont++;
            }
            if(cont == 0){
                mostrarErrorPila();
            }

        }
        }else{
        mostrarErrorPila();
    }
}
bool Joc::primeraInsercio(Carta darrera, int desti, int &cont) {
    bool final = false;
    if(darrera.getValor() == 'A' and coll1.esBuida() and darrera.getPal() == 'P'){
        coll1.empila(darrera);
        tauler.extreuDarrera(desti);
        final = true;
        cont++;
    }
    if(darrera.getValor() == 'A' and coll2.esBuida() and darrera.getPal() == 'c'){
        coll2.empila(darrera);
        tauler.extreuDarrera(desti);
        final = true;
        cont++;
    }
    if(darrera.getValor() == 'A' and coll3.esBuida() and darrera.getPal() == 'd'){
        coll3.empila(darrera);
        tauler.extreuDarrera(desti);
        final = true;
        cont++;
    }
    if(darrera.getValor() == 'A' and coll4.esBuida() and darrera.getPal() == 'T'){
        coll4.empila(darrera);
        tauler.extreuDarrera(desti);
        final = true;
        cont++;
    }

    return final;

}
void Joc::mostrarErrorPila() {
    cout << "LA CARTA NO ES POT APILAR" << endl;
}
void Joc::girarUltima(int desti) {

    Carta ultima = tauler.getUltimaCartaVisible(desti);
    if(!ultima.getVisible()){
        ultima.setVisible();
        tauler.substitueix(ultima, desti);
    }
}
bool Joc::esPotRecuperar(int pila) const{
    bool final = false;
    if(pila > 0 or pila < 5){
        if(((pila == 1) and !coll1.esBuida()) or (pila == 2 and !coll2.esBuida()) or (pila == 3 and !coll3.esBuida()) or (pila == 4 and !coll4.esBuida())){
            final = true;
        }
    }
    return final;
}
void Joc::recuperaCarta(int pila, int columna) {

    int aux = columna -1;
    Carta ultima = tauler.getUltimaCartaVisible(columna-1);
    if(pila == 1){
        if(coll1.cim().casen(ultima)){
            tauler.afageixCartaFinal(coll1.desempila(), aux);
        }else{
            cout << "LA CARTA NO ES POT POSAR A LA COLUMNA " << columna << endl;
        }
    }if(pila == 2){
        if(coll2.cim().casen(ultima)){
            tauler.afageixCartaFinal(coll2.desempila(), aux);
        }else{
            cout << "LA CARTA NO ES POT POSAR A LA COLUMNA " << columna << endl;
        }
    }
    if(pila == 3){
        if(coll3.cim().casen(ultima)){
            tauler.afageixCartaFinal(coll3.desempila(), aux);
        }else{
            cout << "LA CARTA NO ES POT POSAR A LA COLUMNA " << columna << endl;
        }
    }
    if(pila == 4){
        if(coll4.cim().casen(ultima)){
            tauler.afageixCartaFinal(coll4.desempila(), aux);
        }else{
            cout << "LA CARTA NO ES POT POSAR A LA COLUMNA " << columna << endl;
        }
    }
}
bool Joc::haAcabat() const {
    return coll1.cim().getValor() == 'K' and coll2.cim().getValor() == 'K' and coll3.cim().getValor() == 'K' and coll4.cim().getValor() == 'K';
}