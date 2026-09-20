#ifndef VENTANAVICTORIA_H
#define VENTANAVICTORIA_H
#include <QWidget>
class QLabel;
class QPushButton;
class VentanaVictoria:public QWidget
{
    Q_OBJECT
public:
    explicit VentanaVictoria(QWidget *parent=nullptr);
    ~VentanaVictoria() override;
    void mostrarResultado(int segundos,int banderasColocadas,const QString &textoMedalla,bool haySiguienteNivel);
signals:
    void siguienteNivelSolicitado();
    void volverSolicitado();
private:
    QLabel *etiquetaTiempo;
    QLabel *etiquetaBanderas;
    QLabel *etiquetaMedalla;
    QPushButton *botonSiguienteNivel;
    QLabel* etiquetaIconoMedalla;
};

#endif // VENTANAVICTORIA_H
