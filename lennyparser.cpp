#include "lennyparser.h"

LennyParser::LennyParser(QObject *parent) :
    QObject(parent)
{

}

void LennyParser::parseFile(){
    qDebug() << "hello.";
    qDebug() << openFile(inputFile);
}

void LennyParser::insertStartOpts(QString filename){
    inputFile = filename;
}

QJsonDocument LennyParser::openFile(QString filename){
    return QJsonDocument();
}
