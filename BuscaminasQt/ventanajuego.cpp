#include "ventanajuego.h"
#include "vistajuego.h"
#include "tablero.h"
#include "celda.h"
#include "celdagrafica.h"
#include "gestorpuntajes.h"

#include <QGraphicsScene>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>
#include <QFont>
#include <QSizePolicy>
#include <algorithm>

VentanaJuego::VentanaJuego(int filas, int columnas, int cantidadMinas, QWidget *parent)
    : QWidget(parent), nombreJugador("Jugador"), partidaTerminada(false)
{
    tablero = new Tablero(filas, columnas, cantidadMinas);

    // El tamaño de cada celda se calcula para que el tablero completo
    // siempre entre en la misma área disponible, sin importar si el nivel
    // es 8x8, 16x16 o 16x30.
    int celdaPorAncho = ANCHO_AREA_TABLERO / columnas;
    int celdaPorAlto = ALTO_AREA_TABLERO / filas;
    tamanioCelda = std::min(celdaPorAncho, celdaPorAlto);
    if (tamanioCelda < 10) {
        tamanioCelda = 10;
    }

    QVBoxLayout *layoutPrincipal = new QVBoxLayout(this);
    layoutPrincipal->setContentsMargins(15, 15, 15, 15);
    layoutPrincipal->setSpacing(10);

    QHBoxLayout *layoutEncabezado = new QHBoxLayout();

    etiquetaEstado = new QLabel(this);
    etiquetaTiempo = new QLabel("Tiempo: 0s", this);
    for (QLabel *etiqueta : {etiquetaEstado, etiquetaTiempo}) {
        QFont fuenteEstado = etiqueta->font();
        fuenteEstado.setPointSize(11);
        fuenteEstado.setBold(true);
        etiqueta->setFont(fuenteEstado);
    }

    layoutEncabezado->addWidget(etiquetaEstado);
    layoutEncabezado->addStretch();
    layoutEncabezado->addWidget(etiquetaTiempo);

    escena = new QGraphicsScene(this);
    vista = new VistaJuego(this);
    vista->setScene(escena);
    vista->setTamanioCelda(tamanioCelda);
    // con la ventana, y VistaJuego::resizeEvent() la reescala manteniendo
    vista->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    vista->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    vista->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QPushButton *botonVolver = new QPushButton("VOLVER AL MENU", this);
    botonVolver->setStyleSheet("background-color: #7f8c8d; color: white; border-radius: 6px; padding: 8px;");
    connect(botonVolver, &QPushButton::clicked, this, [this]() {
        cronometro.detener();
        emit volverSolicitado();
    });

    layoutPrincipal->addLayout(layoutEncabezado);
    layoutPrincipal->addWidget(vista, 1);
    layoutPrincipal->addWidget(botonVolver);

    connect(vista, &VistaJuego::celdaClicIzquierdo, this, &VentanaJuego::manejarClicIzquierdo);
    connect(vista, &VistaJuego::celdaClicDerecho, this, &VentanaJuego::manejarClicDerecho);
    connect(&cronometro, &Cronometro::tiempoActualizado, this, &VentanaJuego::actualizarTiempo);

    construirCeldasGraficas();
    dibujarTablero();

    cronometro.iniciar();
}

VentanaJuego::~VentanaJuego()
{
    delete[] celdasGraficas;
    delete tablero;
}

void VentanaJuego::setNombreJugador(const QString &nombre)
{
    nombreJugador = nombre;
}

void VentanaJuego::construirCeldasGraficas()
{
    int filas = tablero->getFilas();
    int columnas = tablero->getColumnas();

    celdasGraficas = new celdagrafica*[filas * columnas];

    for (int fila = 0; fila < filas; fila++) {
        for (int columna = 0; columna < columnas; columna++) {
            int indice = fila * columnas + columna;
            celdagrafica *item = new celdagrafica(fila, columna, tamanioCelda);
            item->setPos(columna * tamanioCelda, fila * tamanioCelda);
            item->setAcceptedMouseButtons(Qt::NoButton);
            escena->addItem(item);
            celdasGraficas[indice] = item;
        }
    }

    escena->setSceneRect(0, 0, columnas * tamanioCelda, filas * tamanioCelda);
}

void VentanaJuego::dibujarTablero()
{
    int filas = tablero->getFilas();
    int columnas = tablero->getColumnas();

    for (int fila = 0; fila < filas; fila++) {
        for (int columna = 0; columna < columnas; columna++) {
            int indice = fila * columnas + columna;
            Celda &celda = tablero->obtenerCelda(fila, columna);
            celdasGraficas[indice]->actualizarDesdeCelda(celda);
        }
    }

    if (!partidaTerminada) {
        etiquetaEstado->setText(QString("Minas: %1").arg(tablero->getCantidadMinas()));
    }
}

void VentanaJuego::manejarClicIzquierdo(int fila, int columna)
{
    if (partidaTerminada || !tablero->estaDentroDelTablero(fila, columna)) {
        return;
    }

    tablero->abrirCelda(fila, columna);
    dibujarTablero();

    if (tablero->juegoPerdido()) {
        finalizarPartida(false);
    } else if (tablero->juegoGanado()) {
        finalizarPartida(true);
    }
}

void VentanaJuego::manejarClicDerecho(int fila, int columna)
{
    if (partidaTerminada || !tablero->estaDentroDelTablero(fila, columna)) {
        return;
    }

    tablero->alternarBandera(fila, columna);
    dibujarTablero();
}

void VentanaJuego::actualizarTiempo(int segundos)
{
    etiquetaTiempo->setText(QString("Tiempo: %1s").arg(segundos));
}

void VentanaJuego::finalizarPartida(bool gano)
{
    partidaTerminada = true;
    cronometro.detener();
    etiquetaEstado->setText(gano ? "¡GANASTE!" : "Perdiste");

    if (gano) {
        int segundos = cronometro.getSegundosTranscurridos();
        QString dificultadTexto = QString("%1x%2").arg(tablero->getFilas()).arg(tablero->getColumnas());

        GestorPuntajes gestorPuntajes;
        gestorPuntajes.guardarPuntaje(nombreJugador.toStdString(), segundos, dificultadTexto.toStdString());

        QMessageBox::information(this, "Victoria",
                                 QString("¡Felicidades! Encontraste todas las celdas seguras en %1 segundos.").arg(segundos));
    } else {
        QMessageBox::information(this, "Derrota", "Abriste una mina. Intenta de nuevo.");
    }
}