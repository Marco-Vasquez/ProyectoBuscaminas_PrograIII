#include "seleccionardificultad.h"
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QFont>
SeleccionarDificultad::SeleccionarDificultad(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle("Buscaminas - Seleccionar Dificultad");
    resize(700, 550);
    QWidget *widgetCentral = new QWidget(this);
    setCentralWidget(widgetCentral);
    QVBoxLayout *layoutPrincipal = new QVBoxLayout(widgetCentral);
    layoutPrincipal->setContentsMargins(40, 30, 40, 30);
    layoutPrincipal->setSpacing(12);
    QLabel *etiquetaTitulo = new QLabel("SELECCIONAR DIFICULTAD", widgetCentral);
    QFont fuenteTitulo = etiquetaTitulo->font();
    fuenteTitulo.setPointSize(18);
    fuenteTitulo.setBold(true);
    etiquetaTitulo->setFont(fuenteTitulo);
    etiquetaTitulo->setAlignment(Qt::AlignCenter);
    QPushButton *botonFacil = new QPushButton("FÁCIL\n8x8 · 10 minas", widgetCentral);
    QPushButton *botonMedio = new QPushButton("MEDIO\n16x16 · 40 minas", widgetCentral);
    QPushButton *botonDificil = new QPushButton("DIFÍCIL\n16x30 · 99 minas", widgetCentral);
    QPushButton *botonVolver = new QPushButton("← VOLVER", widgetCentral);
    for (QPushButton *boton : {botonFacil, botonMedio, botonDificil, botonVolver}) {
        boton->setMinimumHeight(55);
        QFont fuenteBoton = boton->font();
        fuenteBoton.setPointSize(11);
        boton->setFont(fuenteBoton);
    }
    botonFacil->setStyleSheet("background-color: #2ecc71; color: white; border-radius: 6px;");
    botonMedio->setStyleSheet("background-color: #3498db; color: white; border-radius: 6px;");
    botonDificil->setStyleSheet("background-color: #e74c3c; color: white; border-radius: 6px;");
    botonVolver->setStyleSheet("background-color: #95a5a6; color: white; border-radius: 6px;");
    connect(botonFacil, &QPushButton::clicked, this, [this]() { emit dificultadSeleccionada(8, 8, 10); });
    connect(botonMedio, &QPushButton::clicked, this, [this]() { emit dificultadSeleccionada(16, 16, 40); });
    connect(botonDificil, &QPushButton::clicked, this, [this]() { emit dificultadSeleccionada(16, 30, 99); });
    connect(botonVolver, &QPushButton::clicked, this, [this]() { emit volverSolicitado(); });
    layoutPrincipal->addWidget(etiquetaTitulo);
    layoutPrincipal->addSpacing(10);
    layoutPrincipal->addWidget(botonFacil);
    layoutPrincipal->addWidget(botonMedio);
    layoutPrincipal->addWidget(botonDificil);
    layoutPrincipal->addStretch();
    layoutPrincipal->addWidget(botonVolver);
}
SeleccionarDificultad::~SeleccionarDificultad() {}