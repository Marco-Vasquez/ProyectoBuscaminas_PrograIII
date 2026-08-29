#ifndef BUSCAMINASMAIN_H
#define BUSCAMINASMAIN_H
#include <QMainWindow>
class SeleccionarDificultad;
class RegistroUsuario;
class BuscaminasMain : public QMainWindow
{
    Q_OBJECT
public:
    explicit BuscaminasMain(QWidget *parent = nullptr);
    ~BuscaminasMain() override;
private:
    SeleccionarDificultad *ventanaSeleccionDificultad = nullptr;
    RegistroUsuario *ventanaRegistroUsuario = nullptr;
};
#endif // BUSCAMINASMAIN_H