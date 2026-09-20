#include "ventanaopciones.h"
#include "gestoraudio.h"
#include "estilos.h"
#include <QLabel>
#include <QSlider>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFrame>
#include <QFont>
VentanaOpciones::VentanaOpciones(GestorAudio* gestorAudio,QWidget* parent): QWidget(parent),gestorAudio(gestorAudio) {
    setStyleSheet(Estilos::fondoPantalla());

    QVBoxLayout* layoutPrincipal=new QVBoxLayout(this);
    layoutPrincipal->setContentsMargins(60,40,60,40);
    layoutPrincipal->setSpacing(12);
    QLabel* etiquetaTitulo=new QLabel("OPCIONES",this);
    etiquetaTitulo->setStyleSheet(Estilos::titulo(24));
    etiquetaTitulo->setAlignment(Qt::AlignCenter);

    QLabel* etiquetaSubtitulo=new QLabel("Ajustá el sonido a tu gusto",this);
    etiquetaSubtitulo->setStyleSheet(Estilos::textoSuave(13));
    etiquetaSubtitulo->setAlignment(Qt::AlignCenter);

    // tarjeta con los controles de audio
    QFrame* tarjeta=new QFrame(this);
    tarjeta->setStyleSheet(Estilos::tarjeta());
    tarjeta->setMaximumWidth(560); // no se estira en pantallas anchas
    QVBoxLayout* layoutTarjeta=new QVBoxLayout(tarjeta);
    layoutTarjeta->setContentsMargins(24,20,24,20);
    layoutTarjeta->setSpacing(8);

    QLabel* etiquetaMusica=new QLabel("Volumen de música",tarjeta);
    etiquetaMusica->setStyleSheet(Estilos::texto(13));
    sliderMusica=new QSlider(Qt::Horizontal,tarjeta);
    sliderMusica->setRange(0,100);
    sliderMusica->setValue(gestorAudio->getVolumenMusica());
    sliderMusica->setStyleSheet(Estilos::slider());
    etiquetaValorMusica=new QLabel(QString("%1%").arg(sliderMusica->value()),tarjeta);
    etiquetaValorMusica->setStyleSheet(Estilos::texto(13));
    etiquetaValorMusica->setAlignment(Qt::AlignRight);

    QLabel* etiquetaEfectos=new QLabel("Volumen de efectos",tarjeta);
    etiquetaEfectos->setStyleSheet(Estilos::texto(13));
    sliderEfectos=new QSlider(Qt::Horizontal,tarjeta);
    sliderEfectos->setRange(0,100);
    sliderEfectos->setValue(gestorAudio->getVolumenEfectos());
    sliderEfectos->setStyleSheet(Estilos::slider());
    etiquetaValorEfectos=new QLabel(QString("%1%").arg(sliderEfectos->value()),tarjeta);
    etiquetaValorEfectos->setStyleSheet(Estilos::texto(13));
    etiquetaValorEfectos->setAlignment(Qt::AlignRight);

    QPushButton *botonVolver=new QPushButton("<- VOLVER",this);
    botonVolver->setMinimumHeight(50);
    botonVolver->setStyleSheet(Estilos::botonSecundario());
    connect(sliderMusica,&QSlider::valueChanged,this,[this](int valor){
        this->gestorAudio->setVolumenMusica(valor);
        this->etiquetaValorMusica->setText(QString("%1%").arg(valor));
    });
    connect(sliderEfectos,&QSlider::valueChanged,this,[this](int valor){
        this->gestorAudio->setVolumenEfectos(valor);
        this->etiquetaValorEfectos->setText(QString("%1%").arg(valor));
    });
    connect(botonVolver,&QPushButton::clicked,this,[this](){
        volverSolicitado();
    });

    // fila: etiqueta + slider + porcentaje
    QHBoxLayout* filaMusica=new QHBoxLayout();
    filaMusica->addWidget(etiquetaMusica);
    filaMusica->addWidget(sliderMusica, 1);
    filaMusica->addWidget(etiquetaValorMusica);
    QHBoxLayout* filaEfectos=new QHBoxLayout();
    filaEfectos->addWidget(etiquetaEfectos);
    filaEfectos->addWidget(sliderEfectos, 1);
    filaEfectos->addWidget(etiquetaValorEfectos);

    layoutTarjeta->addLayout(filaMusica);
    layoutTarjeta->addSpacing(10);
    layoutTarjeta->addLayout(filaEfectos);

    layoutPrincipal->addStretch();
    layoutPrincipal->addWidget(etiquetaTitulo);
    layoutPrincipal->addWidget(etiquetaSubtitulo);
    layoutPrincipal->addSpacing(16);
    layoutPrincipal->addWidget(tarjeta, 0, Qt::AlignHCenter);
    layoutPrincipal->addStretch();
    layoutPrincipal->addWidget(botonVolver);
    layoutPrincipal->addSpacing(8);
}
VentanaOpciones::~VentanaOpciones() {}