#ifndef VENTANAOPCIONES_H
#define VENTANAOPCIONES_H
#include <QWidget>
class GestorAudio;
class QSlider;
class QLabel;
class VentanaOpciones:public QWidget
{
    Q_OBJECT
public:
    explicit VentanaOpciones(GestorAudio* gestorAudio,QWidget* parent=nullptr);
    ~VentanaOpciones() override;
signals:
    void volverSolicitado();
private:
    GestorAudio* gestorAudio;
    QSlider* sliderMusica;
    QSlider* sliderEfectos;
    QLabel* etiquetaValorMusica;
    QLabel* etiquetaValorEfectos;
};

#endif // VENTANAOPCIONES_H
