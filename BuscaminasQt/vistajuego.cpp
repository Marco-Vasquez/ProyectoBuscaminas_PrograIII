#include "vistajuego.h"
#include <QMouseEvent>
#include <QResizeEvent>
#include <QGraphicsScene>

VistaJuego::VistaJuego(QWidget *parent)
    : QGraphicsView(parent), tamanioCelda(32)
{
    setRenderHint(QPainter::Antialiasing, false);
}

void VistaJuego::setTamanioCelda(int tamanioPixeles)
{
    tamanioCelda = tamanioPixeles;
}

void VistaJuego::mousePressEvent(QMouseEvent *evento)
{
    QPointF puntoEnEscena = mapToScene(evento->pos());

    if (puntoEnEscena.x() >= 0 && puntoEnEscena.y() >= 0) {
        int columna = static_cast<int>(puntoEnEscena.x()) / tamanioCelda;
        int fila = static_cast<int>(puntoEnEscena.y()) / tamanioCelda;

        if (evento->button() == Qt::LeftButton) {
            emit celdaClicIzquierdo(fila, columna);
        } else if (evento->button() == Qt::RightButton) {
            emit celdaClicDerecho(fila, columna);
        }
    }

    QGraphicsView::mousePressEvent(evento);
}

void VistaJuego::resizeEvent(QResizeEvent *evento)
{
    QGraphicsView::resizeEvent(evento);

    // Reajusta el zoom del tablero para que siempre quepa completo dentro
    // mapToScene() en mousePressEvent ya tiene en cuenta este zoom
    if (scene()) {
        fitInView(scene()->sceneRect(), Qt::KeepAspectRatio);
    }
}