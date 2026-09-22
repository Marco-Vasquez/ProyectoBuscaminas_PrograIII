#include "buscaminasmain.h"
#include "seleccionardificultad.h"
#include "registrousuario.h"
#include "ventanajuego.h"
#include "ventanarecords.h"
#include "ventanalogin.h"
#include "ventanavictoria.h"
#include "ventanaderrota.h"
#include "ventanaopciones.h"
#include "ventanaayuda.h"
#include "gestormedallas.h"
#include "gestoraudio.h"
#include "estilos.h"
#include "medallaimagen.h"
#include "ventanaayuda.h"
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFrame>
#include <QWidget>
#include <QStackedWidget>
#include <QFont>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsProxyWidget>
#include <QResizeEvent>
#include <QPainter>
#include <QColor>
#include <QTimer>
#include <QShortcut>
#include <QKeySequence>
#include <QApplication>
#include <QSettings>

BuscaminasMain::BuscaminasMain(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle("Buscaminas - Menú Principal");

    resize(720, 580);
    setMinimumSize(480, 380);


    panelPrincipal = new QStackedWidget;
    panelPrincipal->setAutoFillBackground(true);
    QPalette paletaPanel = panelPrincipal->palette();
    paletaPanel.setColor(QPalette::Window, QColor(Estilos::FONDO));
    panelPrincipal->setPalette(paletaPanel);
    escenaUI = new QGraphicsScene(this);
    proxyUI = escenaUI->addWidget(panelPrincipal);
    proxyUI->setGeometry(QRectF(0, 0, 720, 580)); // tamaño base fijo de la interfaz

    escenaUI->setSceneRect(0, 0, 720, 580);
    vistaUI = new QGraphicsView(escenaUI, this);
    vistaUI->setFrameShape(QFrame::NoFrame);
    vistaUI->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    vistaUI->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    vistaUI->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    vistaUI->setBackgroundBrush(QColor(Estilos::FONDO));

    // primer nivel de páginas: la interfaz de menús (720x580 fija) y,
    // encima, la partida que ocupa toda la ventana
    contenedorPrincipal = new QStackedWidget(this);
    contenedorPrincipal->addWidget(vistaUI);
    setCentralWidget(contenedorPrincipal);
    panelPrincipal->setFixedSize(720, 580);

    // Menú principal
    pantallaMenu = new QWidget(panelPrincipal);
    pantallaMenu->setStyleSheet(Estilos::fondoPantalla());
    QVBoxLayout *layoutPrincipal = new QVBoxLayout(pantallaMenu);
    layoutPrincipal->setContentsMargins(50, 20, 50, 20);
    layoutPrincipal->setSpacing(10);
    QLabel *etiquetaTitulo = new QLabel("BUSCAMINAS", pantallaMenu);
    etiquetaTitulo->setStyleSheet(Estilos::titulo(30));
    etiquetaTitulo->setAlignment(Qt::AlignCenter);
    etiquetaSesion = new QLabel(pantallaMenu);
    etiquetaSesion->setAlignment(Qt::AlignCenter);
    etiquetaSesion->setStyleSheet(Estilos::texto(16));
    layoutPrincipal->addWidget(etiquetaSesion);

    // medallas del jugador: tarjetas con el PNG real de cada medalla
    QHBoxLayout *layoutMedallas = new QHBoxLayout();
    layoutMedallas->setSpacing(10);
    QWidget *contenedorMedallas = new QWidget(pantallaMenu);
    contenedorMedallas->setMinimumWidth(620);
    contenedorMedallas->setMaximumWidth(620);
    etiquetaIconoBronce = new QLabel(pantallaMenu);
    etiquetaIconoPlata = new QLabel(pantallaMenu);
    etiquetaIconoOro = new QLabel(pantallaMenu);
    etiquetaIconoDiamante = new QLabel(pantallaMenu);
    etiquetaIconoValiente=new QLabel(pantallaMenu);
    etiquetaMedallaBronce = new QLabel("BRONCE", pantallaMenu);
    etiquetaMedallaPlata = new QLabel("PLATA", pantallaMenu);
    etiquetaMedallaOro = new QLabel("ORO", pantallaMenu);
    etiquetaMedallaDiamante = new QLabel("DIAMANTE", pantallaMenu);
    etiquetaMedallaValiente=new QLabel("VALIENTE",pantallaMenu);
    struct { QLabel *icono; QLabel *nombre; } medallas[] = {
                     {etiquetaIconoBronce, etiquetaMedallaBronce},
                     {etiquetaIconoPlata, etiquetaMedallaPlata},
                     {etiquetaIconoOro, etiquetaMedallaOro},
                     {etiquetaIconoDiamante, etiquetaMedallaDiamante},
                     {etiquetaIconoValiente, etiquetaMedallaValiente},
                     };
    for (auto &m : medallas) {
        QFrame *tarjetaMedalla = new QFrame(pantallaMenu);
        tarjetaMedalla->setStyleSheet(Estilos::tarjeta());
        QVBoxLayout *layoutMedalla = new QVBoxLayout(tarjetaMedalla);
        layoutMedalla->setContentsMargins(10, 10, 10, 8);
        layoutMedalla->setSpacing(4);
        m.icono->setFixedSize(44, 44);
        m.icono->setAlignment(Qt::AlignCenter);
        m.nombre->setAlignment(Qt::AlignCenter);
        m.nombre->setStyleSheet("color: #5d6d6e; font-weight: bold; font-size: 10px;");
        layoutMedalla->addWidget(m.icono);
        layoutMedalla->addWidget(m.nombre);
        layoutMedallas->addWidget(tarjetaMedalla);
    }
    contenedorMedallas->setLayout(layoutMedallas);
    QPushButton *botonJugar = new QPushButton("JUGAR", pantallaMenu);
    QPushButton *botonRecords = new QPushButton("RÉCORDS", pantallaMenu);
    QPushButton *botonOpciones = new QPushButton("OPCIONES", pantallaMenu);
    QPushButton *botonAyuda=new QPushButton("AYUDA",pantallaMenu);
    QPushButton *botonCerrarSesion = new QPushButton("CERRAR SESIÓN", pantallaMenu);
    QPushButton *botonSalir = new QPushButton("SALIR", pantallaMenu);
    botonJugar->setMinimumHeight(55);
    botonJugar->setStyleSheet(Estilos::boton(Estilos::VERDE));
    botonRecords->setMinimumHeight(50);
    botonRecords->setStyleSheet(Estilos::boton(Estilos::MORADO));
    botonOpciones->setMinimumHeight(50);
    botonOpciones->setStyleSheet(Estilos::boton(Estilos::TURQUESA));
    botonAyuda->setMinimumHeight(40); // más chico para que el menú entre en 580 px
    botonAyuda->setStyleSheet(Estilos::boton(Estilos::AZUL));
    botonCerrarSesion->setMinimumHeight(50);
    botonCerrarSesion->setStyleSheet(Estilos::boton(Estilos::NARANJA));
    botonSalir->setMinimumHeight(50);
    botonSalir->setStyleSheet(Estilos::boton(Estilos::ROJO));
    for (QPushButton *b : {botonJugar, botonRecords, botonOpciones, botonAyuda, botonCerrarSesion, botonSalir}) {
        b->setMinimumWidth(620);
        b->setMaximumWidth(620);
    }
    layoutPrincipal->addWidget(etiquetaTitulo);
    layoutPrincipal->addWidget(contenedorMedallas, 0, Qt::AlignHCenter);
    layoutPrincipal->addStretch();
    layoutPrincipal->addWidget(botonJugar, 0, Qt::AlignHCenter);
    layoutPrincipal->addWidget(botonRecords, 0, Qt::AlignHCenter);
    layoutPrincipal->addWidget(botonOpciones, 0, Qt::AlignHCenter);
    layoutPrincipal->addWidget(botonAyuda, 0, Qt::AlignHCenter);
    layoutPrincipal->addWidget(botonCerrarSesion, 0, Qt::AlignHCenter);
    layoutPrincipal->addWidget(botonSalir, 0, Qt::AlignHCenter);
    layoutPrincipal->addStretch();

    ventanaLogin = new VentanaLogin(panelPrincipal);
    ventanaSeleccionDificultad = new SeleccionarDificultad(panelPrincipal);
    ventanaRegistroUsuario = new RegistroUsuario(panelPrincipal);
    ventanaRecords = new VentanaRecords(panelPrincipal);
    ventanaVictoria = new VentanaVictoria(panelPrincipal);
    ventanaDerrota = new VentanaDerrota(panelPrincipal);
    gestorAudio = new GestorAudio(this);
    ventanaOpciones = new VentanaOpciones(gestorAudio, panelPrincipal);
    ventanaAyuda=new VentanaAyuda(panelPrincipal);

    panelPrincipal->addWidget(ventanaLogin);
    panelPrincipal->addWidget(pantallaMenu);
    panelPrincipal->addWidget(ventanaSeleccionDificultad);
    panelPrincipal->addWidget(ventanaRegistroUsuario);
    panelPrincipal->addWidget(ventanaRecords);
    panelPrincipal->addWidget(ventanaVictoria);
    panelPrincipal->addWidget(ventanaDerrota);
    panelPrincipal->addWidget(ventanaOpciones);
    panelPrincipal->addWidget(ventanaAyuda);

    //login es punto de entrada antes de llegar al menú.
    panelPrincipal->setCurrentWidget(ventanaLogin);

    connect(botonJugar, &QPushButton::clicked, this, [this]() {
        GestorMedallas gestorMedallas;
        std::string usuario = nombreUsuarioActual.toStdString();
        bool medioDesbloqueado = gestorMedallas.tieneMedalla(usuario, "Bronce");
        bool dificilDesbloqueado = gestorMedallas.tieneMedalla(usuario, "Plata");
        ventanaSeleccionDificultad->actualizarNivelesDesbloqueados(medioDesbloqueado, dificilDesbloqueado);
        panelPrincipal->setCurrentWidget(ventanaSeleccionDificultad);
    });
    connect(botonRecords, &QPushButton::clicked, this, [this]() { panelPrincipal->setCurrentWidget(ventanaRecords); });
    connect(botonOpciones, &QPushButton::clicked, this, [this]() {
        // refresca los sliders con los niveles reales (si se muteó en
        // partida mostraban valores viejos y no había forma de desmutear)
        ventanaOpciones->sincronizarValores();
        panelPrincipal->setCurrentWidget(ventanaOpciones);
    });
    connect(ventanaOpciones, &VentanaOpciones::volverSolicitado, this, [this]() { mostrarMenu(); });

    // cada cambio de mute se recuerda para el usuario actual
    connect(gestorAudio, &GestorAudio::muteCambiado, this, [this](bool silenciado) {
        guardarPreferenciaMute(silenciado);
    });
    connect(panelPrincipal, &QStackedWidget::currentChanged, this, [this](int) {
        QWidget *actual = panelPrincipal->currentWidget();
        if (actual == pantallaMenu) {
            setWindowTitle("Buscaminas - Menú Principal");
            actualizarMedallas();
            etiquetaSesion->setText(QString("¡Hola, %1!").arg(nombreUsuarioActual));
            gestorAudio->iniciarMusicaMenu();
        } else if (actual == ventanaLogin) {
            setWindowTitle("Buscaminas - Iniciar Sesión");
            gestorAudio->detenerMusica();
        } else if (actual == ventanaDerrota || actual == ventanaVictoria) {
            setWindowTitle(actual == ventanaVictoria ? "Buscaminas - ¡Victoria!" : "Buscaminas - Derrota");
            gestorAudio->detenerMusica();
        } else if (actual == ventanaSeleccionDificultad) {
            setWindowTitle("Buscaminas - Seleccionar Dificultad");
        } else if (actual == ventanaRegistroUsuario) {
            setWindowTitle("Buscaminas - Registro");
        } else if (actual == ventanaRecords) {
            setWindowTitle("Buscaminas - Récords");
        } else if (actual == ventanaOpciones) {
            setWindowTitle("Buscaminas - Opciones");
        } else if (actual == ventanaAyuda) {
            setWindowTitle("Buscaminas - Ayuda");
        }
    });
    connect(botonAyuda,&QPushButton::clicked,this,[this](){
        panelPrincipal->setCurrentWidget(ventanaAyuda);
    });
    connect(ventanaAyuda,&VentanaAyuda::volverSolicitado,this,[this](){
        mostrarMenu();
    });
    connect(ventanaVictoria, &VentanaVictoria::volverSolicitado, this, [this]() { mostrarMenu(); });
    connect(ventanaVictoria, &VentanaVictoria::siguienteNivelSolicitado, this, [this]() {
        int filas = ventanaVictoria->property("filasSig").toInt();
        int columnas = ventanaVictoria->property("columnasSig").toInt();
        int minas = ventanaVictoria->property("minasSig").toInt();
        abrirPartida(filas, columnas, minas);
    });
    connect(ventanaDerrota, &VentanaDerrota::volverSolicitado, this, [this]() { mostrarMenu(); });
    connect(ventanaDerrota, &VentanaDerrota::reintentarSolicitado, this, [this]() {
        int filas = ventanaDerrota->property("filasReintento").toInt();
        int columnas = ventanaDerrota->property("columnasReintento").toInt();
        int minas = ventanaDerrota->property("minasReintento").toInt();
        abrirPartida(filas, columnas, minas);
    });
    connect(botonCerrarSesion, &QPushButton::clicked, this, [this]() {
        cerrarPantallaPartida();
        nombreUsuarioActual = "Jugador";
        aplicarPreferenciaMute(nombreUsuarioActual);
        ventanaLogin->limpiarCampos();
        panelPrincipal->setCurrentWidget(ventanaLogin);
    });
    connect(botonSalir, &QPushButton::clicked, this, &QMainWindow::close);

    connect(ventanaSeleccionDificultad, &SeleccionarDificultad::volverSolicitado, this, [this]() { mostrarMenu(); });
    connect(ventanaSeleccionDificultad, &SeleccionarDificultad::dificultadSeleccionada, this,
            [this](int cantidadFilas, int cantidadColumnas, int cantidadMinas) {
                abrirPartida(cantidadFilas, cantidadColumnas, cantidadMinas);
            });

    connect(ventanaRecords, &VentanaRecords::volverSolicitado, this, [this]() { mostrarMenu(); });

    // pantalla completa estilo borderless: Alt+Enter (o Alt+Return) alterna,
    // Escape sale; también hay un checkbox en Opciones
    QShortcut *atajoFullscreen1 = new QShortcut(QKeySequence("Alt+Return"), this);
    QShortcut *atajoFullscreen2 = new QShortcut(QKeySequence("Alt+Enter"), this);
    connect(atajoFullscreen1, &QShortcut::activated, this, [this]() { setPantallaCompleta(!isFullScreen()); });
    connect(atajoFullscreen2, &QShortcut::activated, this, [this]() { setPantallaCompleta(!isFullScreen()); });
    QShortcut *atajoSalirFullscreen = new QShortcut(QKeySequence(Qt::Key_Escape), this);
    connect(atajoSalirFullscreen, &QShortcut::activated, this, [this]() {
        // no robar el Escape de un popup abierto (p. ej. un combo)
        if (isFullScreen() && !QApplication::activePopupWidget()) {
            setPantallaCompleta(false);
        }
    });

    //al entrar correctamente se guarda el usuario y pasa al menú
    connect(ventanaLogin, &VentanaLogin::loginExitoso, this, [this](QString nombreUsuario) {
        nombreUsuarioActual = nombreUsuario;
        aplicarPreferenciaMute(nombreUsuarioActual);
        mostrarMenu();
    });
    connect(ventanaLogin, &VentanaLogin::registroSolicitado, this, [this]() {
        panelPrincipal->setCurrentWidget(ventanaRegistroUsuario);
    });

    connect(ventanaLogin, &VentanaLogin::salirSolicitado, this, &QMainWindow::close);

    connect(ventanaRegistroUsuario, &RegistroUsuario::volverSolicitado, this, [this]() {
        panelPrincipal->setCurrentWidget(ventanaLogin);
    });
    connect(ventanaRegistroUsuario, &RegistroUsuario::registroCompletado, this, [this](QString nombreUsuario) {
        nombreUsuarioActual = nombreUsuario;
        aplicarPreferenciaMute(nombreUsuarioActual);
        mostrarMenu();
    });
}
void BuscaminasMain::actualizarMedallas(){
    GestorMedallas gestorMedallas;
    std::string usuario=nombreUsuarioActual.toStdString();
    struct { QLabel *icono; QLabel *nombre; const char *tipo; } medallas[] = {
                     {etiquetaIconoBronce, etiquetaMedallaBronce, "Bronce"},
                     {etiquetaIconoPlata, etiquetaMedallaPlata, "Plata"},
                     {etiquetaIconoOro, etiquetaMedallaOro, "Oro"},
                     {etiquetaIconoDiamante, etiquetaMedallaDiamante, "Diamante"},
                     {etiquetaIconoValiente, etiquetaMedallaValiente, "Valiente"},
                     };
    for(auto &m:medallas){
        bool obtenida=gestorMedallas.tieneMedalla(usuario,m.tipo);
        m.icono->setPixmap(cargarMedallaPixmap(obtenida ? QString(m.tipo) : "Ninguna", 44));
        m.nombre->setStyleSheet(obtenida
                                    ? QString("color: %1; font-weight: bold; font-size: 10px;").arg(colorDeMedalla(m.tipo))
                                    : "color: #5d6d6e; font-weight: bold; font-size: 10px;");
    }
}
void BuscaminasMain::abrirPartida(int filas, int columnas, int minas)
{
    cerrarPantallaPartida();
    // el mute vive dentro de la partida: al entrar se restaura la
    // preferencia guardada de la cuenta (el menú siempre entra sin mute)
    aplicarPreferenciaMute(nombreUsuarioActual);
    ventanaJuego = new VentanaJuego(filas, columnas, minas, contenedorPrincipal);
    ventanaJuego->setNombreJugador(nombreUsuarioActual);
    ventanaJuego->setGestorAudio(gestorAudio);

    connect(ventanaJuego, &VentanaJuego::volverSolicitado, this, [this]() {
        mostrarMenu();
    });
    connect(ventanaJuego, &VentanaJuego::victoriaObtenida, this,
            [this](int segundos, int banderas, QString textoMedalla, bool haySiguiente, int filasSig, int columnasSig, int minasSig) {
                ventanaVictoria->setProperty("filasSig", filasSig);
                ventanaVictoria->setProperty("columnasSig", columnasSig);
                ventanaVictoria->setProperty("minasSig", minasSig);
                ventanaVictoria->mostrarResultado(segundos, banderas, textoMedalla, haySiguiente);
                // explícito: currentChanged no siempre dispara (p. ej. dos
                // victorias seguidas) y la música del juego quedaría sonando
                gestorAudio->detenerMusica();
                cerrarPantallaPartida();
                panelPrincipal->setCurrentWidget(ventanaVictoria);
            });
    connect(ventanaJuego, &VentanaJuego::derrotaObtenida, this,
            [this](int filas, int columnas, int minas) {
                int segundos = ventanaJuego->getSegundosTranscurridos();
                int banderas = ventanaJuego->getBanderasColocadas();
                ventanaDerrota->setProperty("filasReintento", filas);
                ventanaDerrota->setProperty("columnasReintento", columnas);
                ventanaDerrota->setProperty("minasReintento", minas);
                ventanaDerrota->mostrarResultado(segundos, banderas);
                // explícito: en derrotas consecutivas el panel ya muestra
                // derrota, currentChanged no dispara y la música seguía
                gestorAudio->detenerMusica();
                cerrarPantallaPartida();
                panelPrincipal->setCurrentWidget(ventanaDerrota);
            });

    contenedorPrincipal->addWidget(ventanaJuego);
    contenedorPrincipal->setCurrentWidget(ventanaJuego);
    setWindowTitle("Buscaminas - Partida");
    gestorAudio->iniciarMusicaJuego();
}

void BuscaminasMain::cerrarPantallaPartida()
{
    // vuelve a mostrar la interfaz de menús y libera la partida actual
    if (contenedorPrincipal) {
        contenedorPrincipal->setCurrentWidget(vistaUI);
    }
    if (ventanaJuego) {
        contenedorPrincipal->removeWidget(ventanaJuego);
        ventanaJuego->deleteLater();
        ventanaJuego = nullptr;
    }
    // NOTA: el mute NO se reinicia aquí a propósito: la preferencia se
    // recuerda entre partidas y por usuario (ver guardar/aplicarPreferenciaMute)
    // la vista de menús estuvo oculta durante la partida; al volver a
    // mostrarla se reajusta para que quede centrada y a escala correcta
    QTimer::singleShot(0, this, [this]() {
        if (vistaUI) {
            vistaUI->fitInView(QRectF(0, 0, 720, 580), Qt::KeepAspectRatio);
        }
    });
}

void BuscaminasMain::mostrarMenu()
{
    cerrarPantallaPartida();
    // el menú siempre suena: se quita el mute sin borrar la preferencia
    // (al abrir la próxima partida se vuelve a aplicar)
    desmutearSinGuardar();
    actualizarMedallas();
    etiquetaSesion->setText(QString("¡Hola, %1!").arg(nombreUsuarioActual));
    setWindowTitle("Buscaminas - Menú Principal");
    // la música del menú se retoma aquí y no solo en currentChanged:
    // al volver de una partida ese signal no dispara (la partida ya no
    // vive dentro de panelPrincipal) y quedaba sonando la música del juego
    gestorAudio->iniciarMusicaMenu();
    panelPrincipal->setCurrentWidget(pantallaMenu);
}

void BuscaminasMain::setPantallaCompleta(bool completa)
{
    if (completa == isFullScreen()) {
        return;
    }
    if (completa) {
        showFullScreen();
    } else {
        showNormal();
    }
}

void BuscaminasMain::guardarPreferenciaMute(bool silenciado)
{
    QSettings ajustes(QCoreApplication::applicationDirPath() + "/BuscaminasQt.ini",
                      QSettings::IniFormat);
    ajustes.setValue(QString("mute/%1").arg(nombreUsuarioActual), silenciado);
}

void BuscaminasMain::aplicarPreferenciaMute(const QString &usuario)
{
    QSettings ajustes(QCoreApplication::applicationDirPath() + "/BuscaminasQt.ini",
                      QSettings::IniFormat);
    bool silenciado = ajustes.value(QString("mute/%1").arg(usuario), false).toBool();
    if (gestorAudio) {
        gestorAudio->setMuteado(silenciado);
    }
}

void BuscaminasMain::desmutearSinGuardar()
{
    if (gestorAudio) {
        // blockSignals para que setMuteado no emita muteCambiado y no
        // se sobrescriba la preferencia guardada del usuario
        gestorAudio->blockSignals(true);
        gestorAudio->setMuteado(false);
        gestorAudio->blockSignals(false);
    }
}
BuscaminasMain::~BuscaminasMain() {}

void BuscaminasMain::resizeEvent(QResizeEvent *evento)
{
    QMainWindow::resizeEvent(evento);

    if (vistaUI) {
        vistaUI->fitInView(QRectF(0, 0, 720, 580), Qt::KeepAspectRatio);
        QTimer::singleShot(0, this, [this]() {
            if (vistaUI) {
                vistaUI->fitInView(QRectF(0, 0, 720, 580), Qt::KeepAspectRatio);
            }
        });
    }
}