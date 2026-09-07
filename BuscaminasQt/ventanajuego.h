#ifndef VENTANAJUEGO_H
#define VENTANAJUEGO_H

#include <QMainWindow>

class Tablero;
class QGraphicsScene;
class QLabel;
class VistaJuego;

// Ventana de juego
class VentanaJuego : public QMainWindow
{
    Q_OBJECT
public:
    explicit VentanaJuego(int filas, int columnas, int cantidadMinas, QWidget *parent = nullptr);
    ~VentanaJuego() override;

signals:
    void volverSolicitado();

private slots:
    void manejarClicIzquierdo(int fila, int columna);
    void manejarClicDerecho(int fila, int columna);

private:
    static const int TAMANIO_CELDA = 32;

    Tablero *tablero;
    QGraphicsScene *escena;
    VistaJuego *vista;
    QLabel *etiquetaEstado;
    bool partidaTerminada;

    void dibujarTablero();
    void finalizarPartida(bool gano);
};

#endif // VENTANAJUEGO_H