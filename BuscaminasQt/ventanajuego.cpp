#include "ventanajuego.h"
#include "vistajuego.h"
#include "tablero.h"
#include "celda.h"
#include "celdagrafica.h"
#include "gestorpuntajes.h"
#include "gestormedallas.h"
#include "indicadoricono.h"
#include "gestoraudio.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGraphicsScene>
#include <QLabel>
#include <QPushButton>
#include <QFrame>
#include <QFont>
#include <QSizePolicy>
#include <algorithm>

VentanaJuego::VentanaJuego(int filas, int columnas, int cantidadMinas, QWidget *parent)
    : QWidget(parent), nombreJugador("Jugador"), partidaTerminada(false)
{
    tablero = new Tablero(filas, columnas, cantidadMinas);

    //tamaño de cada celda se calcula para que el tablero completo
    //siempre entre en la misma área
    int celdaPorAncho = ANCHO_AREA_TABLERO / columnas;
    int celdaPorAlto = ALTO_AREA_TABLERO / filas;
    tamanioCelda = std::min(celdaPorAncho, celdaPorAlto);
    if (tamanioCelda < 10) {
        tamanioCelda = 10;
    }

    QVBoxLayout *layoutPrincipal = new QVBoxLayout(this);
    layoutPrincipal->setContentsMargins(15, 15, 15, 15);
    layoutPrincipal->setSpacing(10);

    QFrame *panelEncabezado = new QFrame(this);
    panelEncabezado->setStyleSheet("background-color: #ecf0f1; border-radius: 8px;");
    QHBoxLayout *layoutEncabezado = new QHBoxLayout(panelEncabezado);
    layoutEncabezado->setContentsMargins(12, 8, 12, 8);

    etiquetaJugador=new QLabel(QString("Jugador: %1").arg(nombreJugador),panelEncabezado);
    etiquetaEstado = new QLabel(panelEncabezado);
    etiquetaBanderas=new QLabel(panelEncabezado);
    etiquetaTiempo = new QLabel("Tiempo: 0s", panelEncabezado);
    for (QLabel *etiqueta : {etiquetaJugador, etiquetaEstado, etiquetaBanderas, etiquetaTiempo}) {
        QFont fuenteEstado = etiqueta->font();
        fuenteEstado.setPointSize(10);
        fuenteEstado.setBold(true);
        etiqueta->setFont(fuenteEstado);
        etiqueta->setStyleSheet("color: #2c3e50;");
    }

    IndicadorIcono *iconoMina=new IndicadorIcono(TipoIcono::Mina,panelEncabezado);
    IndicadorIcono *iconoBandera=new IndicadorIcono(TipoIcono::Bandera,panelEncabezado);

    layoutEncabezado->addWidget(etiquetaJugador);
    layoutEncabezado->addStretch();
    layoutEncabezado->addWidget(iconoMina);
    layoutEncabezado->addWidget(etiquetaEstado);
    layoutEncabezado->addSpacing(15);
    layoutEncabezado->addWidget(iconoBandera);
    layoutEncabezado->addWidget(etiquetaBanderas);
    layoutEncabezado->addStretch();
    layoutEncabezado->addWidget(etiquetaTiempo);

    escena = new QGraphicsScene(this);
    vista = new VistaJuego(this);
    vista->setScene(escena);
    vista->setTamanioCelda(tamanioCelda);
    vista->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    vista->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    vista->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QPushButton *botonVolver = new QPushButton("VOLVER AL MENU", this);
    botonVolver->setStyleSheet("background-color: #7f8c8d; color: white; border-radius: 6px; padding: 8px;");
    connect(botonVolver, &QPushButton::clicked, this, [this]() {
        cronometro.detener();
        emit volverSolicitado();
    });

    layoutPrincipal->addWidget(panelEncabezado);
    layoutPrincipal->addWidget(vista, 1);
    layoutPrincipal->addWidget(botonVolver);

    connect(vista, &VistaJuego::celdaClicIzquierdo, this, &VentanaJuego::manejarClicIzquierdo);
    connect(vista, &VistaJuego::celdaClicDerecho, this, &VentanaJuego::manejarClicDerecho);
    connect(&cronometro, &Cronometro::tiempoActualizado, this, &VentanaJuego::actualizarTiempo);

    construirCeldasGraficas();
    dibujarTablero();

    cronometro.iniciar();
}

VentanaJuego::~VentanaJuego()
{
    delete[] celdasGraficas;
    delete tablero;
}

void VentanaJuego::setNombreJugador(const QString &nombre)
{
    nombreJugador = nombre;
    etiquetaJugador->setText(QString("Jugador: %1").arg(nombre));
}

void VentanaJuego::setGestorAudio(GestorAudio *audio)
{
    gestorAudio = audio;
}

int VentanaJuego::getSegundosTranscurridos() const
{
    return cronometro.getSegundosTranscurridos();
}

int VentanaJuego::getBanderasColocadas() const
{
    return tablero->getBanderasColocadas();
}

void VentanaJuego::construirCeldasGraficas()
{
    int filas = tablero->getFilas();
    int columnas = tablero->getColumnas();

    celdasGraficas = new celdagrafica*[filas * columnas];

    for (int fila = 0; fila < filas; fila++) {
        for (int columna = 0; columna < columnas; columna++) {
            int indice = fila * columnas + columna;
            celdagrafica *item = new celdagrafica(fila, columna, tamanioCelda);
            item->setPos(columna * tamanioCelda, fila * tamanioCelda);
            item->setAcceptedMouseButtons(Qt::NoButton);
            escena->addItem(item);
            celdasGraficas[indice] = item;
        }
    }

    escena->setSceneRect(0, 0, columnas * tamanioCelda, filas * tamanioCelda);
}

void VentanaJuego::dibujarTablero()
{
    int filas = tablero->getFilas();
    int columnas = tablero->getColumnas();

    for (int fila = 0; fila < filas; fila++) {
        for (int columna = 0; columna < columnas; columna++) {
            int indice = fila * columnas + columna;
            Celda &celda = tablero->obtenerCelda(fila, columna);
            celdasGraficas[indice]->actualizarDesdeCelda(celda);
        }
    }

    if (!partidaTerminada) {
        etiquetaEstado->setText(QString("Minas: %1").arg(tablero->getCantidadMinas()));
        etiquetaBanderas->setText(QString("Banderas: %1").arg(tablero->getCantidadMinas() - tablero->getBanderasColocadas()));
    }
}

void VentanaJuego::manejarClicIzquierdo(int fila, int columna)
{
    if (partidaTerminada || !tablero->estaDentroDelTablero(fila, columna)){
        return;
    }
    int celdasSinAbrirAntes = (tablero->getFilas() * tablero->getColumnas()) - tablero->getCeldasReveladas();
    int minasRestantesAntes = tablero->getCantidadMinas() - tablero->getBanderasColocadas();
    double probabilidadMinaAntes = celdasSinAbrirAntes > 0
                                       ? static_cast<double>(minasRestantesAntes) / celdasSinAbrirAntes
                                       : 0.0;
    tablero->abrirCelda(fila, columna);
    dibujarTablero();
    if (tablero->juegoPerdido()) {
        finalizarPartida(false);
        return;
    }
    if (!jugadaArriesgadaDetectada && probabilidadMinaAntes >= 0.40 && probabilidadMinaAntes <= 0.60) {
        jugadaArriesgadaDetectada = true;
    }
    if (tablero->juegoGanado()) {
        finalizarPartida(true);
    }
}

void VentanaJuego::manejarClicDerecho(int fila, int columna)
{
    if (partidaTerminada || !tablero->estaDentroDelTablero(fila, columna)) {
        return;
    }

    // el sonido de bandera solo suena si se va a colocar una (celda cerrada y sin bandera)
    Celda &celda = tablero->obtenerCelda(fila, columna);
    if (gestorAudio && !celda.estaRevelada() && !celda.tieneBandera()) {
        gestorAudio->reproducirBandera();
    }

    tablero->alternarBandera(fila, columna);
    dibujarTablero();
}

void VentanaJuego::actualizarTiempo(int segundos)
{
    etiquetaTiempo->setText(QString("Tiempo: %1s").arg(segundos));
}

void VentanaJuego::finalizarPartida(bool gano)
{
    partidaTerminada = true;
    cronometro.detener();
    etiquetaEstado->setText(gano ? "¡GANASTE!" : "Perdiste");

    if (gano) {
        int segundos = cronometro.getSegundosTranscurridos();
        int banderas = tablero->getBanderasColocadas();
        int minas = tablero->getCantidadMinas();
        QString dificultadTexto = QString("%1x%2").arg(tablero->getFilas()).arg(tablero->getColumnas());
        QString medalla = determinarMedalla();

        GestorMedallas gestorMedallas;
        bool medallaOtorgada = gestorMedallas.otorgarMedalla(nombreJugador.toStdString(), medalla.toStdString());

        QString medallaParaGuardar = medallaOtorgada ? medalla : "Ninguna";

        QString textoMedalla = medallaOtorgada
                                   ? QString("Medalla obtenida: %1").arg(medalla)
                                   : QString("Todavía no desbloqueaste la medalla %1 (completá el nivel anterior primero)").arg(medalla);

        //Medalla por la jugada 50/50 si es detectada
        if (jugadaArriesgadaDetectada) {
            gestorMedallas.otorgarMedalla(nombreJugador.toStdString(), "Valiente");
        }

        //El puntaje se maneja: mayor dificultad (mas minas) mas puntos base, mientras mas rapido menos penalización
        int puntaje = (minas * 100) - (segundos * 2);
        if (puntaje < 10) puntaje = 10;

        GestorPuntajes gestorPuntajes;
        gestorPuntajes.guardarPuntaje(nombreJugador.toStdString(), segundos, dificultadTexto.toStdString(),
                                      medallaParaGuardar.toStdString(), puntaje);

        int filas = tablero->getFilas(), columnas = tablero->getColumnas();
        bool haySiguiente = true;
        int filasSig = 0, columnasSig = 0, minasSig = 0;
        if (filas == 8 && columnas == 8 && minas == 10) { filasSig = 16; columnasSig = 16; minasSig = 40; }
        else if (filas == 16 && columnas == 16 && minas == 40) { filasSig = 16; columnasSig = 30; minasSig = 99; }
        else { haySiguiente = false; }

        emit victoriaObtenida(segundos, banderas, textoMedalla, haySiguiente, filasSig, columnasSig, minasSig);
    } else {
        if (gestorAudio) {
            gestorAudio->reproducirExplosion();
        }
        emit derrotaObtenida(tablero->getFilas(), tablero->getColumnas(), tablero->getCantidadMinas());
    }
}
QString VentanaJuego::determinarMedalla() const{
    int filas,columnas,minas;
    filas=tablero->getFilas();
    columnas=tablero->getColumnas();
    minas=tablero->getCantidadMinas();
    if(filas==8 && columnas==8 && minas==10){
        return "Bronce";
    }
    if(filas==16 && columnas==16 && minas==40){
        return "Plata";
    }
    if(filas==16 && columnas==30 && minas==99){
        return "Oro";
    }
    return "Diamante"; //para nivel personalizado
}