#ifndef BUSCAMINASMAIN_H
#define BUSCAMINASMAIN_H
#include <QMainWindow>
class QStackedWidget;
class SeleccionarDificultad;
class RegistroUsuario;
class VentanaJuego;
class VentanaRecords;
class VentanaLogin;
class BuscaminasMain : public QMainWindow
{
    Q_OBJECT
public:
    explicit BuscaminasMain(QWidget *parent = nullptr);
    ~BuscaminasMain() override;
private:
    QStackedWidget *panelPrincipal = nullptr;
    QWidget *pantallaMenu = nullptr;
    VentanaLogin *ventanaLogin = nullptr;
    SeleccionarDificultad *ventanaSeleccionDificultad = nullptr;
    RegistroUsuario *ventanaRegistroUsuario = nullptr;
    VentanaJuego *ventanaJuego = nullptr;
    VentanaRecords *ventanaRecords=nullptr;
    QString nombreUsuarioActual="Jugador";
};
#endif // BUSCAMINASMAIN_H