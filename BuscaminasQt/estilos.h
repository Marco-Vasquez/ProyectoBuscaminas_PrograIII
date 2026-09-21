#ifndef ESTILOS_H
#define ESTILOS_H
#include <QString>
#include <QColor>

namespace Estilos {

inline const QString FONDO = "#1e272e";
inline const QString TARJETA = "#2c3e50";
inline const QString TARJETA_CLARA = "#34495e";
inline const QString TEXTO = "#ecf0f1";
inline const QString TEXTO_SUAVE = "#95a5a6";
inline const QString VERDE = "#2ecc71";
inline const QString AZUL = "#3498db";
inline const QString ROJO = "#e74c3c";
inline const QString NARANJA = "#f39c12";
inline const QString MORADO = "#9b59b6";
inline const QString TURQUESA = "#16a085";
inline const QString GRIS = "#7f8c8d";

inline QString aclarar(const QString &hex, int factor = 118)
{
    QColor c(hex);
    return c.lighter(factor).name();
}

inline QString oscurecer(const QString &hex, int factor = 82)
{
    QColor c(hex);
    return c.darker(factor).name();
}

inline QString fondoPantalla()
{
    return QString("background-color: %1;").arg(FONDO);
}

inline QString boton(const QString &color, int alto = 50)
{
    return QString(
               "QPushButton { background-color: %1; color: white; border: none;"
               " border-radius: 10px; font-weight: bold; font-size: 13px; padding: 10px; }"
               "QPushButton:hover { background-color: %2; }"
               "QPushButton:pressed { background-color: %3; }"
               "QPushButton:disabled { background-color: #3d4a55; color: #7f8c8d; }")
        .arg(color, aclarar(color), oscurecer(color));
}

inline QString botonSecundario(int alto = 50)
{
    return boton(GRIS, alto);
}

inline QString campoTexto()
{
    return QString(
               "QLineEdit { background-color: %1; color: %2; border: 1px solid #3d4a55;"
               " border-radius: 8px; padding: 12px 14px; font-size: 15px;"
               " selection-background-color: %3; }"
               "QLineEdit:focus { border: 1px solid %3; }")
        .arg(FONDO, TEXTO, AZUL);
}

inline QString titulo(int tamano = 22)
{
    return QString("color: %1; font-weight: bold; font-size: %2px; background: transparent;").arg(TEXTO).arg(tamano);
}

inline QString texto(int tamano = 12)
{
    return QString("color: %1; font-size: %2px; background: transparent;").arg(TEXTO).arg(tamano);
}

inline QString textoSuave(int tamano = 11)
{
    return QString("color: %1; font-size: %2px; background: transparent;").arg(TEXTO_SUAVE).arg(tamano);
}

inline QString tarjeta()
{
    return QString("background-color: %1; border-radius: 14px;").arg(TARJETA);
}

inline QString combo()
{
    return QString(
               "QComboBox { background-color: %1; color: %2; border: 2px solid #3d4a55;"
               " border-radius: 8px; padding: 10px; font-size: 14px; }"
               "QComboBox::drop-down { border: none; width: 24px; }"
               "QComboBox QAbstractItemView { background-color: %1; color: %2;"
               " selection-background-color: %3; selection-color: white; }")
        .arg(FONDO, TEXTO, AZUL);
}

inline QString slider()
{
    return QString(
               "QSlider::groove:horizontal { height: 6px; background: #3d4a55; border-radius: 3px; }"
               "QSlider::handle:horizontal { width: 18px; height: 18px; margin: -6px 0;"
               " background: %1; border-radius: 9px; }"
               "QSlider::handle:horizontal:hover { background: %2; }")
        .arg(AZUL, aclarar(AZUL));
}

}
#endif // ESTILOS_H