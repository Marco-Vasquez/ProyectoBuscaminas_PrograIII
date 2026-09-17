#ifndef VENTANAOPCIONES_H
#define VENTANAOPCIONES_H
#include <QWidget>
class GestorAudio;
class QSlider;
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
};

#endif // VENTANAOPCIONES_H
