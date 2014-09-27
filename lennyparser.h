#ifndef LENNYPARSER_H
#define LENNYPARSER_H

#include <QObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonObject>
#include <QDebug>
#include <QTimer>
#include <QFile>

class LennyParser : public QObject
{
    Q_OBJECT
public:
    explicit LennyParser(QObject *parent = 0);
    QString inputFile;
    QHash<QString,QVariant> examineLaunchables(QJsonArray inputArray);

signals:
    void exportObjects(QHash<QString,QVariant>);
    void exportOptions(QJsonObject);
    void finishedProcessing(); //Returned even if it fails

public slots:
    void parseFile();
private:
    QJsonDocument openFile(QString filename);

private:
};

#endif // LENNYPARSER_H
