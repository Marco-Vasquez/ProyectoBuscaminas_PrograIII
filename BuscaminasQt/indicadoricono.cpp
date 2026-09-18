#include "indicadoricono.h"
#include <QPainter>
#include <QtMath>
using namespace std;
IndicadorIcono::IndicadorIcono(TipoIcono tipo,QWidget *parent)
    :QWidget(parent),tipo(tipo)
{
    setFixedSize(24,24);
}
QSize IndicadorIcono::sizeHint() const{
    return QSize(24,24);
}
void IndicadorIcono::paintEvent(QPaintEvent *evento){
    Q_UNUSED(evento);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    QRectF rectangulo(0,0,width(),height());
    if(tipo==TipoIcono::Mina){
        dibujarMina(&painter,rectangulo);
    }
    else{
        dibujarBandera(&painter,rectangulo);
    }
}
void IndicadorIcono::dibujarMina(QPainter *painter,const QRectF &rectangulo){
    // color claro para que se vea sobre el encabezado oscuro
    QPointF centro=rectangulo.center();
    qreal radio=rectangulo.width()*0.32;
    painter->setPen(QPen(QColor("#ecf0f1"),1.5));
    painter->setBrush(QColor("#ecf0f1"));
    painter->drawEllipse(centro,radio,radio);
    for(int angulo=0;angulo<360;angulo+=45) {
        qreal radianes=qDegreesToRadians(static_cast<qreal>(angulo));
        QPointF desde(centro.x()+cos(radianes)*radio,centro.y()+sin(radianes)*radio);
        QPointF hasta(centro.x()+cos(radianes)*(radio * 1.5),centro.y()+sin(radianes)*(radio * 1.5));
        painter->drawLine(desde,hasta);
    }
}
void IndicadorIcono::dibujarBandera(QPainter *painter, const QRectF &rectangulo){
    qreal margen=rectangulo.width()*0.22;
    QPointF baseAsta(rectangulo.center().x(),rectangulo.bottom()-margen*0.6);
    QPointF puntaAsta(rectangulo.center().x(),rectangulo.top()+margen*0.5);
    painter->setPen(QPen(QColor("#ecf0f1"),1.5));
    painter->drawLine(baseAsta,puntaAsta);
    QPolygonF banderaForma;
    banderaForma<<puntaAsta
                <<QPointF(puntaAsta.x()+rectangulo.width()*0.35,puntaAsta.y()+rectangulo.height()*0.15)
                <<QPointF(puntaAsta.x(),puntaAsta.y()+rectangulo.height()*0.30);
    painter->setPen(QPen(QColor("#ecf0f1"),1.0));
    painter->setBrush(QColor("#e74c3c"));
    painter->drawPolygon(banderaForma);
}