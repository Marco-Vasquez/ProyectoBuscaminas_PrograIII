#include "buscaminasmain.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    BuscaminasMain ventanaPrincipal;
    ventanaPrincipal.show();
    return app.exec();
}