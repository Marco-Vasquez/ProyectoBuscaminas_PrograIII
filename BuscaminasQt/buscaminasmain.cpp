#include "buscaminasmain.h"
#include "seleccionardificultad.h"
#include "registrousuario.h"
#include "ventanajuego.h"
#include "ventanarecords.h"
#include "ventanalogin.h"
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

    panelPrincipal->addWidget(ventanaLogin);
    panelPrincipal->addWidget(pantallaMenu);
    panelPrincipal->addWidget(ventanaSeleccionDificultad);
    panelPrincipal->addWidget(ventanaRegistroUsuario);
    panelPrincipal->addWidget(ventanaRecords);

    //login es punto de entrada antes de llegar al menú.
    panelPrincipal->setCurrentWidget(ventanaLogin);

    connect(botonJugar, &QPushButton::clicked, this, [this]() { panelPrincipal->setCurrentWidget(ventanaSeleccionDificultad); });
    connect(botonRecords, &QPushButton::clicked, this, [this]() { panelPrincipal->setCurrentWidget(ventanaRecords); });
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
                if (ventanaJuego) {
                    panelPrincipal->removeWidget(ventanaJuego);
                    ventanaJuego->deleteLater();
                    ventanaJuego = nullptr;
                }
                ventanaJuego = new VentanaJuego(cantidadFilas, cantidadColumnas, cantidadMinas, panelPrincipal);
                ventanaJuego->setNombreJugador(nombreUsuarioActual);
                connect(ventanaJuego, &VentanaJuego::volverSolicitado, this, [this]() {
                    panelPrincipal->setCurrentWidget(pantallaMenu);
                });
                panelPrincipal->addWidget(ventanaJuego);
                panelPrincipal->setCurrentWidget(ventanaJuego);
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

BuscaminasMain::~BuscaminasMain() {}