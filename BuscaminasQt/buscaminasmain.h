#ifndef BUSCAMINASMAIN_H
#define BUSCAMINASMAIN_H
#include <QMainWindow>
class QStackedWidget;
class SeleccionarDificultad;
class RegistroUsuario;
class VentanaJuego;
class VentanaRecords;
class VentanaLogin;
class QLabel;
class VentanaVictoria;
class VentanaDerrota;
class GestorAudio;
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
    QLabel *etiquetaMedallaBronce=nullptr;
    QLabel *etiquetaMedallaPlata=nullptr;
    QLabel *etiquetaMedallaOro=nullptr;
    QLabel *etiquetaMedallaDiamante=nullptr;
    QLabel *etiquetaSesion=nullptr;
    VentanaVictoria *ventanaVictoria=nullptr;
    VentanaDerrota *ventanaDerrota=nullptr;
    GestorAudio *gestorAudio=nullptr;
    void abrirPartida(int filas,int columnas,int minas);
    void actualizarMedallas();
    QString nombreUsuarioActual="Jugador";
};
#endif // BUSCAMINASMAIN_H