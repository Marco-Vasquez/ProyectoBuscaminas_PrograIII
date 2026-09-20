#ifndef VENTANARECORDS_H
#define VENTANARECORDS_H
#include <QWidget>
class QVBoxLayout;
class QComboBox;
class QWidget;
class VentanaRecords : public QWidget
{
    Q_OBJECT
public:
    explicit VentanaRecords(QWidget *parent = nullptr);
    ~VentanaRecords() override;
signals:
    void volverSolicitado();
protected:
    void showEvent(QShowEvent *evento) override;
private:
    QVBoxLayout *layoutRegistros;
    QComboBox *filtroDificultad = nullptr;
    QWidget *contenedorRegistros = nullptr;
    void actualizarRecords();
};
#endif // VENTANARECORDS_H