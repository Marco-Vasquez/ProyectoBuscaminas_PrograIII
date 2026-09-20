#include "registrousuario.h"
#include "estilos.h"
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFrame>
#include <QFont>
#include <QFile>
#include <QTextStream>
#include <QCoreApplication>
#include <QCryptographicHash>
#include <QDir>
struct QString hashContrasena(const QString &contra){
    QByteArray hash=QCryptographicHash::hash(contra.toUtf8(),QCryptographicHash::Sha256);
    return QString::fromLatin1(hash.toHex());
}
RegistroUsuario::RegistroUsuario(QWidget *parent) : QWidget(parent)
{
    setStyleSheet(Estilos::fondoPantalla());

    QVBoxLayout *layoutPrincipal = new QVBoxLayout(this);
    layoutPrincipal->setContentsMargins(60, 40, 60, 40);
    layoutPrincipal->setSpacing(12);

    QLabel *etiquetaTitulo = new QLabel("REGISTRO DE USUARIO", this);
    etiquetaTitulo->setStyleSheet(Estilos::titulo(24));
    etiquetaTitulo->setAlignment(Qt::AlignCenter);

    QLabel *etiquetaSubtitulo = new QLabel("Creá tu cuenta para empezar a jugar", this);
    etiquetaSubtitulo->setStyleSheet(Estilos::textoSuave(13));
    etiquetaSubtitulo->setAlignment(Qt::AlignCenter);

    QFrame *tarjeta = new QFrame(this);
    tarjeta->setStyleSheet(Estilos::tarjeta());
    tarjeta->setMaximumWidth(460); // no se estira en pantallas anchas
    QVBoxLayout *layoutTarjeta = new QVBoxLayout(tarjeta);
    layoutTarjeta->setContentsMargins(24, 24, 24, 24);
    layoutTarjeta->setSpacing(12);

    QLineEdit *campoUsuario = new QLineEdit(tarjeta);
    campoUsuario->setPlaceholderText("Nombre de usuario");
    QLineEdit *campoContrasena = new QLineEdit(tarjeta);
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

    QPushButton *botonRegistrar = new QPushButton("REGISTRARSE", tarjeta);
    botonRegistrar->setMinimumHeight(50);
    botonRegistrar->setStyleSheet(Estilos::boton(Estilos::VERDE));

    QPushButton *botonVolver = new QPushButton("← VOLVER", this);
    botonVolver->setMinimumHeight(50);
    botonVolver->setStyleSheet(Estilos::botonSecundario());

    connect(botonMostrarContrasena, &QPushButton::toggled, this, [campoContrasena, botonMostrarContrasena](bool marcado) {
        campoContrasena->setEchoMode(marcado ? QLineEdit::Normal : QLineEdit::Password);
        botonMostrarContrasena->setText(marcado ? "Ocultar contraseña" : "Mostrar contraseña");
    });
    connect(botonRegistrar,&QPushButton::clicked,this,[this,campoUsuario,campoContrasena](){
        QString nombreUsuario=campoUsuario->text().trimmed();
        QString contrasena=campoContrasena->text();
        if(nombreUsuario.isEmpty() || contrasena.isEmpty()){
            etiquetaError->setText("Debés ingresar usuario y contraseña");
            etiquetaError->show();
            return;
        }
        QString rutaArchivo=QDir(QCoreApplication::applicationDirPath()).filePath("usuarios.txt");
        //verificacion de que el usuario no exista
        QFile archivoLectura(rutaArchivo);
        if(archivoLectura.open(QIODevice::ReadOnly | QIODevice::Text)){
            QTextStream flujoLectura(&archivoLectura);
            while(!flujoLectura.atEnd()){
                QString linea=flujoLectura.readLine();
                int posicionEspacio=linea.indexOf(' ');
                if(posicionEspacio==-1){
                    continue;
                }
                QString usuarioExistente=linea.left(posicionEspacio);
                if(usuarioExistente.compare(nombreUsuario,Qt::CaseInsensitive)==0){
                    archivoLectura.close();
                    etiquetaError->setText("Ese nombre de usuario ya existe. Elige otro nombre");
                    etiquetaError->show();
                    return;
                }
            }
            archivoLectura.close();
        }
        QFile archivo(rutaArchivo);
        if(archivo.open(QIODevice::Append | QIODevice::Text)){
            QTextStream flujo(&archivo);
            flujo<<nombreUsuario<<" "<<hashContrasena(contrasena)<<"\n";
            archivo.close();
        }
        etiquetaError->hide();
        campoUsuario->clear();
        campoContrasena->clear();
        emit registroCompletado(nombreUsuario);
    });
    connect(botonVolver, &QPushButton::clicked, this, [this]() { emit volverSolicitado(); });

    layoutTarjeta->addWidget(campoUsuario);
    layoutTarjeta->addWidget(campoContrasena);
    layoutTarjeta->addWidget(botonMostrarContrasena);
    layoutTarjeta->addWidget(etiquetaError);
    layoutTarjeta->addWidget(botonRegistrar);

    layoutPrincipal->addStretch();
    layoutPrincipal->addWidget(etiquetaTitulo);
    layoutPrincipal->addWidget(etiquetaSubtitulo);
    layoutPrincipal->addSpacing(16);
    layoutPrincipal->addWidget(tarjeta, 0, Qt::AlignHCenter);
    layoutPrincipal->addStretch();
    layoutPrincipal->addWidget(botonVolver);
    layoutPrincipal->addSpacing(8);
}
RegistroUsuario::~RegistroUsuario() {}