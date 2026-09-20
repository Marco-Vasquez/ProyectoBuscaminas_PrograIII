#include "ventanalogin.h"
#include "estilos.h"
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFrame>
#include <QFont>
#include <QFile>
#include <QTextStream>
#include <QCryptographicHash>
#include <QCoreApplication>
#include <QDir>


static QString hashContrasena(const QString &contra){
    QByteArray hash=QCryptographicHash::hash(contra.toUtf8(),QCryptographicHash::Sha256);
    return QString::fromLatin1(hash.toHex());
}

VentanaLogin::VentanaLogin(QWidget *parent) : QWidget(parent)
{
    setStyleSheet(Estilos::fondoPantalla());

    QVBoxLayout *layoutPrincipal = new QVBoxLayout(this);
    layoutPrincipal->setContentsMargins(60, 40, 60, 40);
    layoutPrincipal->setSpacing(12);

    // saludo grande al entrar
    QLabel *etiquetaSaludo = new QLabel("¡Bienvenido!", this);
    etiquetaSaludo->setStyleSheet(Estilos::titulo(30));
    etiquetaSaludo->setAlignment(Qt::AlignCenter);

    QLabel *etiquetaSubtitulo = new QLabel("Iniciá sesión para jugar", this);
    etiquetaSubtitulo->setStyleSheet(Estilos::textoSuave(13));
    etiquetaSubtitulo->setAlignment(Qt::AlignCenter);

    // tarjeta con el formulario
    QFrame *tarjeta = new QFrame(this);
    tarjeta->setStyleSheet(Estilos::tarjeta());
    QVBoxLayout *layoutTarjeta = new QVBoxLayout(tarjeta);
    layoutTarjeta->setContentsMargins(24, 24, 24, 24);
    layoutTarjeta->setSpacing(12);

    campoUsuario = new QLineEdit(tarjeta);
    campoUsuario->setPlaceholderText("Nombre de usuario");
    campoContrasena = new QLineEdit(tarjeta);
    campoContrasena->setPlaceholderText("Contraseña");
    campoContrasena->setEchoMode(QLineEdit::Password);
    for (QLineEdit *campo : {campoUsuario, campoContrasena}) {
        campo->setMinimumHeight(44);
        campo->setStyleSheet(Estilos::campoTexto());
    }

    etiquetaError = new QLabel(tarjeta);
    etiquetaError->setStyleSheet("color: #e74c3c; font-size: 12px;");
    etiquetaError->setWordWrap(true);
    etiquetaError->setAlignment(Qt::AlignCenter);
    etiquetaError->hide();

    QPushButton *botonMostrarContrasena = new QPushButton("Mostrar contraseña", tarjeta);
    botonMostrarContrasena->setCheckable(true);
    botonMostrarContrasena->setStyleSheet(
        "QPushButton { background: transparent; color: #3498db; border: none; font-size: 12px; }"
        "QPushButton:hover { color: #5dade2; }");

    QPushButton *botonIngresar = new QPushButton("INGRESAR", tarjeta);
    botonIngresar->setMinimumHeight(50);
    botonIngresar->setStyleSheet(Estilos::boton(Estilos::VERDE));

    QPushButton *botonIrARegistro = new QPushButton("¿No tenés cuenta? Regístrate", tarjeta);
    botonIrARegistro->setStyleSheet(
        "QPushButton { background: transparent; color: #3498db; border: none; font-size: 12px; }"
        "QPushButton:hover { color: #5dade2; }");

    QPushButton *botonSalir = new QPushButton("SALIR", this);
    botonSalir->setMinimumHeight(50);
    botonSalir->setStyleSheet(Estilos::boton(Estilos::ROJO));

    connect(botonMostrarContrasena, &QPushButton::toggled, this, [this, botonMostrarContrasena](bool marcado) {
        campoContrasena->setEchoMode(marcado ? QLineEdit::Normal : QLineEdit::Password);
        botonMostrarContrasena->setText(marcado ? "Ocultar contraseña" : "Mostrar contraseña");
    });

    connect(botonIngresar, &QPushButton::clicked, this, [this]() {
        QString usuario = campoUsuario->text().trimmed();
        QString contrasena = campoContrasena->text();

        if (usuario.isEmpty() || contrasena.isEmpty()) {
            etiquetaError->setText("Debés ingresar usuario y contraseña.");
            etiquetaError->show();
            return;
        }

        if (!validarCredenciales(usuario, contrasena)) {
            etiquetaError->setText("Usuario o contraseña incorrectos.");
            etiquetaError->show();
            return;
        }

        etiquetaError->hide();
        campoContrasena->clear();
        emit loginExitoso(usuario);
    });

    connect(botonIrARegistro, &QPushButton::clicked, this, [this]() { emit registroSolicitado(); });
    connect(botonSalir, &QPushButton::clicked, this, [this]() { emit salirSolicitado(); });

    layoutTarjeta->addWidget(campoUsuario);
    layoutTarjeta->addWidget(campoContrasena);
    layoutTarjeta->addWidget(botonMostrarContrasena);
    layoutTarjeta->addWidget(etiquetaError);
    layoutTarjeta->addWidget(botonIngresar);
    layoutTarjeta->addWidget(botonIrARegistro);

    layoutPrincipal->addStretch();
    layoutPrincipal->addWidget(etiquetaSaludo);
    layoutPrincipal->addWidget(etiquetaSubtitulo);
    layoutPrincipal->addSpacing(16);
    layoutPrincipal->addWidget(tarjeta);
    layoutPrincipal->addStretch();
    layoutPrincipal->addWidget(botonSalir);
    layoutPrincipal->addSpacing(8);
}

VentanaLogin::~VentanaLogin() {}

void VentanaLogin::sugerirUsuario(const QString &nombreUsuario)
{
    campoUsuario->setText(nombreUsuario);
    campoContrasena->clear();
    campoContrasena->setFocus();
}

void VentanaLogin::limpiarCampos()
{
    campoUsuario->clear();
    campoContrasena->clear();
    etiquetaError->hide();
}

bool VentanaLogin::validarCredenciales(const QString &usuario, const QString &contrasena) const
{
    QString ruta = QDir(QCoreApplication::applicationDirPath()).filePath("usuarios.txt");
    QFile archivo(ruta);
    if (!archivo.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return false;
    }

    QString contrasenaHasheada = hashContrasena(contrasena);

    QTextStream flujo(&archivo);
    bool encontrado = false;
    while (!flujo.atEnd() && !encontrado) {
        QString linea = flujo.readLine();
        int posicionEspacio = linea.indexOf(' ');
        if (posicionEspacio == -1) {
            continue;
        }
        QString usuarioGuardado = linea.left(posicionEspacio);
        QString contrasenaGuardada = linea.mid(posicionEspacio + 1);
        if (usuarioGuardado == usuario && contrasenaGuardada == contrasenaHasheada) {
            encontrado = true;
        }
    }
    archivo.close();
    return encontrado;
}
