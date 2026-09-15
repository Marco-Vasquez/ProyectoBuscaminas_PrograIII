#ifndef GESTORAUDIO_H
#define GESTORAUDIO_H
#include <QObject>
class QSoundEffect;
// Centraliza los efectos de sonido (QSoundEffect) del juego.
class GestorAudio : public QObject
{
    Q_OBJECT
public:
    explicit GestorAudio(QObject *parent = nullptr);
    ~GestorAudio() override;

    void reproducirClic();
    void reproducirBandera();
    void reproducirExplosion();
private:
    QSoundEffect *efectoClic;
    QSoundEffect *efectoBandera;
    QSoundEffect *efectoExplosion;
};

#endif // GESTORAUDIO_H