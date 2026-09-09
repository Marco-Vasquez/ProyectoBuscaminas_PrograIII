#ifndef BUSCAMINASMAIN_H
#define BUSCAMINASMAIN_H
#include <QMainWindow>
class QStackedWidget;
class SeleccionarDificultad;
class RegistroUsuario;
class VentanaJuego;
class BuscaminasMain : public QMainWindow
{
    Q_OBJECT
public:
    explicit BuscaminasMain(QWidget *parent = nullptr);
    ~BuscaminasMain() override;
private:
    QStackedWidget *panelPrincipal = nullptr;
    QWidget *pantallaMenu = nullptr;
    SeleccionarDificultad *ventanaSeleccionDificultad = nullptr;
    RegistroUsuario *ventanaRegistroUsuario = nullptr;
    VentanaJuego *ventanaJuego = nullptr;
};
#endif // BUSCAMINASMAIN_H