#ifndef VENTANADERROTA_H
#define VENTANADERROTA_H
#include <QWidget>
class QLabel;
class QPushButton;
class VentanaDerrota:public QWidget
{
    Q_OBJECT
public:
    explicit VentanaDerrota(QWidget *parent=nullptr);
    ~VentanaDerrota() override;
    void mostrarResultado(int segundos,int banderasColocadas);
signals:
    void reintentarSolicitado();
    void volverSolicitado();
private:
    QLabel *etiquetaTiempo;
    QLabel *etiquetaBanderas;
};

#endif // VENTANADERROTA_H