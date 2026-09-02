#ifndef TABLERO_H
#define TABLERO_H
#include "celda.h"
class Tablero
{
public:
    Tablero(int filas,int columnas,int cantMinas);
    ~Tablero();
    void abrirCelda(int fila,int columna);
    void alternarBandera(int fila,int columna);
    bool estaDentroDelTablero(int fila,int columna) const;
    Celda& obtenerCelda(int fila,int columna) const;
    int getFilas() const;
    int getColumnas() const;
    int getCantidadMinas() const;
    bool juegoPerdido() const;
    bool juegoGanado() const;
private:
    Celda** matriz;
    int filas,columnas,cantMinas;
    bool minasSembradas,perdio;
    void sembrarMinas(int filaSegura,int columnaSegura);
    void calcularMinasVecinas();
    int contarMinasAlrededor(int fila,int columna) const;
};

#endif // TABLERO_H
