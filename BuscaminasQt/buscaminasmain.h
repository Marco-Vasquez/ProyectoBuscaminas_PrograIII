#ifndef BUSCAMINASMAIN_H
#define BUSCAMINASMAIN_H
#include <QMainWindow>
class SeleccionarDificultad;
class BuscaminasMain : public QMainWindow
{
    Q_OBJECT
public:
    explicit BuscaminasMain(QWidget *parent = nullptr);
    ~BuscaminasMain() override;
private:
    SeleccionarDificultad *ventanaSeleccionDificultad = nullptr;
};
#endif // BUSCAMINASMAIN_H