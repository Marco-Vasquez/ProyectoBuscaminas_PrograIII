#include "ventanavictoria.h"
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFont>
VentanaVictoria::VentanaVictoria(QWidget *parent):QWidget(parent) {
    QVBoxLayout *layoutPrincipal = new QVBoxLayout(this);
    layoutPrincipal->setContentsMargins(50, 40, 50, 40);
    layoutPrincipal->setSpacing(14);
    QLabel *etiquetaTitulo = new QLabel("¡VICTORIA!", this);
    QFont fuenteTitulo = etiquetaTitulo->font();
    fuenteTitulo.setPointSize(28);
    fuenteTitulo.setBold(true);
    etiquetaTitulo->setFont(fuenteTitulo);
    etiquetaTitulo->setStyleSheet("color: #2ecc71;");
    etiquetaTitulo->setAlignment(Qt::AlignCenter);
    etiquetaTiempo = new QLabel(this);
    etiquetaBanderas = new QLabel(this);
    etiquetaMedalla = new QLabel(this);
    for (QLabel *etiqueta : {etiquetaTiempo, etiquetaBanderas, etiquetaMedalla}) {
        etiqueta->setAlignment(Qt::AlignCenter);
        QFont fuente = etiqueta->font();
        fuente.setPointSize(13);
        etiqueta->setFont(fuente);
    }
    etiquetaMedalla->setStyleSheet("font-weight: bold;");
    botonSiguienteNivel = new QPushButton("SIGUIENTE NIVEL", this);
    QPushButton *botonVolver = new QPushButton("VOLVER AL MENÚ", this);
    for (QPushButton *boton : {botonSiguienteNivel, botonVolver}) {
        boton->setMinimumHeight(50);
    }
    botonSiguienteNivel->setStyleSheet("background-color: #2ecc71; color: white; border-radius: 6px;");
    botonVolver->setStyleSheet("background-color: #7f8c8d; color: white; border-radius: 6px;");
    connect(botonSiguienteNivel, &QPushButton::clicked, this, [this]() { emit siguienteNivelSolicitado(); });
    connect(botonVolver, &QPushButton::clicked, this, [this]() { emit volverSolicitado(); });
    layoutPrincipal->addStretch();
    layoutPrincipal->addWidget(etiquetaTitulo);
    layoutPrincipal->addSpacing(15);
    layoutPrincipal->addWidget(etiquetaTiempo);
    layoutPrincipal->addWidget(etiquetaBanderas);
    layoutPrincipal->addWidget(etiquetaMedalla);
    layoutPrincipal->addSpacing(20);
    layoutPrincipal->addWidget(botonSiguienteNivel);
    layoutPrincipal->addWidget(botonVolver);
    layoutPrincipal->addStretch();
}
VentanaVictoria::~VentanaVictoria() {}
void VentanaVictoria::mostrarResultado(int segundos, int banderasColocadas, const QString &textoMedalla, bool haySiguienteNivel)
{
    etiquetaTiempo->setText(QString("Tiempo: %1 segundos").arg(segundos));
    etiquetaBanderas->setText(QString("Banderas colocadas: %1").arg(banderasColocadas));
    etiquetaMedalla->setText(textoMedalla);
    botonSiguienteNivel->setVisible(haySiguienteNivel);
}