#ifndef GESTORMEDALLAS_H
#define GESTORMEDALLAS_H
#include <string>
using namespace std;
struct RegistroMedalla{
    string usuario;
    string tipoMedalla;
};

class GestorMedallas
{
public:
    explicit GestorMedallas(const string &rutaArchivo="medallas.txt");
    ~GestorMedallas();
    bool otorgarMedalla(const string &usuario,const string &tipoMedalla);
    bool tieneMedalla(const string &usuario,const string &tipoMedalla);
private:
    string rutaArchivo;
    RegistroMedalla* registros;
    int cantidadRegistros;
    void cargarMedallas();
    void liberarRegistros();
    bool cumplePrerequisito(const string &usuario,const string &tipoMedallas);
};

#endif // GESTORMEDALLAS_H
