#include "buscaminasmain.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BuscaminasMain w;
    w.show();
    return QApplication::exec();
}
