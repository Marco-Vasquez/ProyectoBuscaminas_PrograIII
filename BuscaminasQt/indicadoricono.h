#ifndef INDICADORICONO_H
#define INDICADORICONO_H
#include <QWidget>
enum class TipoIcono{
    Mina, Bandera
};

class IndicadorIcono:public QWidget
{
    Q_OBJECT
public:
    explicit IndicadorIcono(TipoIcono tipo,QWidget *parent=nullptr);
    QSize sizeHint() const override;
protected:
    void paintEvent(QPaintEvent *evento) override;
private:
    TipoIcono tipo;
    void dibujarMina(QPainter *painte,const QRectF &rectangulo);
    void dibujarBandera(QPainter *painte,const QRectF &rectangulo);
};

#endif // INDICADORICONO_H
