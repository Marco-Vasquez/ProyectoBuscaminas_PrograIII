#ifndef SELECCIONARDIFICULTAD_H
#define SELECCIONARDIFICULTAD_H
#include <QWidget>
#include <QPushButton>
class QStackedWidget;
class QShowEvent;
class SeleccionarDificultad : public QWidget
{
    Q_OBJECT
public:
    explicit SeleccionarDificultad(QWidget *parent = nullptr);
    ~SeleccionarDificultad() override;
    void actualizarNivelesDesbloqueados(bool medioDesbloqueado,bool dificilDesbloqueado);
signals:
    void dificultadSeleccionada(int cantidadFilas, int cantidadColumnas, int cantidadMinas);
    void volverSolicitado();
protected:
    void showEvent(QShowEvent *evento) override;
private:
    QPushButton *botonMedio;
    QPushButton *botonDificil;
    QStackedWidget *panelDificultad;
};
#endif // SELECCIONARDIFICULTAD_H