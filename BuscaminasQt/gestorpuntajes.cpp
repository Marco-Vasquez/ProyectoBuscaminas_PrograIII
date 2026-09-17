#include "gestorpuntajes.h"
#include <fstream>
#include <QCoreApplication>
#include <QDir>
GestorPuntajes::GestorPuntajes(const std::string &rutaArchivo)
{
    QString ruta = QDir(QCoreApplication::applicationDirPath()).filePath(QString::fromStdString(rutaArchivo));
    this->rutaArchivo = ruta.toStdString();
    registros = nullptr;
    cantidadRegistros = 0;
}
GestorPuntajes::~GestorPuntajes(){
    liberarRegistros();
}
void GestorPuntajes::liberarRegistros(){
    delete[] registros;
    registros=nullptr;
    cantidadRegistros=0;
}
void GestorPuntajes::guardarPuntaje(const string &nombreJugador,int segundos,const string &dificultad,const string &medalla){
    ofstream archivo(rutaArchivo,ios::app);
    if(archivo.is_open()){
        archivo<<nombreJugador<<" "<<segundos<<" "<<dificultad<<" "<<medalla<<"\n";
        archivo.close();
    }
}
void GestorPuntajes::cargarPuntajes(){
    liberarRegistros();
    ifstream archivo(rutaArchivo);
    if(!archivo.is_open()){
        return;
    }
    string nombreTemp,dificultadTemp,medallaTemp;
    int segundosTemp,cantidadLeida=0;
    // se leen 4 valores por línea; si una línea vieja solo tiene 3,
    // la medalla queda vacía y se sigue leyendo (compatibilidad hacia atrás)
    while(archivo>>nombreTemp>>segundosTemp>>dificultadTemp){
        if(!(archivo>>medallaTemp)){
            medallaTemp="";
            archivo.clear();
        }
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
        if(!(archivo>>medallaTemp)){
            medallaTemp="";
            archivo.clear();
        }
        registros[i].nombreJugador=nombreTemp;
        registros[i].segundos=segundosTemp;
        registros[i].dificultad=dificultadTemp;
        registros[i].medalla=medallaTemp;
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
