#include "celdagrafica.h"
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QtMath>
#include <cmath>
celdagrafica::celdagrafica(int fila,int columna,qreal size,QGraphicsItem *parent)
    :QGraphicsObject(parent),fila(fila),columna(columna),size(size),mina(false),revelada(false),minasVecinas(0)
{
    setAcceptedMouseButtons(Qt::LeftButton | Qt::RightButton);
}
QRectF celdagrafica::boundingRect() const{
    return QRectF(0,0,size,size);
}
void celdagrafica::actualizarDesdeCelda(const Celda &celda){
    mina=celda.tieneMina();
    revelada=celda.estaRevelada();
    bandera=celda.tieneBandera();
    minasVecinas=celda.getMinasVecinas();
    update();
}
void celdagrafica::paint(QPainter *painter,const QStyleOptionGraphicsItem *option, QWidget *widget){
    Q_UNUSED(option);
    Q_UNUSED(widget);
    QRectF rectangulo=boundingRect();
    painter->setRenderHint(QPainter::Antialiasing, true);

    if(!revelada){
        painter->fillRect(rectangulo,bandera ? QColor("#f39c12"):QColor("#bdc3c7"));
        painter->setPen(Qt::black);
        painter->drawRect(rectangulo);
        if(bandera){
            dibujarBandera(painter,rectangulo);
        }
        return;
    }
    if(mina){
        painter->fillRect(rectangulo,QColor("#e74c3c"));
        painter->setPen(Qt::black);
        painter->drawRect(rectangulo);
        dibujarMina(painter,rectangulo);
        return;
    }
    painter->fillRect(rectangulo,QColor("#ecf0f1"));
    painter->setPen(Qt::black);
    painter->drawRect(rectangulo);
    if(minasVecinas>0){
        static const QColor colores[9]={
            Qt::black,Qt::blue,Qt::darkGreen,Qt::red,Qt::darkBlue,Qt::darkRed,Qt::darkCyan,Qt::black,Qt::gray
        };
        QFont fuente=painter->font();
        fuente.setBold(true);
        painter->setFont(fuente);
        painter->setPen(colores[minasVecinas]);
        painter->drawText(rectangulo,Qt::AlignCenter,QString::number(minasVecinas));
    }
}
void celdagrafica::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if(event->button()==Qt::LeftButton){
        emit aperturaSolicitada(fila,columna);
    }
    else if(event->button()==Qt::RightButton){
        emit banderaSolicitada(fila,columna);
    }
}

void celdagrafica::dibujarMina(QPainter *painter, const QRectF &rectangulo) const{
    QPointF centro = rectangulo.center();
    qreal radio = rectangulo.width() * 0.28;

    painter->setPen(QPen(Qt::black, qMax(1.0, rectangulo.width() * 0.05)));
    painter->setBrush(Qt::black);
    painter->drawEllipse(centro, radio, radio);

    for (int angulo = 0; angulo < 360; angulo += 45) {
        qreal radianes = qDegreesToRadians(static_cast<qreal>(angulo));
        QPointF desde(centro.x() + std::cos(radianes) * radio,
                      centro.y() + std::sin(radianes) * radio);
        QPointF hasta(centro.x() + std::cos(radianes) * (radio * 1.5),
                      centro.y() + std::sin(radianes) * (radio * 1.5));
        painter->drawLine(desde, hasta);
    }

    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::white);
    painter->drawEllipse(QPointF(centro.x() - radio * 0.35, centro.y() - radio * 0.35), radio * 0.2, radio * 0.2);
}

void celdagrafica::dibujarBandera(QPainter *painter, const QRectF &rectangulo) const{
    qreal margen = rectangulo.width() * 0.22;
    QPointF baseAsta(rectangulo.center().x(), rectangulo.bottom() - margen * 0.6);
    QPointF puntaAsta(rectangulo.center().x(), rectangulo.top() + margen * 0.5);

    painter->setPen(QPen(Qt::black, qMax(1.0, rectangulo.width() * 0.05)));
    painter->drawLine(baseAsta, puntaAsta);

    QPolygonF banderaForma;
    banderaForma << puntaAsta
                 << QPointF(puntaAsta.x() + rectangulo.width() * 0.32, puntaAsta.y() + rectangulo.height() * 0.14)
                 << QPointF(puntaAsta.x(), puntaAsta.y() + rectangulo.height() * 0.28);

    painter->setPen(Qt::black);
    painter->setBrush(QColor("#c0392b"));
    painter->drawPolygon(banderaForma);
}