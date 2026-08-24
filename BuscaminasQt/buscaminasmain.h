#ifndef BUSCAMINASMAIN_H
#define BUSCAMINASMAIN_H

#include <QMainWindow>

class BuscaminasMain : public QMainWindow
{
    Q_OBJECT

public:
    explicit BuscaminasMain(QWidget *parent = nullptr);
    ~BuscaminasMain() override;
};
#endif // BUSCAMINASMAIN_H
