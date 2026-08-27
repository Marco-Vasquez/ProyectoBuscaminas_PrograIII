#include "buscaminasmain.h"
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QFont>
#include <QApplication>
BuscaminasMain::BuscaminasMain(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Buscaminas - Menú Principal");
    resize(700,500);
    QWidget *widgetCentral=new QWidget(this);
    setCentralWidget(widgetCentral);
    QVBoxLayout *layout=new QVBoxLayout(widgetCentral);
    QLabel *titulo=new QLabel("BUSCAMINAS",widgetCentral);
    QFont fuenteTitulo=titulo->font();
    fuenteTitulo.setPointSize(24);
    fuenteTitulo.setBold(true);
    titulo->setFont(fuenteTitulo);
    titulo->setAlignment(Qt::AlignCenter);
    QLabel *subtitulo=new QLabel("Proyecto Programación 3", widgetCentral);
    subtitulo->setAlignment(Qt::AlignCenter);
    subtitulo->setStyleSheet("color: gray;");
    QPushButton *botonJugar=new QPushButton("JUGAR", widgetCentral);
    QPushButton *botonRecords=new QPushButton("RÉCORDS", widgetCentral);
    QPushButton *botonOpciones=new QPushButton("OPCIONES", widgetCentral);
    QPushButton *botonSalir=new QPushButton("SALIR", widgetCentral);
    for(QPushButton *boton:{botonJugar, botonRecords, botonOpciones, botonSalir}) {
        boton->setMinimumHeight(45);
        QFont fuenteBoton = boton->font();
        fuenteBoton.setPointSize(12);
        boton->setFont(fuenteBoton);
    }
    botonJugar->setStyleSheet("background-color: #2ecc71; color: white; border-radius: 6px;");
    botonRecords->setStyleSheet("background-color: #3498db; color: white; border-radius: 6px;");
    botonOpciones->setStyleSheet("background-color: #f39c12; color: white; border-radius: 6px;");
    botonSalir->setStyleSheet("background-color: #e74c3c; color: white; border-radius: 6px;");
    connect(botonSalir, &QPushButton::clicked, qApp, &QApplication::quit);
    layout->addStretch();
    layout->addWidget(titulo);
    layout->addWidget(subtitulo);
    layout->addSpacing(20);
    layout->addWidget(botonJugar);
    layout->addWidget(botonRecords);
    layout->addWidget(botonOpciones);
    layout->addWidget(botonSalir);
    layout->addStretch();
}

BuscaminasMain::~BuscaminasMain() = default;
