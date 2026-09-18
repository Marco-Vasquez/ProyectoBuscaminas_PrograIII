#ifndef ESTILOS_H
#define ESTILOS_H
#include <QString>
#include <QColor>

// Tema visual compartido por todas las pantallas (oscuro, moderno).
// Solo estilos: no cambia ninguna lógica del programa.
namespace Estilos {

inline const QString FONDO = "#1e272e";         // fondo general de pantallas
inline const QString TARJETA = "#2c3e50";       // tarjetas y paneles
inline const QString TARJETA_CLARA = "#34495e"; // tarjetas destacadas (récords)
inline const QString TEXTO = "#ecf0f1";         // texto principal
inline const QString TEXTO_SUAVE = "#95a5a6";   // texto secundario
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

// fondo de una pantalla completa
inline QString fondoPantalla()
{
    return QString("background-color: %1;").arg(FONDO);
}

// botón principal con hover/pressed/disabled
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

// botón secundario (volver, etc.)
inline QString botonSecundario(int alto = 50)
{
    return boton(GRIS, alto);
}

// campo de texto (QLineEdit)
inline QString campoTexto()
{
    return QString(
        "QLineEdit { background-color: %1; color: %2; border: 2px solid #3d4a55;"
        " border-radius: 8px; padding: 8px; font-size: 13px; }"
        "QLineEdit:focus { border-color: %3; }")
        .arg(FONDO, TEXTO, AZUL);
}

// etiqueta de título grande
inline QString titulo(int tamano = 22)
{
    return QString("color: %1; font-weight: bold; font-size: %2px;").arg(TEXTO).arg(tamano);
}

// etiqueta de texto normal
inline QString texto(int tamano = 12)
{
    return QString("color: %1; font-size: %2px;").arg(TEXTO).arg(tamano);
}

inline QString textoSuave(int tamano = 11)
{
    return QString("color: %1; font-size: %2px;").arg(TEXTO_SUAVE).arg(tamano);
}

// tarjeta contenedora
inline QString tarjeta()
{
    return QString("background-color: %1; border-radius: 14px;").arg(TARJETA);
}

// combo box (QComboBox)
inline QString combo()
{
    return QString(
        "QComboBox { background-color: %1; color: %2; border: 2px solid #3d4a55;"
        " border-radius: 8px; padding: 8px; font-size: 13px; }"
        "QComboBox::drop-down { border: none; width: 24px; }"
        "QComboBox QAbstractItemView { background-color: %1; color: %2;"
        " selection-background-color: %3; selection-color: white; }")
        .arg(FONDO, TEXTO, AZUL);
}

// slider (QSlider)
inline QString slider()
{
    return QString(
        "QSlider::groove:horizontal { height: 6px; background: #3d4a55; border-radius: 3px; }"
        "QSlider::handle:horizontal { width: 18px; height: 18px; margin: -6px 0;"
        " background: %1; border-radius: 9px; }"
        "QSlider::handle:horizontal:hover { background: %2; }")
        .arg(AZUL, aclarar(AZUL));
}

} // namespace Estilos
#endif // ESTILOS_H