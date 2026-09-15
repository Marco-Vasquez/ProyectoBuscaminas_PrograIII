#include "ventanaderrota.h"
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFont>
VentanaDerrota::VentanaDerrota(QWidget *parent):QWidget(parent) {
    QVBoxLayout *layoutPrincipal = new QVBoxLayout(this);
    layoutPrincipal->setContentsMargins(50, 40, 50, 40);
    layoutPrincipal->setSpacing(14);
    QLabel *etiquetaTitulo = new QLabel("PERDISTE", this);
    QFont fuenteTitulo = etiquetaTitulo->font();
    fuenteTitulo.setPointSize(28);
    fuenteTitulo.setBold(true);
    etiquetaTitulo->setFont(fuenteTitulo);
    etiquetaTitulo->setStyleSheet("color: #e74c3c;");
    etiquetaTitulo->setAlignment(Qt::AlignCenter);
    etiquetaTiempo = new QLabel(this);
    etiquetaBanderas = new QLabel(this);
    for (QLabel *etiqueta : {etiquetaTiempo, etiquetaBanderas}) {
        etiqueta->setAlignment(Qt::AlignCenter);
        QFont fuente = etiqueta->font();
        fuente.setPointSize(13);
        etiqueta->setFont(fuente);
    }
    QPushButton *botonReintentar = new QPushButton("REINTENTAR", this);
    QPushButton *botonVolver = new QPushButton("VOLVER AL MENÚ", this);
    for (QPushButton *boton : {botonReintentar, botonVolver}) {
        boton->setMinimumHeight(50);
    }
    botonReintentar->setStyleSheet("background-color: #e74c3c; color: white; border-radius: 6px;");
    botonVolver->setStyleSheet("background-color: #7f8c8d; color: white; border-radius: 6px;");
    connect(botonReintentar, &QPushButton::clicked, this, [this]() { emit reintentarSolicitado(); });
    connect(botonVolver, &QPushButton::clicked, this, [this]() { emit volverSolicitado(); });
    layoutPrincipal->addStretch();
    layoutPrincipal->addWidget(etiquetaTitulo);
    layoutPrincipal->addSpacing(15);
    layoutPrincipal->addWidget(etiquetaTiempo);
    layoutPrincipal->addWidget(etiquetaBanderas);
    layoutPrincipal->addSpacing(20);
    layoutPrincipal->addWidget(botonReintentar);
    layoutPrincipal->addWidget(botonVolver);
    layoutPrincipal->addStretch();
}
VentanaDerrota::~VentanaDerrota() {}
void VentanaDerrota::mostrarResultado(int segundos, int banderasColocadas)
{
    etiquetaTiempo->setText(QString("Tiempo: %1 segundos").arg(segundos));
    etiquetaBanderas->setText(QString("Banderas colocadas: %1").arg(banderasColocadas));
}