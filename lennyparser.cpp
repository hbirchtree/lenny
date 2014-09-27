#include "lennyparser.h"

LennyParser::LennyParser(QObject *parent) :
    QObject(parent)
{
}

void LennyParser::parseFile(){
    QJsonDocument toProcess = openFile(inputFile);
    QJsonObject rootObject = toProcess.object();
    QHash<QString,QVariant> launchables;
    QJsonObject options;
    foreach(QString key, rootObject.keys()){
        if(key=="launchables"){
            launchables = examineLaunchables(rootObject.value(key).toArray());
        }
        if(key=="lenny-opts")
            options=rootObject.value(key).toObject();
    }
    if(!launchables.isEmpty()){
        emit exportObjects(launchables);
    }else{
        printf("WARN: No launchable objects were found.\n");
    }
    if(!options.isEmpty())
        emit exportOptions(options);

    emit finishedProcessing();
}

QHash<QString,QVariant> LennyParser::examineLaunchables(QJsonArray inputArray){
    QHash<QString,QVariant> returnHash;
    for(int i=0;i<inputArray.count();i++)
        if(inputArray.at(i).isObject()){
            QJsonObject launchObject=inputArray.at(i).toObject();
            QString idString = launchObject.value("id").toString();
            launchObject.remove("id");
            if(!idString.isEmpty())
                returnHash.insert(idString,launchObject);
        }
    return returnHash;
}

QJsonDocument LennyParser::openFile(QString filename){
    QFile docFile(filename);
    if(!docFile.exists()){
        printf("ERROR: File %s does not exist.\n",qPrintable(filename));
        return QJsonDocument();
    }
    if(!docFile.open(QIODevice::ReadOnly|QIODevice::Text)){
        printf("ERROR: File %s could not be opened.\n",qPrintable(filename));
        return QJsonDocument();
    }
    QJsonDocument jDoc;
    jDoc = jDoc.fromJson(docFile.readAll());
    if(jDoc.isEmpty()){
        printf("ERROR: JSON document is empty.\n");
        return QJsonDocument();
    }else
        return jDoc;
}
