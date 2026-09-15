#include "buscaminasmain.h"
#include "seleccionardificultad.h"
#include "registrousuario.h"
#include "ventanajuego.h"
#include "ventanarecords.h"
#include "ventanalogin.h"
#include "ventanavictoria.h"
#include "ventanaderrota.h"
#include "gestormedallas.h"
#include "gestoraudio.h"
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
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
    QVBoxLayout *layoutPrincipal = new QVBoxLayout(pantallaMenu);
    layoutPrincipal->setContentsMargins(40, 40, 40, 40);
    layoutPrincipal->setSpacing(15);
    QLabel *etiquetaTitulo = new QLabel("BUSCAMINAS", pantallaMenu);
    QFont fuenteTitulo = etiquetaTitulo->font();
    fuenteTitulo.setPointSize(24);
    fuenteTitulo.setBold(true);
    etiquetaTitulo->setFont(fuenteTitulo);
    etiquetaTitulo->setAlignment(Qt::AlignCenter);
    etiquetaSesion = new QLabel(pantallaMenu);
    etiquetaSesion->setAlignment(Qt::AlignCenter);
    etiquetaSesion->setStyleSheet("color: #7f8c8d;");
    layoutPrincipal->addWidget(etiquetaSesion);
    QHBoxLayout *layoutMedallas=new QHBoxLayout();
    etiquetaMedallaBronce=new QLabel("BRONCE",pantallaMenu);
    etiquetaMedallaPlata=new QLabel("PLATA",pantallaMenu);
    etiquetaMedallaOro=new QLabel("ORO",pantallaMenu);
    etiquetaMedallaDiamante=new QLabel("DIAMANTE",pantallaMenu);
    for(QLabel *medalla:{etiquetaMedallaBronce,etiquetaMedallaPlata,etiquetaMedallaOro,etiquetaMedallaDiamante}){
        medalla->setAlignment(Qt::AlignCenter);
        medalla->setMinimumHeight(30);
        QFont fuenteMedalla=medalla->font();
        fuenteMedalla.setPointSize(9);
        fuenteMedalla.setBold(true);
        medalla->setFont(fuenteMedalla);
    }
    layoutMedallas->addWidget(etiquetaMedallaBronce);
    layoutMedallas->addWidget(etiquetaMedallaPlata);
    layoutMedallas->addWidget(etiquetaMedallaOro);
    layoutMedallas->addWidget(etiquetaMedallaDiamante);
    QPushButton *botonJugar = new QPushButton("JUGAR", pantallaMenu);
    QPushButton *botonRecords = new QPushButton("RÉCORDS", pantallaMenu);
    QPushButton *botonCerrarSesion = new QPushButton("CERRAR SESIÓN", pantallaMenu);
    QPushButton *botonSalir = new QPushButton("SALIR", pantallaMenu);
    for (QPushButton *boton : {botonJugar, botonRecords, botonCerrarSesion, botonSalir}) {
        boton->setMinimumHeight(55);
        QFont fuenteBoton = boton->font();
        fuenteBoton.setPointSize(12);
        fuenteBoton.setBold(true);
        boton->setFont(fuenteBoton);
    }
    botonJugar->setStyleSheet("background-color: #2ecc71; color: white; border-radius: 6px;");
    botonRecords->setStyleSheet("background-color: #9b59b6; color: white; border-radius: 6px;");
    botonCerrarSesion->setStyleSheet("background-color: #f39c12; color: white; border-radius: 6px;");
    botonSalir->setStyleSheet("background-color: #e74c3c; color: white; border-radius: 6px;");
    layoutPrincipal->addWidget(etiquetaTitulo);
    layoutPrincipal->addLayout(layoutMedallas);
    layoutPrincipal->addStretch();
    layoutPrincipal->addWidget(botonJugar);
    layoutPrincipal->addWidget(botonRecords);
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

    panelPrincipal->addWidget(ventanaLogin);
    panelPrincipal->addWidget(pantallaMenu);
    panelPrincipal->addWidget(ventanaSeleccionDificultad);
    panelPrincipal->addWidget(ventanaRegistroUsuario);
    panelPrincipal->addWidget(ventanaRecords);
    panelPrincipal->addWidget(ventanaVictoria);
    panelPrincipal->addWidget(ventanaDerrota);

    //login es punto de entrada antes de llegar al menú.
    panelPrincipal->setCurrentWidget(ventanaLogin);

    connect(botonJugar, &QPushButton::clicked, this, [this]() { panelPrincipal->setCurrentWidget(ventanaSeleccionDificultad); });
    connect(botonRecords, &QPushButton::clicked, this, [this]() { panelPrincipal->setCurrentWidget(ventanaRecords); });
    connect(panelPrincipal, &QStackedWidget::currentChanged, this, [this](int) {
        QWidget *actual = panelPrincipal->currentWidget();
        if (actual == pantallaMenu) {
            actualizarMedallas();
            etiquetaSesion->setText(QString("Sesión activa: %1").arg(nombreUsuarioActual));
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
    string usuario=nombreUsuarioActual.toStdString();
    struct { QLabel *etiqueta; const char *tipo; const char *color; } medallas[] = {
            {etiquetaMedallaBronce, "Bronce", "#cd7f32"},
            {etiquetaMedallaPlata, "Plata", "#a8a9ad"},
            {etiquetaMedallaOro, "Oro", "#f1c40f"},
            {etiquetaMedallaDiamante, "Diamante", "#3498db"},
    };
    for(auto &m:medallas){
        bool obtenida=gestorMedallas.tieneMedalla(usuario,m.tipo);
        if (obtenida){
            m.etiqueta->setStyleSheet(QString("background-color: %1; color: white; border-radius: 6px;").arg(m.color));
        }
        else{
            m.etiqueta->setStyleSheet("background-color: #dcdcdc; color: #999999; border-radius: 6px;");
        }
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