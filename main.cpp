#include "lennygui.h"
#include <QApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include "stdio.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    QApplication::setApplicationDisplayName("Lenny");
    QApplication::setApplicationName("Lenny");
    QApplication::setApplicationVersion("0.9");
    LennyGUI w;

    QCommandLineParser cParser;
    cParser.addHelpOption();
    cParser.setApplicationDescription("A QML interface for launching programs.");
    cParser.addPositionalArgument("<*.json>",QApplication::translate("init","JSON file for Lenny"),"<*.json>");
    cParser.process(a);

    if(cParser.positionalArguments().length()>=1){
        w.initAll(cParser.positionalArguments()[0]);
    }

    qDebug() << "done";

    w.show();

    return a.exec();
}
