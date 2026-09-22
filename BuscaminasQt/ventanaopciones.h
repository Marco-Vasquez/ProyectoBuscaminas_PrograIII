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
    // refresca sliders con los niveles reales (el mute de partida los
    // dejaba desactualizados); no dispara los signals de cambio
    void sincronizarValores();
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
