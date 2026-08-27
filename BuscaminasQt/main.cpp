#include "buscaminasmain.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    BuscaminasMain ventana;
    ventana.show();
    return app.exec();
}
