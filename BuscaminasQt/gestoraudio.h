#ifndef GESTORAUDIO_H
#define GESTORAUDIO_H
#include <QObject>
#include <QString>
class QSoundEffect;
class QMediaPlayer;
class QAudioOutput;
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
    void setVolumenMusica(int porcentaje);
    void setVolumenEfectos(int porcentaje);
    int getVolumenMusica() const;
    int getVolumenEfectos() const;


    bool estaMuteado() const;
    void setMuteado(bool silenciado);

    // contadores para verificar en pruebas que los efectos solo suenan cuando corresponde
    int getContadorClics() const;
    int getContadorBanderas() const;
    int getContadorExplosiones() const;
signals:

    void muteCambiado(bool silenciado);
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
    int volumenEfectosActual;
    bool muteado = false;
    int nivelMusicaPreMute = 50;
    int nivelEfectosPreMute = 60;

    bool musicaPausadaPorMute = false;
};

#endif // GESTORAUDIO_H