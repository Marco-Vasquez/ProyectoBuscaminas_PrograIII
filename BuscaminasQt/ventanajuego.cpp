#include "ventanajuego.h"
#include "vistajuego.h"
#include "tablero.h"
#include "celda.h"
#include "celdagrafica.h"

#include <QGraphicsScene>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QWidget>
#include <QMessageBox>
#include <QFont>

VentanaJuego::VentanaJuego(int filas, int columnas, int cantidadMinas, QWidget *parent)
    : QMainWindow(parent), partidaTerminada(false)
{
    tablero = new Tablero(filas, columnas, cantidadMinas);

    setWindowTitle("Buscaminas - En juego");

    QWidget *widgetCentral = new QWidget(this);
    setCentralWidget(widgetCentral);
    QVBoxLayout *layoutPrincipal = new QVBoxLayout(widgetCentral);
    layoutPrincipal->setContentsMargins(20, 20, 20, 20);
    layoutPrincipal->setSpacing(12);

    etiquetaEstado = new QLabel(widgetCentral);
    QFont fuenteEstado = etiquetaEstado->font();
    fuenteEstado.setPointSize(12);
    fuenteEstado.setBold(true);
    etiquetaEstado->setFont(fuenteEstado);
    etiquetaEstado->setAlignment(Qt::AlignCenter);

    escena = new QGraphicsScene(this);
    vista = new VistaJuego(widgetCentral);
    vista->setScene(escena);
    vista->setTamanioCelda(TAMANIO_CELDA);
    vista->setFixedSize(columnas * TAMANIO_CELDA + 4, filas * TAMANIO_CELDA + 4);
    vista->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    vista->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QPushButton *botonVolver = new QPushButton("VOLVER AL MENU", widgetCentral);
    botonVolver->setStyleSheet("background-color: #7f8c8d; color: white; border-radius: 6px; padding: 8px;");
    connect(botonVolver, &QPushButton::clicked, this, [this]() { emit volverSolicitado(); });

    layoutPrincipal->addWidget(etiquetaEstado);
    layoutPrincipal->addWidget(vista, 0, Qt::AlignHCenter);
    layoutPrincipal->addWidget(botonVolver);

    connect(vista, &VistaJuego::celdaClicIzquierdo, this, &VentanaJuego::manejarClicIzquierdo);
    connect(vista, &VistaJuego::celdaClicDerecho, this, &VentanaJuego::manejarClicDerecho);

    construirCeldasGraficas();
    dibujarTablero();
}

VentanaJuego::~VentanaJuego()
{
    //celdasGraficas no se borra celda por celda, como cada celdagrafica ya es
    //propiedad de escena, y Qt la destruye sola
    //Acá solo liberamos el arreglo de punteros que armamos nosotros
    delete[] celdasGraficas;
    delete tablero;
}

void VentanaJuego::construirCeldasGraficas()
{
    int filas = tablero->getFilas();
    int columnas = tablero->getColumnas();

    celdasGraficas = new celdagrafica*[filas * columnas];

    for (int fila = 0; fila < filas; fila++) {
        for (int columna = 0; columna < columnas; columna++) {
            int indice = fila * columnas + columna;
            celdagrafica *item = new celdagrafica(fila, columna, TAMANIO_CELDA);
            item->setPos(columna * TAMANIO_CELDA, fila * TAMANIO_CELDA);
            //VistaJuego ya captura los clics y calcula fila/columna a mano,
            //así que le apagamos la captura propia a cada celda para no
            //manejar el mismo clic dos veces
            item->setAcceptedMouseButtons(Qt::NoButton);
            escena->addItem(item);
            celdasGraficas[indice] = item;
        }
    }

    escena->setSceneRect(0, 0, columnas * TAMANIO_CELDA, filas * TAMANIO_CELDA);
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

void VentanaJuego::finalizarPartida(bool gano)
{
    partidaTerminada = true;
    etiquetaEstado->setText(gano ? "¡GANASTE!" : "Perdiste");

    if (gano) {
        QMessageBox::information(this, "Victoria", "¡Felicidades! Encontraste todas las celdas seguras.");
    } else {
        QMessageBox::information(this, "Derrota", "Abriste una mina. Intenta de nuevo.");
    }
}