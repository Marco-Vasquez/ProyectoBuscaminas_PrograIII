#include "ventanaayuda.h"
#include "estilos.h"
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFrame>
VentanaAyuda::VentanaAyuda(QWidget* parent):QWidget(parent) {
    setStyleSheet(Estilos::fondoPantalla());
    QVBoxLayout* layoutPrincipal=new QVBoxLayout(this);
    layoutPrincipal->setContentsMargins(50,30,50,30);
    layoutPrincipal->setSpacing(12);
    QLabel* etiquetaTitulo=new QLabel("¿CÓMO JUGAR?",this);
    etiquetaTitulo->setStyleSheet(Estilos::titulo(26));
    etiquetaTitulo->setAlignment(Qt::AlignCenter);

    QFrame* tarjeta=new QFrame(this);
    tarjeta->setStyleSheet(Estilos::tarjeta());
    tarjeta->setMaximumWidth(560);
    QVBoxLayout* layoutTarjeta=new QVBoxLayout(tarjeta);
    layoutTarjeta->setContentsMargins(24,20,24,20);

    QLabel* etiquetaReglas=new QLabel(
        "• Clic izquierdo revela una celda\n"
        "• Clic derecho coloca o quita una bandera\n"
        "• Los números indican cuántas minas hay alrededor de la celda clickeada\n"
        "• El primer clic nunca será una mina\n"
        "• Para ganar debes de revelar todas las celdas sin minas\n\n"
        "Medallas: Bronce (Fácil), Plata (Medio), Oro (Difícil),\n"
        "Diamante (Personalizado) y Valiente (jugada arriesgada,\n"
        "cuando arriesgás con una probabilidad de una mina cercana al 50%)",
        tarjeta);
    etiquetaReglas->setStyleSheet(Estilos::texto(13));
    etiquetaReglas->setWordWrap(true);

    layoutTarjeta->addWidget(etiquetaReglas);

    QPushButton* botonVolver=new QPushButton("<- VOLVER",this);
    botonVolver->setMinimumHeight(50);
    botonVolver->setMinimumWidth(620);
    botonVolver->setMaximumWidth(620);
    botonVolver->setStyleSheet(Estilos::botonSecundario());
    connect(botonVolver,&QPushButton::clicked,this,[this](){
        emit volverSolicitado();
    });

    layoutPrincipal->addWidget(etiquetaTitulo);
    layoutPrincipal->addSpacing(10);
    layoutPrincipal->addWidget(tarjeta, 0, Qt::AlignHCenter);
    layoutPrincipal->addStretch();
    layoutPrincipal->addWidget(botonVolver, 0, Qt::AlignHCenter);
}
