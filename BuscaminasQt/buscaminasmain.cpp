#include "buscaminasmain.h"
#include "seleccionardificultad.h"
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QFont>
BuscaminasMain::BuscaminasMain(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle("Buscaminas - Menú Principal");
    resize(700, 550);
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
    QPushButton *botonSalir = new QPushButton("SALIR", widgetCentral);
    for (QPushButton *boton : {botonJugar, botonSalir}) {
        boton->setMinimumHeight(55);
        QFont fuenteBoton = boton->font();
        fuenteBoton.setPointSize(12);
        fuenteBoton.setBold(true);
        boton->setFont(fuenteBoton);
    }
    botonJugar->setStyleSheet("background-color: #2ecc71; color: white; border-radius: 6px;");
    botonSalir->setStyleSheet("background-color: #e74c3c; color: white; border-radius: 6px;");
    layoutPrincipal->addWidget(etiquetaTitulo);
    layoutPrincipal->addStretch();
    layoutPrincipal->addWidget(botonJugar);
    layoutPrincipal->addWidget(botonSalir);
    layoutPrincipal->addStretch();
    ventanaSeleccionDificultad = new SeleccionarDificultad(this);
    connect(botonJugar, &QPushButton::clicked, this, [this]() { this->hide(); ventanaSeleccionDificultad->show(); });
    connect(botonSalir, &QPushButton::clicked, this, &QMainWindow::close);
    connect(ventanaSeleccionDificultad, &SeleccionarDificultad::volverSolicitado, this, [this]() { ventanaSeleccionDificultad->hide(); this->show(); });
    connect(ventanaSeleccionDificultad, &SeleccionarDificultad::dificultadSeleccionada, this, [](int cantidadFilas, int cantidadColumnas, int cantidadMinas) {});
}
BuscaminasMain::~BuscaminasMain() {}