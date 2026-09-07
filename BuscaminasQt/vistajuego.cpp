#include "vistajuego.h"
#include <QMouseEvent>

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