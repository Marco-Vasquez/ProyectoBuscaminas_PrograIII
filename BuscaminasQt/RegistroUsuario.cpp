#include "registrousuario.h"
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QFont>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
RegistroUsuario::RegistroUsuario(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle("Buscaminas - Registro de Usuario");
    resize(700, 550);
    QWidget *widgetCentral = new QWidget(this);
    setCentralWidget(widgetCentral);
    QVBoxLayout *layoutPrincipal = new QVBoxLayout(widgetCentral);
    layoutPrincipal->setContentsMargins(40, 30, 40, 30);
    layoutPrincipal->setSpacing(12);
    QLabel *etiquetaTitulo = new QLabel("REGISTRO DE USUARIO", widgetCentral);
    QFont fuenteTitulo = etiquetaTitulo->font();
    fuenteTitulo.setPointSize(18);
    fuenteTitulo.setBold(true);
    etiquetaTitulo->setFont(fuenteTitulo);
    etiquetaTitulo->setAlignment(Qt::AlignCenter);
    QLineEdit *campoUsuario = new QLineEdit(widgetCentral);
    campoUsuario->setPlaceholderText("Nombre de usuario");
    QLineEdit *campoContrasena = new QLineEdit(widgetCentral);
    campoContrasena->setPlaceholderText("Contraseña");
    campoContrasena->setEchoMode(QLineEdit::Password);
    QPushButton *botonMostrarContrasena = new QPushButton("Mostrar contraseña", widgetCentral);
    botonMostrarContrasena->setCheckable(true);
    QPushButton *botonRegistrar = new QPushButton("REGISTRARSE", widgetCentral);
    QPushButton *botonVolver = new QPushButton("← VOLVER", widgetCentral);
    for (QLineEdit *campo : {campoUsuario, campoContrasena}) campo->setMinimumHeight(40);
    for (QPushButton *boton : {botonRegistrar, botonVolver}) boton->setMinimumHeight(50);
    botonRegistrar->setStyleSheet("background-color: #2ecc71; color: white; border-radius: 6px;");
    botonVolver->setStyleSheet("background-color: #95a5a6; color: white; border-radius: 6px;");
    connect(botonMostrarContrasena, &QPushButton::toggled, this, [campoContrasena, botonMostrarContrasena](bool marcado) {
        campoContrasena->setEchoMode(marcado ? QLineEdit::Normal : QLineEdit::Password);
        botonMostrarContrasena->setText(marcado ? "Ocultar contraseña" : "Mostrar contraseña");
    });
    connect(botonRegistrar, &QPushButton::clicked, this, [this, campoUsuario, campoContrasena]() {
        QString nombreUsuario = campoUsuario->text().trimmed();
        QString contrasena = campoContrasena->text();
        if (nombreUsuario.isEmpty() || contrasena.isEmpty()) {
            QMessageBox::warning(this, "Campos incompletos", "Debés ingresar usuario y contraseña.");
            return;
        }
        QFile archivo("usuarios.txt");
        if (archivo.open(QIODevice::Append | QIODevice::Text)) {
            QTextStream flujo(&archivo);
            flujo << nombreUsuario << " " << contrasena << "\n";
            archivo.close();
        }
        campoUsuario->clear();
        campoContrasena->clear();
        emit registroCompletado(nombreUsuario);
    });
    connect(botonVolver, &QPushButton::clicked, this, [this]() { emit volverSolicitado(); });
    layoutPrincipal->addWidget(etiquetaTitulo);
    layoutPrincipal->addSpacing(10);
    layoutPrincipal->addWidget(campoUsuario);
    layoutPrincipal->addWidget(campoContrasena);
    layoutPrincipal->addWidget(botonMostrarContrasena);
    layoutPrincipal->addSpacing(10);
    layoutPrincipal->addWidget(botonRegistrar);
    layoutPrincipal->addStretch();
    layoutPrincipal->addWidget(botonVolver);
}
RegistroUsuario::~RegistroUsuario() {}