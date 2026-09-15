#include "gestormedallas.h"
#include <fstream>
using namespace std;
GestorMedallas::GestorMedallas(const string &rutaArchivo)
    :rutaArchivo(rutaArchivo),registros(nullptr),cantidadRegistros(0)
{}
GestorMedallas::~GestorMedallas(){
    liberarRegistros();
}
void GestorMedallas::liberarRegistros(){
    delete[] registros;
    registros=nullptr;
    cantidadRegistros=0;
}
void GestorMedallas::cargarMedallas(){
    liberarRegistros();
    ifstream archivo(rutaArchivo);
    if(!archivo.is_open()){
        return;
    }
    string usuarioTemp,medallaTemp;
    int cantidadLeida=0;
    while(archivo>>usuarioTemp>>medallaTemp){
        cantidadLeida++;
    }
    if(cantidadLeida==0){
        return;
    }
    registros=new RegistroMedalla[cantidadLeida];
    archivo.clear();
    archivo.seekg(0);
    int i=0;
    while(archivo>>usuarioTemp>>medallaTemp && i<cantidadLeida){
        registros[i].usuario=usuarioTemp;
        registros[i].tipoMedalla=medallaTemp;
        i++;
    }
    cantidadRegistros=cantidadLeida;
}
bool GestorMedallas::tieneMedalla(const string &usuario,const string &tipoMedalla){
    cargarMedallas();
    for(int i=0;i<cantidadRegistros;i++){
        if(registros[i].usuario==usuario && registros[i].tipoMedalla==tipoMedalla){
            return true;
        }
    }
    return false;
}
bool GestorMedallas::cumplePrerequisito(const string &usuario,const string &tipoMedalla){
    if(tipoMedalla=="Bronce"){
        return true;
    }
    if(tipoMedalla=="Plata"){
        return tieneMedalla(usuario,"Bronce");
    }
    if(tipoMedalla=="Oro"){
        return tieneMedalla(usuario,"Plata");
    }
    if(tipoMedalla=="Diamante"){
        return tieneMedalla(usuario,"Oro");
    }
    return true;
}
bool GestorMedallas::otorgarMedalla(const string &usuario,const string &tipoMedalla){
    if(tieneMedalla(usuario,tipoMedalla)){
        return true; //esto evita medallas duplicadas
    }
    if(!cumplePrerequisito(usuario,tipoMedalla)){
        return false; //no ha desbloqueado la medalla anterior
    }
    ofstream archivo(rutaArchivo,ios::app);
    if(archivo.is_open()){
        archivo<<usuario<<" "<<tipoMedalla<<"\n";
        archivo.close();
        return true;
    }
    return false;
}