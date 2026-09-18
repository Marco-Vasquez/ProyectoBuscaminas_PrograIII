#ifndef MEDALLAIMAGEN_H
#define MEDALLAIMAGEN_H
#include <QPixmap>
#include <QPainter>
#include <QPen>
#include <QString>
#include <QDir>
#include <QCoreApplication>

// color base de cada medalla (mismo esquema en todo el programa)
inline QString colorDeMedalla(const QString &medalla)
{
    if (medalla == "Bronce")   return "#cd7f32";
    if (medalla == "Plata")    return "#a8a9ad";
    if (medalla == "Oro")      return "#f1c40f";
    if (medalla == "Diamante") return "#3498db";
    if (medalla == "Valiente") return "#e67e22";
    return "#95a5a6"; // "Ninguna" o sin medalla
}

// carga el PNG de la medalla desde recursos/medallas/<tipo>.png (junto al exe).
// si el archivo no existe, dibuja un círculo de color como respaldo.
inline QPixmap cargarMedallaPixmap(const QString &tipo, int ancho = 40)
{
    QString nombre = tipo.trimmed().toLower();
    if (nombre.isEmpty() || nombre == "ninguna" || nombre == "sin medalla") {
        nombre = "ninguna";
    }
    QString ruta = QDir(QCoreApplication::applicationDirPath())
                       .filePath(QString("recursos/medallas/%1.png").arg(nombre));
    QPixmap pixmap(ruta);
    if (!pixmap.isNull()) {
        return pixmap.scaled(ancho, ancho, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    }

    // respaldo: círculo con el color de la medalla
    QPixmap respaldo(ancho, ancho);
    respaldo.fill(Qt::transparent);
    QPainter painter(&respaldo);
    painter.setRenderHint(QPainter::Antialiasing, true);
    QColor color(colorDeMedalla(tipo));
    painter.setBrush(color);
    painter.setPen(QPen(color.darker(130), 2));
    painter.drawEllipse(1, 1, ancho - 2, ancho - 2);
    painter.end();
    return respaldo;
}
#endif // MEDALLAIMAGEN_H