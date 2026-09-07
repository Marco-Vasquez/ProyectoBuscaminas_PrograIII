#include "cronometro.h"

Cronometro::Cronometro(QObject *parent):QObject(parent),segundos(0) {
    connect(&temporizador,&QTimer::timeout,this,&Cronometro::avanzarUnSegundo);
    temporizador.setInterval(1000);
}
void Cronometro::iniciar(){
    temporizador.start();
}
void Cronometro::detener(){
    temporizador.stop();
}
void Cronometro::reiniciar(){
    segundos=0;
    emit tiempoActualizado(segundos);
}
int Cronometro::getSegundosTranscurridos() const{
    return segundos;
}
void Cronometro::avanzarUnSegundo(){
    segundos++;
    emit tiempoActualizado(segundos);
}
