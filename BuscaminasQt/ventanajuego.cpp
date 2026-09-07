#include "ventanajuego.h"
#include "vistajuego.h"
#include "tablero.h"
#include "celda.h"

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsSimpleTextItem>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QWidget>
#include <QMessageBox>
#include <QFont>
#include <QBrush>
#include <QPen>
#include <QColor>

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

    dibujarTablero();
}

VentanaJuego::~VentanaJuego()
{
    delete tablero;
}

void VentanaJuego::dibujarTablero()
{
    escena->clear();

    int filas = tablero->getFilas();
    int columnas = tablero->getColumnas();

    for (int fila = 0; fila < filas; fila++) {
        for (int columna = 0; columna < columnas; columna++) {
            Celda &celda = tablero->obtenerCelda(fila, columna);
            qreal x = columna * TAMANIO_CELDA;
            qreal y = fila * TAMANIO_CELDA;

            QColor colorFondo;
            QString texto;

            if (celda.estaRevelada()) {
                if (celda.tieneMina()) {
                    colorFondo = QColor("#e74c3c");
                    texto = "*";
                } else {
                    colorFondo = QColor("#ecf0f1");
                    if (celda.getMinasVecinas() > 0) {
                        texto = QString::number(celda.getMinasVecinas());
                    }
                }
            } else if (celda.tieneBandera()) {
                colorFondo = QColor("#f1c40f");
                texto = "B";
            } else {
                colorFondo = QColor("#95a5a6");
            }

            escena->addRect(x, y, TAMANIO_CELDA, TAMANIO_CELDA, QPen(Qt::black), QBrush(colorFondo));

            if (!texto.isEmpty()) {
                QGraphicsSimpleTextItem *itemTexto = escena->addSimpleText(texto);
                itemTexto->setPos(x + TAMANIO_CELDA / 2.0 - 5, y + TAMANIO_CELDA / 2.0 - 9);
            }
        }
    }

    escena->setSceneRect(0, 0, columnas * TAMANIO_CELDA, filas * TAMANIO_CELDA);

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