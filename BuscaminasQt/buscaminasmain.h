#ifndef BUSCAMINASMAIN_H
#define BUSCAMINASMAIN_H
#include <QMainWindow>
class QStackedWidget;
class QGraphicsScene;
class QGraphicsView;
class QGraphicsProxyWidget;
class QResizeEvent;
class SeleccionarDificultad;
class RegistroUsuario;
class VentanaJuego;
class VentanaRecords;
class VentanaLogin;
class QLabel;
class VentanaVictoria;
class VentanaDerrota;
class GestorAudio;
class VentanaOpciones;
class VentanaAyuda;
class BuscaminasMain : public QMainWindow
{
    Q_OBJECT
public:
    explicit BuscaminasMain(QWidget *parent = nullptr);
    ~BuscaminasMain() override;
    void setPantallaCompleta(bool completa);
protected:
    // escala toda la interfaz para que crezca junto con la ventana
    void resizeEvent(QResizeEvent *evento) override;
private:
    QStackedWidget *panelPrincipal = nullptr;
    QGraphicsScene *escenaUI = nullptr;
    QGraphicsView *vistaUI = nullptr;
    QGraphicsProxyWidget *proxyUI = nullptr;
    QStackedWidget *contenedorPrincipal = nullptr;
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
    QLabel *etiquetaIconoBronce=nullptr;
    QLabel *etiquetaIconoPlata=nullptr;
    QLabel *etiquetaIconoOro=nullptr;
    QLabel *etiquetaIconoDiamante=nullptr;
    QLabel *etiquetaSesion=nullptr;
    VentanaVictoria *ventanaVictoria=nullptr;
    VentanaDerrota *ventanaDerrota=nullptr;
    GestorAudio *gestorAudio=nullptr;
    VentanaOpciones* ventanaOpciones=nullptr;
    void abrirPartida(int filas,int columnas,int minas);
    void cerrarPantallaPartida();

    void mostrarMenu();

    void guardarPreferenciaMute(bool silenciado);
    void aplicarPreferenciaMute(const QString &usuario);

    void desmutearSinGuardar();
    void actualizarMedallas();
    QString nombreUsuarioActual="Jugador";
    QLabel* etiquetaIconoValiente=nullptr;
    QLabel* etiquetaMedallaValiente=nullptr;
    VentanaAyuda* ventanaAyuda=nullptr;
};
#endif // BUSCAMINASMAIN_H