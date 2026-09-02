#include "celda.h"

Celda::Celda()
    : mina(false),revelada(false),bandera(false),minasVecinas(0)
{}
void Celda::ponerMina(){
    mina=true;
}
bool Celda::tieneMina() const{
    return mina;
}
void Celda::revelar(){
    revelada=true;
}
bool Celda::estaRevelada() const{
    return revelada;
}
void Celda::alternarBandera(){
    if(!revelada){
        bandera=!bandera;
    }
}
bool Celda::tieneBandera() const{
    return bandera;
}
void Celda::setMinasVecinas(int cant){
    minasVecinas=cant;
}
int Celda::getMinasVecinas() const{
    return minasVecinas;
}