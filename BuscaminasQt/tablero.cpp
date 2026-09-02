#include "tablero.h"
#include <random>
using namespace std;
Tablero::Tablero(int filas,int columnas,int cantMinas)
    :filas(filas),columnas(columnas),cantMinas(cantMinas),minasSembradas(false),perdio(false)
{
    matriz=new Celda* [filas];
    for(int i=0;i<filas;i++){
        matriz[i]=new Celda[columnas];
    }
}
Tablero::~Tablero(){
    for(int i=0;i<filas;i++){
        delete[] matriz[i];
    }
    delete[] matriz;
    matriz=nullptr;
}
bool Tablero::estaDentroDelTablero(int fila,int columna) const{
    return fila>=0 && fila<filas && columna>=0 && columna<columnas;
}
Celda& Tablero::obtenerCelda(int fila,int columna) const{
    return matriz[fila][columna];
}
void Tablero::sembrarMinas(int filaSegura,int columnaSegura){
    random_device semilla;
    mt19937 generador(semilla());
    uniform_int_distribution<int> distribucionFilas(0,filas-1);
    uniform_int_distribution<int> distribucionColumnas(0,columnas-1);
    int minasColocadas=0;
    while(minasColocadas<cantMinas){
        int filaCandidata=distribucionFilas(generador);
        int columnaCandidata=distribucionColumnas(generador);
        bool esLaCeldaSegura=(filaCandidata==filaSegura && columnaCandidata==columnaSegura);
        bool yaTieneMina=matriz[filaCandidata][columnaCandidata].tieneMina();
        if(!esLaCeldaSegura && !yaTieneMina){
            matriz[filaCandidata][columnaCandidata].ponerMina();
            minasColocadas++;
        }
    }
    minasSembradas=true;
}
int Tablero::contarMinasAlrededor(int fila,int columna) const{
    int contador=0;
    for(int deltaFila=-1;deltaFila<=1;deltaFila++){
        for(int deltaColumna=-1;deltaColumna<=1;deltaColumna++){
            if(deltaFila==0 && deltaColumna==0){
                continue;
            }
            int filaVecina,colVecina;
            filaVecina=fila+deltaFila;
            colVecina=columna+deltaColumna;
            if(estaDentroDelTablero(filaVecina,colVecina)){
                matriz[filaVecina][colVecina].tieneMina();
                contador++;
            }
        }
    }
    return contador;
}
void Tablero::calcularMinasVecinas(){
    for(int fila=0;fila<filas;fila++){
        for(int columna=0;columna<columnas;columna++){
            int cantidad=contarMinasAlrededor(fila,columna);
            matriz[fila][columna].setMinasVecinas(cantidad);
        }
    }
}
void Tablero::abrirCelda(int fila,int columna){
    if(!estaDentroDelTablero(fila,columna)){
        return;
    }
    if(!minasSembradas){
        sembrarMinas(fila,columna);
        calcularMinasVecinas();
    }
    Celda &celda=matriz[fila][columna];
    if(celda.estaRevelada() || celda.tieneBandera()){
        return;
    }
    celda.revelar();
    if(celda.tieneMina()){
        perdio=true;
        return;
    }
    if(celda.getMinasVecinas()!=0){
        return;
    }
    for(int deltaFila=-1;deltaFila<=1;deltaFila++){
        for(int deltaCol=-1;deltaCol<=1;deltaCol++){
            if(deltaFila==0 && deltaCol==0){
                continue;
            }
            abrirCelda(fila+deltaFila,columna+deltaCol);
        }
    }
}
void Tablero::alternarBandera(int fila,int columna){
    if(!estaDentroDelTablero(fila,columna)){
        return;
    }
    matriz[fila][columna].alternarBandera();
}
int Tablero::getColumnas() const{
    return columnas;
}
int Tablero::getFilas() const{
    return filas;
}
int Tablero::getCantidadMinas() const{
    return cantMinas;
}
bool Tablero::juegoPerdido() const{
    return perdio;
}
bool Tablero::juegoGanado() const{
    if(perdio){
        return false;
    }
    for(int fila=0;fila<filas;fila++){
        for(int columna=0;columna<columnas;columna++){
            const Celda &celda=matriz[fila][columna];
            if(!celda.tieneMina() && !celda.estaRevelada()){
                return false;
            }
        }
    }
    return true;
}
