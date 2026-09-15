#ifndef GESTORAUDIO_H
#define GESTORAUDIO_H
#include <QObject>
#include <QString>
class QSoundEffect;
class QMediaPlayer;
class QAudioOutput;
// Centraliza los efectos de sonido (QSoundEffect) y la música de fondo (QMediaPlayer).
// Los efectos van en sonidos/ y la música en musica/ junto al ejecutable.
class GestorAudio : public QObject
{
    Q_OBJECT
public:
    explicit GestorAudio(QObject *parent = nullptr);
    ~GestorAudio() override;

    void reproducirClic();
    void reproducirBandera();
    void reproducirExplosion();
    void iniciarMusicaMenu();
    void iniciarMusicaJuego();
    void detenerMusica();

    // contadores para verificar en pruebas que los efectos solo suenan cuando corresponde
    int getContadorClics() const;
    int getContadorBanderas() const;
    int getContadorExplosiones() const;
private:
    QSoundEffect *efectoClic;
    QSoundEffect *efectoBandera;
    QSoundEffect *efectoExplosion;
    QMediaPlayer *reproductorMusica;
    QAudioOutput *salidaAudio;
    QString musicaActual;
    int contadorClics;
    int contadorBanderas;
    int contadorExplosiones;
    void reproducirMusica(const QString &archivo);
};

#endif // GESTORAUDIO_H