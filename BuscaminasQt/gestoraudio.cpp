#include "gestoraudio.h"
#include <QSoundEffect>
#include <QCoreApplication>
#include <QDir>
#include <QFile>
#include <QUrl>

namespace {
QString rutaSonido(const QString &nombre)
{
    // busca el .wav en varias ubicaciones posibles y usa la primera que exista.
    QStringList candidatas;
    candidatas << QCoreApplication::applicationDirPath() + "/sonidos/" + nombre
               << QDir::currentPath() + "/sonidos/" + nombre
               << QCoreApplication::applicationDirPath() + "/" + nombre;
    for (const QString &candidata : candidatas) {
        if (QFile::exists(candidata)) {
            return candidata;
        }
    }
    return candidatas.first();
}
}

GestorAudio::GestorAudio(QObject *parent)
    : QObject(parent)
{
    efectoClic = new QSoundEffect(this);
    efectoClic->setSource(QUrl::fromLocalFile(rutaSonido("clic.wav")));
    efectoClic->setVolume(0.6f);

    efectoBandera = new QSoundEffect(this);
    efectoBandera->setSource(QUrl::fromLocalFile(rutaSonido("bandera.wav")));
    efectoBandera->setVolume(0.6f);

    efectoExplosion = new QSoundEffect(this);
    efectoExplosion->setSource(QUrl::fromLocalFile(rutaSonido("explosion.wav")));
    efectoExplosion->setVolume(0.8f);
}

GestorAudio::~GestorAudio() {}

void GestorAudio::reproducirClic()
{
    // play() es seguro aunque el sonido aún esté cargando (se reproduce al
    // terminar de cargar) y no hace nada si el archivo no existe.
    efectoClic->play();
}

void GestorAudio::reproducirBandera()
{
    efectoBandera->play();
}

void GestorAudio::reproducirExplosion()
{
    efectoExplosion->play();
}