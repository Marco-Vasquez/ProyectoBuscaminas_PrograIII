#include "gestorpuntajes.h"
#include <fstream>
GestorPuntajes::GestorPuntajes(const string &rutaArchivo):registros(nullptr),cantidadRegistros(0) {
}
GestorPuntajes::~GestorPuntajes(){
    liberarRegistros();
}
void GestorPuntajes::liberarRegistros(){
    delete[] registros;
    registros=nullptr;
    cantidadRegistros=0;
}
void GestorPuntajes::guardarPuntaje(const string &nombreJugador,int segundos,const string &dificultad){
    ofstream archivo(rutaArchivo,ios::app);
    if(archivo.is_open()){
        archivo<<nombreJugador<<" "<<segundos<<" "<<dificultad<<"\n";
        archivo.close();
    }
}
void GestorPuntajes::cargarPuntajes(){
    liberarRegistros();
    ifstream archivo(rutaArchivo);
    if(!archivo.is_open()){
        return;
    }
    string nombreTemp,dificultadTemp;
    int segundosTemp,cantidadLeida=0;
    while(archivo>>nombreTemp>>segundosTemp>>dificultadTemp){
        cantidadLeida++;
    }
    if(cantidadLeida==0){
        return;
    }
    registros=new RegistroPuntaje[cantidadLeida];
    archivo.clear();
    archivo.seekg(0);
    int i=0;
    while(archivo>>nombreTemp>>segundosTemp>>dificultadTemp && i<cantidadLeida){
        registros[i].nombreJugador=nombreTemp;
        registros[i].segundos=segundosTemp;
        registros[i].dificultad=dificultadTemp;
        i++;
    }
    cantidadRegistros=cantidadLeida;
}
int GestorPuntajes::getCantidadRegistros() const{
    return cantidadRegistros;
}
const RegistroPuntaje &GestorPuntajes::obtenerRegistro(int indice) const{
    return registros[indice];
}
