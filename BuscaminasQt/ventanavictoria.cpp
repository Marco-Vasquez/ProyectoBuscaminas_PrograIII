#include "ventanavictoria.h"
#include "estilos.h"
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFont>
VentanaVictoria::VentanaVictoria(QWidget *parent):QWidget(parent) {
    setStyleSheet(Estilos::fondoPantalla());

    QVBoxLayout *layoutPrincipal = new QVBoxLayout(this);
    layoutPrincipal->setContentsMargins(60, 40, 60, 40);
    layoutPrincipal->setSpacing(14);
    QLabel *etiquetaTitulo = new QLabel("¡VICTORIA!", this);
    QFont fuenteTitulo = etiquetaTitulo->font();
    fuenteTitulo.setPointSize(30);
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
        etiqueta->setStyleSheet(Estilos::texto(13));
    }
    etiquetaMedalla->setStyleSheet("font-weight: bold; color: #f1c40f; font-size: 14px;");
    botonSiguienteNivel = new QPushButton("SIGUIENTE NIVEL", this);
    QPushButton *botonVolver = new QPushButton("VOLVER AL MENÚ", this);
    botonSiguienteNivel->setMinimumHeight(50);
    botonSiguienteNivel->setStyleSheet(Estilos::boton(Estilos::VERDE));
    botonVolver->setMinimumHeight(50);
    botonVolver->setStyleSheet(Estilos::botonSecundario());
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