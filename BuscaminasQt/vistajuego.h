#ifndef VISTAJUEGO_H
#define VISTAJUEGO_H

#include <QGraphicsView>

// captura clics del mouse sobre la escena
// traduce a coordenadas de fila/columna del Tablero..y reescala
class VistaJuego : public QGraphicsView
{
    Q_OBJECT
public:
    explicit VistaJuego(QWidget *parent = nullptr);
    void setTamanioCelda(int tamanioPixeles);

signals:
    void celdaClicIzquierdo(int fila, int columna);
    void celdaClicDerecho(int fila, int columna);

protected:
    void mousePressEvent(QMouseEvent *evento) override;
    void resizeEvent(QResizeEvent *evento) override;

private:
    int tamanioCelda;
};

#endif // VISTAJUEGO_H