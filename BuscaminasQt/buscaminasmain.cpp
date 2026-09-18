#include "buscaminasmain.h"
#include "seleccionardificultad.h"
#include "registrousuario.h"
#include "ventanajuego.h"
#include "ventanarecords.h"
#include "ventanalogin.h"
#include "ventanavictoria.h"
#include "ventanaderrota.h"
#include "ventanaopciones.h"
#include "gestormedallas.h"
#include "gestoraudio.h"
#include "estilos.h"
#include "medallaimagen.h"
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFrame>
#include <QWidget>
#include <QStackedWidget>
#include <QFont>

BuscaminasMain::BuscaminasMain(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle("Buscaminas - Menú Principal");
    resize(700, 550);

    panelPrincipal = new QStackedWidget(this);
    setCentralWidget(panelPrincipal);

    // Menú principal
    pantallaMenu = new QWidget(panelPrincipal);
    pantallaMenu->setStyleSheet(Estilos::fondoPantalla());
    QVBoxLayout *layoutPrincipal = new QVBoxLayout(pantallaMenu);
    layoutPrincipal->setContentsMargins(50, 30, 50, 30);
    layoutPrincipal->setSpacing(12);
    QLabel *etiquetaTitulo = new QLabel("BUSCAMINAS", pantallaMenu);
    etiquetaTitulo->setStyleSheet(Estilos::titulo(30));
    etiquetaTitulo->setAlignment(Qt::AlignCenter);
    etiquetaSesion = new QLabel(pantallaMenu);
    etiquetaSesion->setAlignment(Qt::AlignCenter);
    etiquetaSesion->setStyleSheet(Estilos::texto(16));
    layoutPrincipal->addWidget(etiquetaSesion);

    // medallas del jugador: tarjetas con el PNG real de cada medalla
    QHBoxLayout *layoutMedallas = new QHBoxLayout();
    layoutMedallas->setSpacing(10);
    etiquetaIconoBronce = new QLabel(pantallaMenu);
    etiquetaIconoPlata = new QLabel(pantallaMenu);
    etiquetaIconoOro = new QLabel(pantallaMenu);
    etiquetaIconoDiamante = new QLabel(pantallaMenu);
    etiquetaMedallaBronce = new QLabel("BRONCE", pantallaMenu);
    etiquetaMedallaPlata = new QLabel("PLATA", pantallaMenu);
    etiquetaMedallaOro = new QLabel("ORO", pantallaMenu);
    etiquetaMedallaDiamante = new QLabel("DIAMANTE", pantallaMenu);
    struct { QLabel *icono; QLabel *nombre; } medallas[] = {
        {etiquetaIconoBronce, etiquetaMedallaBronce},
        {etiquetaIconoPlata, etiquetaMedallaPlata},
        {etiquetaIconoOro, etiquetaMedallaOro},
        {etiquetaIconoDiamante, etiquetaMedallaDiamante},
    };
    for (auto &m : medallas) {
        QFrame *tarjetaMedalla = new QFrame(pantallaMenu);
        tarjetaMedalla->setStyleSheet(Estilos::tarjeta());
        QVBoxLayout *layoutMedalla = new QVBoxLayout(tarjetaMedalla);
        layoutMedalla->setContentsMargins(10, 10, 10, 8);
        layoutMedalla->setSpacing(4);
        m.icono->setFixedSize(44, 44);
        m.icono->setAlignment(Qt::AlignCenter);
        m.nombre->setAlignment(Qt::AlignCenter);
        m.nombre->setStyleSheet("color: #5d6d6e; font-weight: bold; font-size: 10px;");
        layoutMedalla->addWidget(m.icono);
        layoutMedalla->addWidget(m.nombre);
        layoutMedallas->addWidget(tarjetaMedalla);
    }
    QPushButton *botonJugar = new QPushButton("JUGAR", pantallaMenu);
    QPushButton *botonRecords = new QPushButton("RÉCORDS", pantallaMenu);
    QPushButton *botonOpciones = new QPushButton("OPCIONES", pantallaMenu);
    QPushButton *botonCerrarSesion = new QPushButton("CERRAR SESIÓN", pantallaMenu);
    QPushButton *botonSalir = new QPushButton("SALIR", pantallaMenu);
    botonJugar->setMinimumHeight(60);
    botonJugar->setStyleSheet(Estilos::boton(Estilos::VERDE));
    botonRecords->setMinimumHeight(50);
    botonRecords->setStyleSheet(Estilos::boton(Estilos::MORADO));
    botonOpciones->setMinimumHeight(50);
    botonOpciones->setStyleSheet(Estilos::boton(Estilos::TURQUESA));
    botonCerrarSesion->setMinimumHeight(50);
    botonCerrarSesion->setStyleSheet(Estilos::boton(Estilos::NARANJA));
    botonSalir->setMinimumHeight(50);
    botonSalir->setStyleSheet(Estilos::boton(Estilos::ROJO));
    layoutPrincipal->addWidget(etiquetaTitulo);
    layoutPrincipal->addLayout(layoutMedallas);
    layoutPrincipal->addStretch();
    layoutPrincipal->addWidget(botonJugar);
    layoutPrincipal->addWidget(botonRecords);
    layoutPrincipal->addWidget(botonOpciones);
    layoutPrincipal->addWidget(botonCerrarSesion);
    layoutPrincipal->addWidget(botonSalir);
    layoutPrincipal->addStretch();

    ventanaLogin = new VentanaLogin(panelPrincipal);
    ventanaSeleccionDificultad = new SeleccionarDificultad(panelPrincipal);
    ventanaRegistroUsuario = new RegistroUsuario(panelPrincipal);
    ventanaRecords = new VentanaRecords(panelPrincipal);
    ventanaVictoria = new VentanaVictoria(panelPrincipal);
    ventanaDerrota = new VentanaDerrota(panelPrincipal);
    gestorAudio = new GestorAudio(this);
    ventanaOpciones = new VentanaOpciones(gestorAudio, panelPrincipal);

    panelPrincipal->addWidget(ventanaLogin);
    panelPrincipal->addWidget(pantallaMenu);
    panelPrincipal->addWidget(ventanaSeleccionDificultad);
    panelPrincipal->addWidget(ventanaRegistroUsuario);
    panelPrincipal->addWidget(ventanaRecords);
    panelPrincipal->addWidget(ventanaVictoria);
    panelPrincipal->addWidget(ventanaDerrota);
    panelPrincipal->addWidget(ventanaOpciones);

    //login es punto de entrada antes de llegar al menú.
    panelPrincipal->setCurrentWidget(ventanaLogin);

    connect(botonJugar, &QPushButton::clicked, this, [this]() {
        GestorMedallas gestorMedallas;
        std::string usuario = nombreUsuarioActual.toStdString();
        bool medioDesbloqueado = gestorMedallas.tieneMedalla(usuario, "Bronce");
        bool dificilDesbloqueado = gestorMedallas.tieneMedalla(usuario, "Plata");
        ventanaSeleccionDificultad->actualizarNivelesDesbloqueados(medioDesbloqueado, dificilDesbloqueado);
        panelPrincipal->setCurrentWidget(ventanaSeleccionDificultad);
    });
    connect(botonRecords, &QPushButton::clicked, this, [this]() { panelPrincipal->setCurrentWidget(ventanaRecords); });
    connect(botonOpciones, &QPushButton::clicked, this, [this]() { panelPrincipal->setCurrentWidget(ventanaOpciones); });
    connect(ventanaOpciones, &VentanaOpciones::volverSolicitado, this, [this]() { panelPrincipal->setCurrentWidget(pantallaMenu); });
    connect(panelPrincipal, &QStackedWidget::currentChanged, this, [this](int) {
        QWidget *actual = panelPrincipal->currentWidget();
        if (actual == pantallaMenu) {
            actualizarMedallas();
            etiquetaSesion->setText(QString("¡Hola, %1!").arg(nombreUsuarioActual));
            gestorAudio->iniciarMusicaMenu();
        } else if (actual == ventanaLogin) {
            gestorAudio->detenerMusica();
        } else if (actual == ventanaDerrota || actual == ventanaVictoria) {
            gestorAudio->detenerMusica();
        }
    });
    connect(ventanaVictoria, &VentanaVictoria::volverSolicitado, this, [this]() { panelPrincipal->setCurrentWidget(pantallaMenu); });
    connect(ventanaVictoria, &VentanaVictoria::siguienteNivelSolicitado, this, [this]() {
        // los valores quedan guardados en las propiedades dinámicas de ventanaVictoria (ver abajo)
        int filas = ventanaVictoria->property("filasSig").toInt();
        int columnas = ventanaVictoria->property("columnasSig").toInt();
        int minas = ventanaVictoria->property("minasSig").toInt();
        abrirPartida(filas, columnas, minas);
    });
    connect(ventanaDerrota, &VentanaDerrota::volverSolicitado, this, [this]() { panelPrincipal->setCurrentWidget(pantallaMenu); });
    connect(ventanaDerrota, &VentanaDerrota::reintentarSolicitado, this, [this]() {
        // los valores quedan guardados en las propiedades dinámicas de ventanaDerrota (ver abajo)
        int filas = ventanaDerrota->property("filasReintento").toInt();
        int columnas = ventanaDerrota->property("columnasReintento").toInt();
        int minas = ventanaDerrota->property("minasReintento").toInt();
        abrirPartida(filas, columnas, minas);
    });
    connect(botonCerrarSesion, &QPushButton::clicked, this, [this]() {
        // Descarta la partida en curso (si la hay) para no arrastrar estado entre cuentas
        if (ventanaJuego) {
            panelPrincipal->removeWidget(ventanaJuego);
            ventanaJuego->deleteLater();
            ventanaJuego = nullptr;
        }
        nombreUsuarioActual = "Jugador";
        ventanaLogin->limpiarCampos();
        panelPrincipal->setCurrentWidget(ventanaLogin);
    });
    connect(botonSalir, &QPushButton::clicked, this, &QMainWindow::close);

    connect(ventanaSeleccionDificultad, &SeleccionarDificultad::volverSolicitado, this, [this]() { panelPrincipal->setCurrentWidget(pantallaMenu); });
    connect(ventanaSeleccionDificultad, &SeleccionarDificultad::dificultadSeleccionada, this,
            [this](int cantidadFilas, int cantidadColumnas, int cantidadMinas) {
                abrirPartida(cantidadFilas, cantidadColumnas, cantidadMinas);
            });

    connect(ventanaRecords, &VentanaRecords::volverSolicitado, this, [this]() { panelPrincipal->setCurrentWidget(pantallaMenu); });

    //al entrar correctamente se guarda el usuario y pasa al menú
    connect(ventanaLogin, &VentanaLogin::loginExitoso, this, [this](QString nombreUsuario) {
        nombreUsuarioActual = nombreUsuario;
        panelPrincipal->setCurrentWidget(pantallaMenu);
    });
    connect(ventanaLogin, &VentanaLogin::registroSolicitado, this, [this]() {
        panelPrincipal->setCurrentWidget(ventanaRegistroUsuario);
    });

    connect(ventanaLogin, &VentanaLogin::salirSolicitado, this, &QMainWindow::close);

    // volver regresa al login
    connect(ventanaRegistroUsuario, &RegistroUsuario::volverSolicitado, this, [this]() {
        panelPrincipal->setCurrentWidget(ventanaLogin);
    });
    // al registrarse correctamente se ingresa directo al juego con esa cuenta
    connect(ventanaRegistroUsuario, &RegistroUsuario::registroCompletado, this, [this](QString nombreUsuario) {
        nombreUsuarioActual = nombreUsuario;
        panelPrincipal->setCurrentWidget(pantallaMenu);
    });
}
void BuscaminasMain::actualizarMedallas(){
    GestorMedallas gestorMedallas;
    std::string usuario=nombreUsuarioActual.toStdString();
    struct { QLabel *icono; QLabel *nombre; const char *tipo; } medallas[] = {
                     {etiquetaIconoBronce, etiquetaMedallaBronce, "Bronce"},
                     {etiquetaIconoPlata, etiquetaMedallaPlata, "Plata"},
                     {etiquetaIconoOro, etiquetaMedallaOro, "Oro"},
                     {etiquetaIconoDiamante, etiquetaMedallaDiamante, "Diamante"},
                     };
    for(auto &m:medallas){
        bool obtenida=gestorMedallas.tieneMedalla(usuario,m.tipo);
        // PNG real de la medalla; gris (ninguna) si todavía no se ganó
        m.icono->setPixmap(cargarMedallaPixmap(obtenida ? QString(m.tipo) : "Ninguna", 44));
        m.nombre->setStyleSheet(obtenida
            ? QString("color: %1; font-weight: bold; font-size: 10px;").arg(colorDeMedalla(m.tipo))
            : "color: #5d6d6e; font-weight: bold; font-size: 10px;");
    }
}
void BuscaminasMain::abrirPartida(int filas, int columnas, int minas)
{
    if (ventanaJuego) {
        panelPrincipal->removeWidget(ventanaJuego);
        ventanaJuego->deleteLater();
        ventanaJuego = nullptr;
    }
    ventanaJuego = new VentanaJuego(filas, columnas, minas, panelPrincipal);
    ventanaJuego->setNombreJugador(nombreUsuarioActual);
    ventanaJuego->setGestorAudio(gestorAudio);

    connect(ventanaJuego, &VentanaJuego::volverSolicitado, this, [this]() {
        panelPrincipal->setCurrentWidget(pantallaMenu);
    });
    connect(ventanaJuego, &VentanaJuego::victoriaObtenida, this,
            [this](int segundos, int banderas, QString textoMedalla, bool haySiguiente, int filasSig, int columnasSig, int minasSig) {
                ventanaVictoria->setProperty("filasSig", filasSig);
                ventanaVictoria->setProperty("columnasSig", columnasSig);
                ventanaVictoria->setProperty("minasSig", minasSig);
                ventanaVictoria->mostrarResultado(segundos, banderas, textoMedalla, haySiguiente);
                panelPrincipal->setCurrentWidget(ventanaVictoria);
            });
    connect(ventanaJuego, &VentanaJuego::derrotaObtenida, this,
            [this](int filas, int columnas, int minas) {
                ventanaDerrota->setProperty("filasReintento", filas);
                ventanaDerrota->setProperty("columnasReintento", columnas);
                ventanaDerrota->setProperty("minasReintento", minas);
                ventanaDerrota->mostrarResultado(ventanaJuego->getSegundosTranscurridos(),
                                                 ventanaJuego->getBanderasColocadas());
                panelPrincipal->setCurrentWidget(ventanaDerrota);
            });

    panelPrincipal->addWidget(ventanaJuego);
    panelPrincipal->setCurrentWidget(ventanaJuego);
    gestorAudio->iniciarMusicaJuego();
}
BuscaminasMain::~BuscaminasMain() {}