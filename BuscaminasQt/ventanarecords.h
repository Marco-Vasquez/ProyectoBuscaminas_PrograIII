#ifndef VENTANARECORDS_H
#define VENTANARECORDS_H
#include <QWidget>
class QVBoxLayout;
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
    void actualizarRecords();
};
#endif // VENTANARECORDS_H