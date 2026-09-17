#include "ventanalogin.h"
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFont>
#include <QFile>
#include <QTextStream>
#include <QCoreApplication>
#include <QDir>

VentanaLogin::VentanaLogin(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *layoutPrincipal = new QVBoxLayout(this);
    layoutPrincipal->setContentsMargins(40, 30, 40, 30);
    layoutPrincipal->setSpacing(12);

    QLabel *etiquetaTitulo = new QLabel("INICIAR SESIÓN", this);
    QFont fuenteTitulo = etiquetaTitulo->font();
    fuenteTitulo.setPointSize(18);
    fuenteTitulo.setBold(true);
    etiquetaTitulo->setFont(fuenteTitulo);
    etiquetaTitulo->setAlignment(Qt::AlignCenter);

    campoUsuario = new QLineEdit(this);
    campoUsuario->setPlaceholderText("Nombre de usuario");
    campoContrasena = new QLineEdit(this);
    campoContrasena->setPlaceholderText("Contraseña");
    campoContrasena->setEchoMode(QLineEdit::Password);

    etiquetaError = new QLabel(this);
    etiquetaError->setStyleSheet("color: #e74c3c;");
    etiquetaError->setWordWrap(true);
    etiquetaError->setAlignment(Qt::AlignCenter);
    etiquetaError->hide();

    QPushButton *botonMostrarContrasena = new QPushButton("Mostrar contraseña", this);
    botonMostrarContrasena->setCheckable(true);
    QPushButton *botonIngresar = new QPushButton("INGRESAR", this);
    QPushButton *botonIrARegistro = new QPushButton("¿No tenés cuenta? Regístrate", this);
    QPushButton *botonSalir=new QPushButton("SALIR",this);

    for (QLineEdit *campo : {campoUsuario, campoContrasena}) {
        campo->setMinimumHeight(40);
    }
    botonIngresar->setMinimumHeight(50);
    botonSalir->setMinimumHeight(50);

    botonIngresar->setStyleSheet("background-color: #2ecc71; color: white; border-radius: 6px;");
    botonIrARegistro->setStyleSheet("background-color: transparent; color: #3498db; border: none;");
    botonSalir->setStyleSheet("background-color: #e74c3c; color: white; border-radius: 6px");

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

    layoutPrincipal->addStretch();
    layoutPrincipal->addWidget(etiquetaTitulo);
    layoutPrincipal->addSpacing(10);
    layoutPrincipal->addWidget(campoUsuario);
    layoutPrincipal->addWidget(campoContrasena);
    layoutPrincipal->addWidget(botonMostrarContrasena);
    layoutPrincipal->addSpacing(10);
    layoutPrincipal->addWidget(etiquetaError);
    layoutPrincipal->addWidget(botonIngresar);
    layoutPrincipal->addWidget(botonIrARegistro);
    layoutPrincipal->addSpacing(10);
    layoutPrincipal->addWidget(botonSalir);
    layoutPrincipal->addStretch();
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
    // Mismo archivo y mismo formato
    QFile archivo(QDir(QCoreApplication::applicationDirPath()).filePath("usuarios.txt"));
    if (!archivo.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return false;
    }

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
        if (usuarioGuardado == usuario && contrasenaGuardada == contrasena) {
            encontrado = true;
        }
    }
    archivo.close();
    return encontrado;
}