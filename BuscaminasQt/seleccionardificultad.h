#ifndef SELECCIONARDIFICULTAD_H
#define SELECCIONARDIFICULTAD_H
#include <QWidget>
class SeleccionarDificultad : public QWidget
{
    Q_OBJECT
public:
    explicit SeleccionarDificultad(QWidget *parent = nullptr);
    ~SeleccionarDificultad() override;
signals:
    void dificultadSeleccionada(int cantidadFilas, int cantidadColumnas, int cantidadMinas);
    void volverSolicitado();
};
#endif // SELECCIONARDIFICULTAD_H