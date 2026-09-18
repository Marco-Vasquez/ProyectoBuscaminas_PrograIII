#include "seleccionardificultad.h"
#include "estilos.h"
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QStackedWidget>
#include <QShowEvent>
#include <QFont>
#include <QComboBox>

namespace {
const int FILAS_COLUMNAS_MINIMO = 5;
const int FILAS_COLUMNAS_MAXIMO = 40;
}

SeleccionarDificultad::SeleccionarDificultad(QWidget *parent) : QWidget(parent)
{
    setStyleSheet(Estilos::fondoPantalla());

    QVBoxLayout *layoutPrincipal = new QVBoxLayout(this);
    layoutPrincipal->setContentsMargins(0, 0, 0, 0);

    panelDificultad = new QStackedWidget(this);
    layoutPrincipal->addWidget(panelDificultad);

    // --- Página 1: menú de dificultades ---
    QWidget *paginaMenu = new QWidget(panelDificultad);
    QVBoxLayout *layoutMenu = new QVBoxLayout(paginaMenu);
    layoutMenu->setContentsMargins(50, 30, 50, 30);
    layoutMenu->setSpacing(12);

    QLabel *etiquetaTitulo = new QLabel("SELECCIONAR DIFICULTAD", paginaMenu);
    etiquetaTitulo->setStyleSheet(Estilos::titulo(24));
    etiquetaTitulo->setAlignment(Qt::AlignCenter);

    QLabel *etiquetaSubtitulo = new QLabel("Elegí el nivel de desafío", paginaMenu);
    etiquetaSubtitulo->setStyleSheet(Estilos::textoSuave(13));
    etiquetaSubtitulo->setAlignment(Qt::AlignCenter);

    QPushButton *botonFacil = new QPushButton("FÁCIL\n8x8 · 10 minas", paginaMenu);
    botonMedio=new QPushButton("MEDIO\n16x16 · 40 minas", paginaMenu);
    botonDificil=new QPushButton("DIFÍCIL\n16x30 · 99 minas", paginaMenu);
    QPushButton *botonPersonalizado = new QPushButton("PERSONALIZADO", paginaMenu);
    QPushButton *botonVolver = new QPushButton("← VOLVER", paginaMenu);
    botonFacil->setMinimumHeight(60);
    botonFacil->setStyleSheet(Estilos::boton(Estilos::VERDE));
    botonMedio->setMinimumHeight(60);
    botonMedio->setStyleSheet(Estilos::boton(Estilos::AZUL));
    botonDificil->setMinimumHeight(60);
    botonDificil->setStyleSheet(Estilos::boton(Estilos::ROJO));
    botonPersonalizado->setMinimumHeight(55);
    botonPersonalizado->setStyleSheet(Estilos::boton(Estilos::MORADO));
    botonVolver->setMinimumHeight(50);
    botonVolver->setStyleSheet(Estilos::botonSecundario());

    connect(botonFacil, &QPushButton::clicked, this, [this]() { emit dificultadSeleccionada(8, 8, 10); });
    connect(botonMedio, &QPushButton::clicked, this, [this]() { emit dificultadSeleccionada(16, 16, 40); });
    connect(botonDificil, &QPushButton::clicked, this, [this]() { emit dificultadSeleccionada(16, 30, 99); });
    connect(botonPersonalizado, &QPushButton::clicked, panelDificultad, [this]() { panelDificultad->setCurrentIndex(1); });
    connect(botonVolver, &QPushButton::clicked, this, [this]() { emit volverSolicitado(); });

    layoutMenu->addWidget(etiquetaTitulo);
    layoutMenu->addWidget(etiquetaSubtitulo);
    layoutMenu->addSpacing(10);
    layoutMenu->addWidget(botonFacil);
    layoutMenu->addWidget(botonMedio);
    layoutMenu->addWidget(botonDificil);
    layoutMenu->addWidget(botonPersonalizado);
    layoutMenu->addStretch();
    layoutMenu->addWidget(botonVolver);

    // --- Página 2: configuración personalizada ---
    QWidget *paginaPersonalizado = new QWidget(panelDificultad);
    QVBoxLayout *layoutPersonalizado = new QVBoxLayout(paginaPersonalizado);
    layoutPersonalizado->setContentsMargins(50, 30, 50, 30);
    layoutPersonalizado->setSpacing(12);

    QLabel *etiquetaPersonalizado = new QLabel("PERSONALIZADO", paginaPersonalizado);
    etiquetaPersonalizado->setStyleSheet(Estilos::titulo(24));
    etiquetaPersonalizado->setAlignment(Qt::AlignCenter);

    QLabel *etiquetaAyuda = new QLabel("Elegí el tamaño del tablero y la cantidad de minas", paginaPersonalizado);
    etiquetaAyuda->setStyleSheet(Estilos::textoSuave(13));
    etiquetaAyuda->setAlignment(Qt::AlignCenter);

    QComboBox *campoFilas = new QComboBox(paginaPersonalizado);
    for (int i = FILAS_COLUMNAS_MINIMO; i <= FILAS_COLUMNAS_MAXIMO; i++) {
        campoFilas->addItem(QString("Filas: %1").arg(i), i);
    }

    QComboBox *campoColumnas = new QComboBox(paginaPersonalizado);
    for (int i = FILAS_COLUMNAS_MINIMO; i <= FILAS_COLUMNAS_MAXIMO; i++) {
        campoColumnas->addItem(QString("Columnas: %1").arg(i), i);
    }

    QComboBox *campoMinas = new QComboBox(paginaPersonalizado);

    auto actualizarOpcionesMinas = [campoFilas, campoColumnas, campoMinas]() {
        int filasElegidas = campoFilas->currentData().toInt();
        int columnasElegidas = campoColumnas->currentData().toInt();
        int maximoMinas = filasElegidas * columnasElegidas - 1;
        campoMinas->clear();
        for (int i = 1; i <= maximoMinas; i++) {
            campoMinas->addItem(QString("Minas: %1").arg(i), i);
        }
    };
    actualizarOpcionesMinas();

    connect(campoFilas, QOverload<int>::of(&QComboBox::currentIndexChanged), paginaPersonalizado, actualizarOpcionesMinas);
    connect(campoColumnas, QOverload<int>::of(&QComboBox::currentIndexChanged), paginaPersonalizado, actualizarOpcionesMinas);

    for (QComboBox *campo : {campoFilas, campoColumnas, campoMinas}) {
        campo->setMinimumHeight(44);
        campo->setStyleSheet(Estilos::combo());
    }

    QHBoxLayout *layoutCamposPersonalizado = new QHBoxLayout();
    layoutCamposPersonalizado->setSpacing(10);
    layoutCamposPersonalizado->addWidget(campoFilas);
    layoutCamposPersonalizado->addWidget(campoColumnas);
    layoutCamposPersonalizado->addWidget(campoMinas);

    QPushButton *botonJugarPersonalizado = new QPushButton("JUGAR PERSONALIZADO", paginaPersonalizado);
    botonJugarPersonalizado->setMinimumHeight(55);
    botonJugarPersonalizado->setStyleSheet(Estilos::boton(Estilos::MORADO));

    QPushButton *botonVolverPersonalizado = new QPushButton("← VOLVER", paginaPersonalizado);
    botonVolverPersonalizado->setMinimumHeight(50);
    botonVolverPersonalizado->setStyleSheet(Estilos::botonSecundario());

    connect(botonJugarPersonalizado, &QPushButton::clicked, this, [this, campoFilas, campoColumnas, campoMinas]() {
        int filas = campoFilas->currentData().toInt();
        int columnas = campoColumnas->currentData().toInt();
        int minas = campoMinas->currentData().toInt();
        emit dificultadSeleccionada(filas, columnas, minas);
    });

    connect(botonVolverPersonalizado, &QPushButton::clicked, panelDificultad, [this]() { panelDificultad->setCurrentIndex(0); });

    layoutPersonalizado->addWidget(etiquetaPersonalizado);
    layoutPersonalizado->addWidget(etiquetaAyuda);
    layoutPersonalizado->addSpacing(10);
    layoutPersonalizado->addLayout(layoutCamposPersonalizado);
    layoutPersonalizado->addWidget(botonJugarPersonalizado);
    layoutPersonalizado->addStretch();
    layoutPersonalizado->addWidget(botonVolverPersonalizado);

    panelDificultad->addWidget(paginaMenu);
    panelDificultad->addWidget(paginaPersonalizado);
}
void SeleccionarDificultad::showEvent(QShowEvent *evento){
    QWidget::showEvent(evento);
    // al volver a mostrar la pantalla siempre se arranca en el menú de niveles,
    // no en la configuración personalizada que quedó abierta la última vez
    panelDificultad->setCurrentIndex(0);
}
void SeleccionarDificultad::actualizarNivelesDesbloqueados(bool medioDesbloqueado,bool dificilDesbloqueado){
    botonMedio->setEnabled(medioDesbloqueado);
    botonDificil->setEnabled(dificilDesbloqueado);
    // el estilo :disabled del tema ya los muestra grises y bloqueados
}
SeleccionarDificultad::~SeleccionarDificultad() {}