#ifndef VENTANAAYUDA_H
#define VENTANAAYUDA_H
#include <QWidget>
class VentanaAyuda:public QWidget
{
    Q_OBJECT
public:
    explicit VentanaAyuda(QWidget* parent=nullptr);
signals:
    void volverSolicitado();
};

#endif // VENTANAAYUDA_H
