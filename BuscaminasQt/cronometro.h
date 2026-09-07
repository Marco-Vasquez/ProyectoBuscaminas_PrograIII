#ifndef CRONOMETRO_H
#define CRONOMETRO_H
#include <QObject>
#include <Qtimer>
class Cronometro:public QObject
{
    Q_OBJECT
public:
    explicit Cronometro(QObject *parent=nullptr);
    void iniciar();
    void detener();
    void reiniciar();
    int getSegundosTranscurridos() const;
signals:
    void tiempoActualizado(int segundos);
private slots:
    void avanzarUnSegundo();
private:
    QTimer temporizador;
    int segundos;
};

#endif // CRONOMETRO_H
