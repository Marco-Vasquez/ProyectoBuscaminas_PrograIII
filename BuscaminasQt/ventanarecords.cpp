#include "ventanarecords.h"
#include "gestorpuntajes.h"
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFrame>
#include <QFont>
#include <QString>
#include <QEvent>

// mismo esquema de colores de medallas que el menú principal
static QString colorDeMedalla(const std::string &medalla)
{
    if (medalla == "Bronce")   return "#cd7f32";
    if (medalla == "Plata")    return "#a8a9ad";
    if (medalla == "Oro")      return "#f1c40f";
    if (medalla == "Diamante") return "#3498db";
    return "#95a5a6"; // registro sin medalla (archivo viejo)
}

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

        // tarjeta por partida: contenedor con fondo y bordes redondeados
        QFrame *tarjeta=new QFrame(this);
        tarjeta->setStyleSheet("background-color: #34495e; border-radius: 10px;");
        QHBoxLayout *layoutTarjeta=new QHBoxLayout(tarjeta);
        layoutTarjeta->setContentsMargins(12, 8, 12, 8);
        layoutTarjeta->setSpacing(12);

        // insignia de color según la medalla de ese registro
        QString nombreMedalla=QString::fromStdString(registro.medalla);
        if(nombreMedalla.isEmpty()){
            nombreMedalla="SIN MEDALLA";
        }
        QLabel *insignia=new QLabel(nombreMedalla.toUpper(), tarjeta);
        insignia->setAlignment(Qt::AlignCenter);
        insignia->setMinimumSize(110, 28);
        insignia->setStyleSheet(QString("background-color: %1; color: white; border-radius: 14px; font-weight: bold;")
                                    .arg(colorDeMedalla(registro.medalla)));
        layoutTarjeta->addWidget(insignia);

        // nombre + dificultad a la izquierda, tiempo a la derecha
        QVBoxLayout *layoutDatos=new QVBoxLayout();
        layoutDatos->setSpacing(2);
        QLabel *etiquetaNombre=new QLabel(QString::fromStdString(registro.nombreJugador), tarjeta);
        QFont fuenteNombre=etiquetaNombre->font();
        fuenteNombre.setPointSize(11);
        fuenteNombre.setBold(true);
        etiquetaNombre->setFont(fuenteNombre);
        etiquetaNombre->setStyleSheet("color: white; background: transparent;");
        QLabel *etiquetaDificultad=new QLabel(QString::fromStdString(registro.dificultad), tarjeta);
        etiquetaDificultad->setStyleSheet("color: #bdc3c7; background: transparent;");
        layoutDatos->addWidget(etiquetaNombre);
        layoutDatos->addWidget(etiquetaDificultad);
        layoutTarjeta->addLayout(layoutDatos);

        layoutTarjeta->addStretch();

        QLabel *etiquetaTiempo=new QLabel(QString("%1s").arg(registro.segundos), tarjeta);
        QFont fuenteTiempo=etiquetaTiempo->font();
        fuenteTiempo.setPointSize(14);
        fuenteTiempo.setBold(true);
        etiquetaTiempo->setFont(fuenteTiempo);
        etiquetaTiempo->setStyleSheet("color: white; background: transparent;");
        layoutTarjeta->addWidget(etiquetaTiempo);

        layoutRegistros->addWidget(tarjeta);
    }
}