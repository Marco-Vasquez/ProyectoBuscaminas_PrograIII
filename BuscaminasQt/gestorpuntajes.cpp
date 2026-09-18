#include "gestorpuntajes.h"
#include <fstream>
#include <sstream>
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
void GestorPuntajes::guardarPuntaje(const string &nombreJugador,int segundos,const string &dificultad,const string &medalla,int puntaje){
    ofstream archivo(rutaArchivo,ios::app);
    if(archivo.is_open()){
        archivo<<nombreJugador<<" "<<segundos<<" "<<dificultad<<" "<<medalla<<" "<<puntaje<<"\n";
        archivo.close();
    }
}
void GestorPuntajes::cargarPuntajes(){
    liberarRegistros();
    ifstream archivo(rutaArchivo);
    if(!archivo.is_open()){
        return;
    }

    string linea;
    int cantidadValida = 0;
    while (getline(archivo, linea)) {
        istringstream flujo(linea);
        string nombreTemp, dificultadTemp, medallaTemp;
        int segundosTemp, puntajeTemp;
        if (flujo >> nombreTemp >> segundosTemp >> dificultadTemp >> medallaTemp >> puntajeTemp) {
            cantidadValida++;
        }
    }
    if (cantidadValida == 0) {
        return;
    }

    registros = new RegistroPuntaje[cantidadValida];
    archivo.clear();
    archivo.seekg(0);

    int i = 0;
    while (getline(archivo, linea) && i < cantidadValida) {
        istringstream flujo(linea);
        string nombreTemp, dificultadTemp, medallaTemp;
        int segundosTemp, puntajeTemp;
        if (flujo >> nombreTemp >> segundosTemp >> dificultadTemp >> medallaTemp >> puntajeTemp) {
            registros[i].nombreJugador = nombreTemp;
            registros[i].segundos = segundosTemp;
            registros[i].dificultad = dificultadTemp;
            registros[i].medalla = medallaTemp;
            registros[i].puntaje = puntajeTemp;
            i++;
        }
    }
    cantidadRegistros = i;
}
int GestorPuntajes::getCantidadRegistros() const{
    return cantidadRegistros;
}
const RegistroPuntaje &GestorPuntajes::obtenerRegistro(int indice) const{
    return registros[indice];
}