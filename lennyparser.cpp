#include "lennyparser.h"

LennyParser::LennyParser(QObject *parent) :
    QObject(parent)
{
    qDebug() << "I'm born!";
}

void LennyParser::parseFile(){
    qDebug() << "hello.";
    qDebug() << openFile(inputFile);
    emit finishedProcessing();
}

QJsonDocument LennyParser::openFile(QString filename){
    return QJsonDocument();
}
