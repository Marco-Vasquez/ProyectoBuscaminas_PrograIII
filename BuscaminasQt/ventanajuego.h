#ifndef VENTANAJUEGO_H
#define VENTANAJUEGO_H
#include <QWidget>
#include <QString>
#include "cronometro.h"
class Tablero;
class QGraphicsScene;
class QLabel;
class QPushButton;
class VistaJuego;
class celdagrafica;
class GestorAudio;
// Ventana de juego (página dentro del QStackedWidget del main)
class VentanaJuego : public QWidget
{
    Q_OBJECT
public:
    explicit VentanaJuego(int filas, int columnas, int cantidadMinas, QWidget *parent = nullptr);
    ~VentanaJuego() override;

    void setNombreJugador(const QString &nombre);
    void setGestorAudio(GestorAudio *audio);
    int getSegundosTranscurridos() const;
    int getBanderasColocadas() const;
signals:
    void volverSolicitado();
    void victoriaObtenida(int segundos,int banderasColocadas,QString textoMedalla,bool haySiguienteNivel,int filasSiguiente,int columnasSiguiente,int minasSiguiente);
    void derrotaObtenida(int filas,int columnas,int minas);
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
    QLabel *etiquetaJugador;
    QLabel *etiquetaBanderas;
    celdagrafica **celdasGraficas;
    Cronometro cronometro;
    QString nombreJugador;
    int tamanioCelda;
    bool partidaTerminada;
    GestorAudio *gestorAudio = nullptr;
    QPushButton *botonMute = nullptr;

    void construirCeldasGraficas();
    void dibujarTablero();
    void finalizarPartida(bool gano);
    QString determinarMedalla() const;

    bool jugadaArriesgadaDetectada=false;
};
#endif // VENTANAJUEGO_H