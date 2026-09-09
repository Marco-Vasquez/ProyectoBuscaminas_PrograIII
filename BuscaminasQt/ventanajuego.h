#ifndef VENTANAJUEGO_H
#define VENTANAJUEGO_H
#include <QWidget>
#include <QString>
#include "cronometro.h"
class Tablero;
class QGraphicsScene;
class QLabel;
class VistaJuego;
class celdagrafica;
// Ventana de juego (página dentro del QStackedWidget del main)
class VentanaJuego : public QWidget
{
    Q_OBJECT
public:
    explicit VentanaJuego(int filas, int columnas, int cantidadMinas, QWidget *parent = nullptr);
    ~VentanaJuego() override;

    void setNombreJugador(const QString &nombre);
signals:
    void volverSolicitado();
private slots:
    void manejarClicIzquierdo(int fila, int columna);
    void manejarClicDerecho(int fila, int columna);
    void actualizarTiempo(int segundos);
private:
    static const int ANCHO_AREA_TABLERO = 640;
    static const int ALTO_AREA_TABLERO = 420;

    Tablero *tablero;
    QGraphicsScene *escena;
    VistaJuego *vista;
    QLabel *etiquetaEstado;
    QLabel *etiquetaTiempo;
    celdagrafica **celdasGraficas;
    Cronometro cronometro;
    QString nombreJugador;
    int tamanioCelda;
    bool partidaTerminada;

    void construirCeldasGraficas();
    void dibujarTablero();
    void finalizarPartida(bool gano);
};
#endif // VENTANAJUEGO_H