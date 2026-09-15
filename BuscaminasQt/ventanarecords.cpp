#include "ventanarecords.h"
#include "gestorpuntajes.h"
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFont>
#include <QString>
#include <QEvent>

VentanaRecords::VentanaRecords(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *layoutPrincipal = new QVBoxLayout(this);
    layoutPrincipal->setContentsMargins(30, 20, 30, 20);
    layoutPrincipal->setSpacing(8);

    QLabel *etiquetaTitulo = new QLabel("MEJORES TIEMPOS", this);
    QFont fuenteTitulo = etiquetaTitulo->font();
    fuenteTitulo.setPointSize(16);
    fuenteTitulo.setBold(true);
    etiquetaTitulo->setFont(fuenteTitulo);
    etiquetaTitulo->setAlignment(Qt::AlignCenter);
    layoutPrincipal->addWidget(etiquetaTitulo);

    //es un layout aparte para vaciar/reconstruir esta pantalla sin tocar el titulo ni el botón volver
    layoutRegistros=new QVBoxLayout();
    layoutPrincipal->addLayout(layoutRegistros);

    QPushButton *botonVolver=new QPushButton("<- VOLVER",this);
    botonVolver->setStyleSheet("background-color: #95a5a6;color:white;border-radius:6px");
    connect(botonVolver,&QPushButton::clicked,this,[this](){
        emit volverSolicitado();
    });

    layoutPrincipal->addStretch();
    layoutPrincipal->addWidget(botonVolver);

    actualizarRecords();
}

VentanaRecords::~VentanaRecords() {}

void VentanaRecords::showEvent(QShowEvent *evento){
    QWidget::showEvent(evento);
    actualizarRecords();
}

void VentanaRecords::actualizarRecords(){
    //se borran las filas de la vez anterior antes de recargar el archivo
    //de esta manera siempre los puntajes mas recientes se muestran
    QLayoutItem *item;
    while((item=layoutRegistros->takeAt(0))!=nullptr){
        delete item->widget();
        delete item;
    }
    GestorPuntajes gestorPuntajes;
    gestorPuntajes.cargarPuntajes();
    int cantidad=gestorPuntajes.getCantidadRegistros();
    if(cantidad==0){
        QLabel *etiquetaVacio=new QLabel("Todavía no hay puntajes guardados",this);
        etiquetaVacio->setAlignment(Qt::AlignCenter);
        layoutRegistros->addWidget(etiquetaVacio);
        return;
    }
    for(int i=0;i<cantidad;i++){
        const RegistroPuntaje &registro=gestorPuntajes.obtenerRegistro(i);
        QString texto=QString("%1 — %2s — %3")
                            .arg(QString::fromStdString(registro.nombreJugador))
                            .arg(registro.segundos)
                            .arg(QString::fromStdString(registro.dificultad));
        QLabel *etiquetaRegistro=new QLabel(texto,this);
        layoutRegistros->addWidget(etiquetaRegistro);
    }
}