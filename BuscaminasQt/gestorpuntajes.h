#ifndef GESTORPUNTAJES_H
#define GESTORPUNTAJES_H
#include <string>
using namespace std;
struct RegistroPuntaje{
    string nombreJugador;
    int segundos;
    string dificultad;
};

class GestorPuntajes
{
public:
    explicit GestorPuntajes(const string &rutaArchivo="puntajes.txt");
    ~GestorPuntajes();
    void guardarPuntaje(const string &nombreJugador,int segundos,const string &dificultad);
    void cargarPuntajes();
    int getCantidadRegistros() const;
    const RegistroPuntaje &obtenerRegistro(int indice) const;
private:
    string rutaArchivo;
    RegistroPuntaje* registros;
    int cantidadRegistros;
    void liberarRegistros();
};

#endif // GESTORPUNTAJES_H
