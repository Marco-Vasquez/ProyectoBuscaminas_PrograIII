#ifndef VENTANALOGIN_H
#define VENTANALOGIN_H
#include <QWidget>
class QLineEdit;
class QLabel;

// Pantalla de inicio de sesión
class VentanaLogin : public QWidget
{
    Q_OBJECT
public:
    explicit VentanaLogin(QWidget *parent = nullptr);
    ~VentanaLogin() override;

    // Precarga el nombre de usuario
    void sugerirUsuario(const QString &nombreUsuario);

    // Limpia usuario, contraseña y mensajes de error (al cerrar sesión)
    void limpiarCampos();

signals:
    void loginExitoso(QString nombreUsuario);
    void registroSolicitado();
    void salirSolicitado();

private:
    QLineEdit *campoUsuario;
    QLineEdit *campoContrasena;
    QLabel *etiquetaError;

    bool validarCredenciales(const QString &usuario, const QString &contrasena) const;
};
#endif // VENTANALOGIN_H