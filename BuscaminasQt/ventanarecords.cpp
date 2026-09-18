#include "ventanarecords.h"
#include "gestorpuntajes.h"
#include "estilos.h"
#include "medallaimagen.h"
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFrame>
#include <QFont>
#include <QString>
#include <QEvent>
#include <vector>
#include <algorithm>

VentanaRecords::VentanaRecords(QWidget *parent) : QWidget(parent)
{
    setStyleSheet(Estilos::fondoPantalla());

    QVBoxLayout *layoutPrincipal = new QVBoxLayout(this);
    layoutPrincipal->setContentsMargins(40, 25, 40, 25);
    layoutPrincipal->setSpacing(8);

    QLabel *etiquetaTitulo = new QLabel("MEJORES TIEMPOS", this);
    etiquetaTitulo->setStyleSheet(Estilos::titulo(24));
    etiquetaTitulo->setAlignment(Qt::AlignCenter);
    layoutPrincipal->addWidget(etiquetaTitulo);

    QLabel *etiquetaSubtitulo = new QLabel("Ordenados por puntaje", this);
    etiquetaSubtitulo->setStyleSheet(Estilos::textoSuave(12));
    etiquetaSubtitulo->setAlignment(Qt::AlignCenter);
    layoutPrincipal->addWidget(etiquetaSubtitulo);

    //es un layout aparte para vaciar/reconstruir esta pantalla sin tocar el titulo ni el botón volver
    layoutRegistros=new QVBoxLayout();
    layoutPrincipal->addLayout(layoutRegistros);

    QPushButton *botonVolver=new QPushButton("<- VOLVER",this);
    botonVolver->setMinimumHeight(50);
    botonVolver->setStyleSheet(Estilos::botonSecundario());
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
        etiquetaVacio->setStyleSheet(Estilos::textoSuave(13));
        etiquetaVacio->setAlignment(Qt::AlignCenter);
        layoutRegistros->addWidget(etiquetaVacio);
        return;
    }

    // copia local para ordenar por puntaje (mayor primero) sin tocar el gestor
    std::vector<RegistroPuntaje> registros;
    registros.reserve(cantidad);
    for(int i=0;i<cantidad;i++){
        registros.push_back(gestorPuntajes.obtenerRegistro(i));
    }
    std::sort(registros.begin(), registros.end(),
              [](const RegistroPuntaje &a, const RegistroPuntaje &b){
                  return a.puntaje > b.puntaje;
              });

    for(const RegistroPuntaje &registro : registros){

        // tarjeta por partida: contenedor con fondo y bordes redondeados
        QFrame *tarjeta=new QFrame(this);
        tarjeta->setStyleSheet("background-color: #34495e; border-radius: 10px;");
        QHBoxLayout *layoutTarjeta=new QHBoxLayout(tarjeta);
        layoutTarjeta->setContentsMargins(12, 8, 12, 8);
        layoutTarjeta->setSpacing(12);

        // medalla real (PNG) según el registro
        QString nombreMedalla=QString::fromStdString(registro.medalla);
        if(nombreMedalla.isEmpty()){
            nombreMedalla="Ninguna";
        }
        QLabel *iconoMedalla=new QLabel(tarjeta);
        iconoMedalla->setFixedSize(36, 36);
        iconoMedalla->setPixmap(cargarMedallaPixmap(nombreMedalla, 36));
        layoutTarjeta->addWidget(iconoMedalla);

        QVBoxLayout *layoutMedallaNombre=new QVBoxLayout();
        layoutMedallaNombre->setSpacing(0);
        QLabel *etiquetaMedalla=new QLabel(nombreMedalla.toUpper(), tarjeta);
        QFont fuenteMedalla=etiquetaMedalla->font();
        fuenteMedalla.setPointSize(9);
        fuenteMedalla.setBold(true);
        etiquetaMedalla->setFont(fuenteMedalla);
        etiquetaMedalla->setStyleSheet(QString("color: %1; background: transparent;")
                                           .arg(colorDeMedalla(nombreMedalla)));
        layoutMedallaNombre->addWidget(etiquetaMedalla);
        layoutMedallaNombre->addStretch();
        layoutTarjeta->addLayout(layoutMedallaNombre);

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

        // puntaje (grande) y tiempo (chico) a la derecha
        QVBoxLayout *layoutPuntajeTiempo=new QVBoxLayout();
        layoutPuntajeTiempo->setSpacing(2);
        QLabel *etiquetaPuntaje=new QLabel(QString("%1 pts").arg(registro.puntaje), tarjeta);
        QFont fuentePuntaje=etiquetaPuntaje->font();
        fuentePuntaje.setPointSize(14);
        fuentePuntaje.setBold(true);
        etiquetaPuntaje->setFont(fuentePuntaje);
        etiquetaPuntaje->setStyleSheet("color: white; background: transparent;");
        etiquetaPuntaje->setAlignment(Qt::AlignRight);
        QLabel *etiquetaTiempo=new QLabel(QString("%1s").arg(registro.segundos), tarjeta);
        etiquetaTiempo->setStyleSheet("color: #bdc3c7; background: transparent;");
        etiquetaTiempo->setAlignment(Qt::AlignRight);
        layoutPuntajeTiempo->addWidget(etiquetaPuntaje);
        layoutPuntajeTiempo->addWidget(etiquetaTiempo);
        layoutTarjeta->addLayout(layoutPuntajeTiempo);

        layoutRegistros->addWidget(tarjeta);
    }
}