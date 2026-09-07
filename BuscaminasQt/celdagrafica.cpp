#include "celdagrafica.h"
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
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
    if(!revelada){
        painter->fillRect(rectangulo,bandera ? QColor("#f39c12"):QColor("#bdc3c7"));
        painter->setPen(Qt::black);
        painter->drawRect(rectangulo);
        if(bandera){
            painter->drawText(rectangulo,Qt::AlignCenter, "🚩");
        }
        return;
    }
    if(mina){
        painter->fillRect(rectangulo,QColor("#e74c3c"));
        painter->setPen(Qt::black);
        painter->drawRect(rectangulo);
        painter->drawText(rectangulo,Qt::AlignCenter,"💣");
        return;
    }
    painter->fillRect(rectangulo,QColor("#ecf0f1"));
    painter->setPen(Qt::black);
    painter->drawRect(rectangulo);
    if(minasVecinas>0){
        static const QColor colores[9]={
            Qt::black,Qt::blue,Qt::darkGreen,Qt::red,Qt::darkBlue,Qt::darkRed,Qt::darkCyan,Qt::black,Qt::gray
        };
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