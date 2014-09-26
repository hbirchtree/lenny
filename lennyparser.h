#ifndef LENNYPARSER_H
#define LENNYPARSER_H

#include <QObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonObject>
#include <QDebug>
#include <QTimer>

class LennyParser : public QObject
{
    Q_OBJECT
public:
    explicit LennyParser(QObject *parent = 0);
    QString inputFile;

signals:
    void exportEntry(QString,QStringList,QString);
    void finishedProcessing();

public slots:
    void parseFile();
private:
    QJsonDocument openFile(QString filename);

private:
};

#endif // LENNYPARSER_H
