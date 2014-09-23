#include "lennygui.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LennyGUI w;
    w.show();

    return a.exec();
}
