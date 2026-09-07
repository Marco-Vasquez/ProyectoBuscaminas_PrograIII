#ifndef CELDAGRAFICA_H
#define CELDAGRAFICA_H
#include <QGraphicsObject>
#include "celda.h"
class celdagrafica:public QGraphicsObject
{
    Q_OBJECT
public:
    celdagrafica(int fila,int columna,qreal size,QGraphicsItem *parent=nullptr);
    QRectF boundingRect() const override;
    void paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget) override;
    void actualizarDesdeCelda(const Celda &celda);
signals:
    void aperturaSolicitada(int fila,int columna);
    void banderaSolicitada(int fila,int columna);
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
private:
    int fila,columna,minasVecinas;
    qreal size;
    bool mina,revelada,bandera;
};

#endif // CELDAGRAFICA_H
