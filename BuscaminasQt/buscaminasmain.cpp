#include "buscaminasmain.h"
#include "seleccionardificultad.h"
#include "registrousuario.h"
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QFont>
BuscaminasMain::BuscaminasMain(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle("Buscaminas - Menú Principal");
    resize(400, 380);
    QWidget *widgetCentral = new QWidget(this);
    setCentralWidget(widgetCentral);
    QVBoxLayout *layoutPrincipal = new QVBoxLayout(widgetCentral);
    layoutPrincipal->setContentsMargins(40, 40, 40, 40);
    layoutPrincipal->setSpacing(15);
    QLabel *etiquetaTitulo = new QLabel("BUSCAMINAS", widgetCentral);
    QFont fuenteTitulo = etiquetaTitulo->font();
    fuenteTitulo.setPointSize(24);
    fuenteTitulo.setBold(true);
    etiquetaTitulo->setFont(fuenteTitulo);
    etiquetaTitulo->setAlignment(Qt::AlignCenter);
    QPushButton *botonJugar = new QPushButton("JUGAR", widgetCentral);
    QPushButton *botonRegistrarse = new QPushButton("REGISTRARSE", widgetCentral);
    QPushButton *botonSalir = new QPushButton("SALIR", widgetCentral);
    for (QPushButton *boton : {botonJugar, botonRegistrarse, botonSalir}) {
        boton->setMinimumHeight(55);
        QFont fuenteBoton = boton->font();
        fuenteBoton.setPointSize(12);
        fuenteBoton.setBold(true);
        boton->setFont(fuenteBoton);
    }
    botonJugar->setStyleSheet("background-color: #2ecc71; color: white; border-radius: 6px;");
    botonRegistrarse->setStyleSheet("background-color: #3498db; color: white; border-radius: 6px;");
    botonSalir->setStyleSheet("background-color: #e74c3c; color: white; border-radius: 6px;");
    layoutPrincipal->addWidget(etiquetaTitulo);
    layoutPrincipal->addStretch();
    layoutPrincipal->addWidget(botonJugar);
    layoutPrincipal->addWidget(botonRegistrarse);
    layoutPrincipal->addWidget(botonSalir);
    layoutPrincipal->addStretch();
    ventanaSeleccionDificultad = new SeleccionarDificultad(this);
    ventanaRegistroUsuario = new RegistroUsuario(this);
    connect(botonJugar, &QPushButton::clicked, this, [this]() { this->hide(); ventanaSeleccionDificultad->show(); });
    connect(botonRegistrarse, &QPushButton::clicked, this, [this]() { this->hide(); ventanaRegistroUsuario->show(); });
    connect(botonSalir, &QPushButton::clicked, this, &QMainWindow::close);
    connect(ventanaSeleccionDificultad, &SeleccionarDificultad::volverSolicitado, this, [this]() { ventanaSeleccionDificultad->hide(); this->show(); });
    connect(ventanaSeleccionDificultad, &SeleccionarDificultad::dificultadSeleccionada, this, [](int cantidadFilas, int cantidadColumnas, int cantidadMinas) {});
    connect(ventanaRegistroUsuario, &RegistroUsuario::volverSolicitado, this, [this]() { ventanaRegistroUsuario->hide(); this->show(); });
    connect(ventanaRegistroUsuario, &RegistroUsuario::registroCompletado, this, [this](QString nombreUsuario) {
        ventanaRegistroUsuario->hide();
        this->show();
    });
}
BuscaminasMain::~BuscaminasMain() {}