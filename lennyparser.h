#ifndef LENNYPARSER_H
#define LENNYPARSER_H

#include <QObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonObject>
#include <QDebug>

class LennyParser : public QObject
{
    Q_OBJECT
public:
    explicit LennyParser(QObject *parent = 0);
    void insertStartOpts(QString filename);

signals:
    void exportEntry(QString,QStringList,QString);

public slots:
    void parseFile();
private:
    QJsonDocument openFile(QString filename);

private:
    QString inputFile;
};

#endif // LENNYPARSER_H
