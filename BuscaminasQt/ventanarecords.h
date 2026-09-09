#ifndef VENTANARECORDS_H
#define VENTANARECORDS_H
#include <QWidget>

class VentanaRecords : public QWidget
{
    Q_OBJECT
public:
    explicit VentanaRecords(QWidget *parent = nullptr);
    ~VentanaRecords() override;
signals:
    void volverSolicitado();
};
#endif // VENTANARECORDS_H