#include "ventanaopciones.h"
#include "gestoraudio.h"
#include <QLabel>
#include <QSlider>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFont>
VentanaOpciones::VentanaOpciones(GestorAudio* gestorAudio,QWidget* parent): QWidget(parent),gestorAudio(gestorAudio) {
    QVBoxLayout* layoutPrincipal=new QVBoxLayout(this);
    layoutPrincipal->setContentsMargins(40,30,40,30);
    layoutPrincipal->setSpacing(14);
    QLabel* etiquetaTitulo=new QLabel("OPCIONES",this);
    QFont fuenteTitulo=etiquetaTitulo->font();
    fuenteTitulo.setPointSize(18);
    fuenteTitulo.setBold(true);
    etiquetaTitulo->setFont(fuenteTitulo);
    etiquetaTitulo->setAlignment(Qt::AlignCenter);
    QLabel* etiquetaMusica=new QLabel("Volumen de música",this);
    sliderMusica=new QSlider(Qt::Horizontal,this);
    sliderMusica->setRange(0,100);
    sliderMusica->setValue(gestorAudio->getVolumenMusica());
    QLabel* etiquetaEfectos=new QLabel("Volumen de efectos",this);
    sliderEfectos=new QSlider(Qt::Horizontal,this);
    sliderEfectos->setRange(0,100);
    sliderEfectos->setValue(gestorAudio->getVolumenEfectos());
    QPushButton *botonVolver=new QPushButton("<- VOLVER",this);
    botonVolver->setMinimumHeight(50);
    botonVolver->setStyleSheet("background-color: #95a5a6; color: white; border-radius: 6px;");
    connect(sliderMusica,&QSlider::valueChanged,this,[this](int valor){
        this->gestorAudio->setVolumenMusica(valor);
    });
    connect(sliderEfectos,&QSlider::valueChanged,this,[this](int valor){
        this->gestorAudio->setVolumenEfectos(valor);
    });
    connect(botonVolver,&QPushButton::clicked,this,[this](){
        volverSolicitado();
    });
    layoutPrincipal->addWidget(etiquetaTitulo);
    layoutPrincipal->addSpacing(10);
    layoutPrincipal->addWidget(etiquetaMusica);
    layoutPrincipal->addWidget(sliderMusica);
    layoutPrincipal->addSpacing(10);
    layoutPrincipal->addWidget(etiquetaEfectos);
    layoutPrincipal->addWidget(sliderEfectos);
    layoutPrincipal->addStretch();
    layoutPrincipal->addWidget(botonVolver);
}
VentanaOpciones::~VentanaOpciones() {}