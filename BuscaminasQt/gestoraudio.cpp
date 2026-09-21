#include "gestoraudio.h"
#include <QSoundEffect>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QCoreApplication>
#include <QDir>
#include <QFile>
#include <QUrl>

namespace {
const char *ARCHIVO_MUSICA_MENU = "sounovamusic-puzzle-amp-casual-game-music-460543.mp3.wav";
const char *ARCHIVO_MUSICA_JUEGO = "cyberwave-orchestra-adventure-game-fun-background-music-247661.mp3.wav";

QString rutaEnCarpeta(const QString &carpeta, const QString &nombre)
{
    // busca el archivo en varias ubicaciones posibles y usa la primera que exista.
    // así funciona aunque el ejecutable se corra desde otra carpeta.
    QStringList candidatas;
    candidatas << QCoreApplication::applicationDirPath() + "/" + carpeta + "/" + nombre
               << QDir::currentPath() + "/" + carpeta + "/" + nombre
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
    : QObject(parent), contadorClics(0), contadorBanderas(0), contadorExplosiones(0),volumenEfectosActual(60)
{
    efectoClic = new QSoundEffect(this);
    efectoClic->setSource(QUrl::fromLocalFile(rutaEnCarpeta("sonidos", "clic.wav")));
    efectoClic->setVolume(0.6f);

    efectoBandera = new QSoundEffect(this);
    efectoBandera->setSource(QUrl::fromLocalFile(rutaEnCarpeta("sonidos", "bandera.wav")));
    efectoBandera->setVolume(0.6f);

    efectoExplosion = new QSoundEffect(this);
    efectoExplosion->setSource(QUrl::fromLocalFile(rutaEnCarpeta("sonidos", "explosion.wav")));
    efectoExplosion->setVolume(0.8f);

    salidaAudio = new QAudioOutput(this);
    salidaAudio->setVolume(0.5f);

    reproductorMusica = new QMediaPlayer(this);
    reproductorMusica->setAudioOutput(salidaAudio);
    reproductorMusica->setLoops(QMediaPlayer::Infinite);
}

GestorAudio::~GestorAudio() {}

void GestorAudio::reproducirClic()
{
    contadorClics++;
    // play() es seguro aunque el sonido aún esté cargando
    efectoClic->play();
}

void GestorAudio::reproducirBandera()
{
    contadorBanderas++;
    efectoBandera->play();
}

void GestorAudio::reproducirExplosion()
{
    contadorExplosiones++;
    efectoExplosion->play();
}

void GestorAudio::iniciarMusicaMenu()
{
    reproducirMusica(ARCHIVO_MUSICA_MENU);
}

void GestorAudio::iniciarMusicaJuego()
{
    reproducirMusica(ARCHIVO_MUSICA_JUEGO);
}

void GestorAudio::detenerMusica()
{
    reproductorMusica->stop();
    musicaActual.clear();
}

void GestorAudio::reproducirMusica(const QString &archivo)
{
    QString ruta = rutaEnCarpeta("musica", archivo);
    if (musicaActual == ruta && reproductorMusica->playbackState() == QMediaPlayer::PlayingState) {
        return; // la pista ya está sonando, no la reinicio
    }
    musicaActual = ruta;
    reproductorMusica->setSource(QUrl::fromLocalFile(ruta));
    reproductorMusica->play();
}
void GestorAudio::setVolumenMusica(int porcentaje){
    salidaAudio->setVolume(porcentaje/100.0f);
    if (porcentaje > 0) muteado = false;
}
void GestorAudio::setVolumenEfectos(int porcentaje){
    volumenEfectosActual=porcentaje;
    float volumen=porcentaje/100.0f;
    efectoClic->setVolume(volumen);
    efectoBandera->setVolume(volumen);
    efectoExplosion->setVolume(volumen);
    if (porcentaje > 0) muteado = false;
}
int GestorAudio::getVolumenMusica() const{
    return static_cast<int>(salidaAudio->volume()*100);
}
int GestorAudio::getVolumenEfectos() const{
    return volumenEfectosActual;
}
bool GestorAudio::estaMuteado() const{
    return muteado;
}
void GestorAudio::setMuteado(bool silenciado){
    if (muteado == silenciado) {
        return;
    }
    if (silenciado) {
        // guarda los niveles actuales para poder restaurarlos al desmutear
        nivelMusicaPreMute = getVolumenMusica();
        nivelEfectosPreMute = getVolumenEfectos();
        setVolumenMusica(0);
        setVolumenEfectos(0);
    } else {
        setVolumenMusica(nivelMusicaPreMute);
        setVolumenEfectos(nivelEfectosPreMute);
    }
    muteado = silenciado;
}
int GestorAudio::getContadorClics() const { return contadorClics; }
int GestorAudio::getContadorBanderas() const { return contadorBanderas; }
int GestorAudio::getContadorExplosiones() const { return contadorExplosiones; }