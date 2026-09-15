#include "buscaminasmain.h"
#include "seleccionardificultad.h"
#include "registrousuario.h"
#include "ventanajuego.h"
#include "ventanarecords.h"
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
    QPushButton *botonRegistrarse = new QPushButton("REGISTRARSE", pantallaMenu);
    QPushButton *botonRecords = new QPushButton("RÉCORDS", pantallaMenu);
    QPushButton *botonSalir = new QPushButton("SALIR", pantallaMenu);
    for (QPushButton *boton : {botonJugar, botonRegistrarse, botonRecords, botonSalir}) {
        boton->setMinimumHeight(55);
        QFont fuenteBoton = boton->font();
        fuenteBoton.setPointSize(12);
        fuenteBoton.setBold(true);
        boton->setFont(fuenteBoton);
    }
    botonJugar->setStyleSheet("background-color: #2ecc71; color: white; border-radius: 6px;");
    botonRegistrarse->setStyleSheet("background-color: #3498db; color: white; border-radius: 6px;");
    botonRecords->setStyleSheet("background-color: #9b59b6; color: white; border-radius: 6px;");
    botonSalir->setStyleSheet("background-color: #e74c3c; color: white; border-radius: 6px;");
    layoutPrincipal->addWidget(etiquetaTitulo);
    layoutPrincipal->addStretch();
    layoutPrincipal->addWidget(botonJugar);
    layoutPrincipal->addWidget(botonRegistrarse);
    layoutPrincipal->addWidget(botonRecords);
    layoutPrincipal->addWidget(botonSalir);
    layoutPrincipal->addStretch();

    ventanaSeleccionDificultad = new SeleccionarDificultad(panelPrincipal);
    ventanaRegistroUsuario = new RegistroUsuario(panelPrincipal);
    ventanaRecords = new VentanaRecords(panelPrincipal);

    panelPrincipal->addWidget(pantallaMenu);
    panelPrincipal->addWidget(ventanaSeleccionDificultad);
    panelPrincipal->addWidget(ventanaRegistroUsuario);
    panelPrincipal->addWidget(ventanaRecords);
    panelPrincipal->setCurrentWidget(pantallaMenu);

    connect(botonJugar, &QPushButton::clicked, this, [this]() { panelPrincipal->setCurrentWidget(ventanaSeleccionDificultad); });
    connect(botonRegistrarse, &QPushButton::clicked, this, [this]() { panelPrincipal->setCurrentWidget(ventanaRegistroUsuario); });
    connect(botonRecords, &QPushButton::clicked, this, [this]() { panelPrincipal->setCurrentWidget(ventanaRecords); });
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

    connect(ventanaRegistroUsuario, &RegistroUsuario::volverSolicitado, this, [this]() { panelPrincipal->setCurrentWidget(pantallaMenu); });
    connect(ventanaRegistroUsuario, &RegistroUsuario::registroCompletado, this, [this](QString nombreUsuario) {
        nombreUsuarioActual = nombreUsuario;
        panelPrincipal->setCurrentWidget(pantallaMenu);
    });
}

BuscaminasMain::~BuscaminasMain() {}