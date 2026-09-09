#ifndef REGISTROUSUARIO_H
#define REGISTROUSUARIO_H
#include <QWidget>
class RegistroUsuario : public QWidget
{
    Q_OBJECT
public:
    explicit RegistroUsuario(QWidget *parent = nullptr);
    ~RegistroUsuario() override;
signals:
    void registroCompletado(QString nombreUsuario);
    void volverSolicitado();
};
#endif // REGISTROUSUARIO_H