#include "lennygui.h"
#include "ui_lennygui.h"
#include "lennyparser.h"


LennyGUI::LennyGUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LennyGUI)
{
    ui->setupUi(this);
    initItemModel();
    createQmlRoot();
    ui->quickWidget->setSource(QUrl("qrc:/qml/lenny-canvas.qml"));
    ui->centralWidget->setStyleSheet("background-color:black;");
    ui->loadBar->hide();
}

LennyGUI::~LennyGUI()
{
    emit shutDownEverything();
    delete ui;
}

void LennyGUI::createQmlRoot(){
    QQmlEngine *qmlEngine = ui->quickWidget->engine();
    QQmlContext *rootContext = ui->quickWidget->rootContext();
    QObject *rootObject = ui->quickWidget->rootObject();
    rootContext->setContextProperty("itemscale_",1.0);
}

void LennyGUI::execLennyParser(){
    LennyParser testParser;
    QThread *workerThread = new QThread;
    testParser.moveToThread(workerThread);
    QFileDialog getInputFile;
    testParser.inputFile = getInputFile.getOpenFileName(this,tr("Select a Lenny-compatible JSON file"),QDir::currentPath(),tr("JSON files %1").arg("(*.json)"));
    connect(workerThread,SIGNAL(started()),&testParser,SLOT(parseFile()),Qt::QueuedConnection);
    connect(this,SIGNAL(shutDownEverything()),workerThread,SLOT(quit()),Qt::QueuedConnection);
    connect(&testParser,SIGNAL(exportObjects(QHash<QString,QVariant>)),this,SLOT(importObjects(QHash<QString,QVariant>)));
    QEventLoop workWaiter;
    connect(workerThread,SIGNAL(finished()),&workWaiter,SLOT(quit()));
    connect(&testParser,SIGNAL(finishedProcessing()),&workWaiter,SLOT(quit()),Qt::QueuedConnection);
    ui->loadBar->setVisible(true);
    ui->loadBar->setMaximum(0);
    workerThread->start();
    workWaiter.exec();
    ui->loadBar->setMaximum(100);
    ui->loadBar->setValue(100);
    ui->loadBar->setVisible(false);
}

void LennyGUI::importObjects(QHash<QString, QVariant> importedHash){
    itemGridModel.clear();
    foreach(QString key, importedHash.keys()){
        QJsonObject launchObject = importedHash.value(key).toJsonObject();
        QString title,exec,itemId;
        QHash<QString,QString> images;
        foreach(QString obKey,launchObject.keys()){
            qDebug() << obKey << launchObject.value(obKey);
            if(obKey=="desktop.title")
                title=launchObject.value(obKey).toString();
            if(obKey=="desktop.icon")
                images.insert("icon",launchObject.value(obKey).toString());
            if(obKey=="desktop.banner")
                images.insert("banner",launchObject.value(obKey).toString());
            if(obKey=="desktop.poster")
                images.insert("poster",launchObject.value(obKey).toString());
            if(obKey=="exec")
                exec=launchObject.value(obKey).toString();
            if(obKey=="id")
                itemId=launchObject.value(obKey).toString();
        }
        QHash<QString,QVariant> thisEntry;
        thisEntry.insert("title",title);
        if(!images.value("icon").isEmpty())
            thisEntry.insert("icon",images.value("icon"));
        if(!images.value("banner").isEmpty())
            thisEntry.insert("banner",images.value("banner"));
        if(!images.value("poster").isEmpty())
            thisEntry.insert("poster",images.value("poster"));
        thisEntry.insert("itemId",itemId);
        thisEntry.insert("exec",exec);
        addToItemModel(thisEntry);
    }
}

void LennyGUI::executeItem(QString itemId){

}

void LennyGUI::initItemModel(){
    itemGridModel.setColumnCount(6);
    QQmlContext *rootContext = ui->quickWidget->rootContext();
    rootContext->setContextProperty("items_",&itemGridModel);
    QHash<int,QByteArray> roleNames;
    roleNames.insert(0,"itemId");
    roleNames.insert(1,"title");
    roleNames.insert(2,"exec");
    roleNames.insert(3,"icon");
    roleNames.insert(4,"banner");
    roleNames.insert(5,"poster");
    itemGridModel.setItemRoleNames(roleNames);
}

void LennyGUI::addToItemModel(QHash<QString, QVariant> importedHash){
    QList<QStandardItem*> stdRow;
    for(int i=0;i<6;i++){
        QStandardItem *stdItem = new QStandardItem;
        stdRow.insert(i,stdItem);
    }
    foreach(QString key,importedHash.keys()){
        if(key=="itemId")
            stdRow.at(0)->setData(importedHash.value(key));
        if(key=="title")
            stdRow.at(1)->setData(importedHash.value(key));
        if(key=="exec")
            stdRow.at(2)->setData(importedHash.value(key));
        if(key=="icon")
            stdRow.at(3)->setData(importedHash.value(key));
        if(key=="banner")
            stdRow.at(4)->setData(importedHash.value(key));
        if(key=="poster")
            stdRow.at(5)->setData(importedHash.value(key));
    }
    itemGridModel.appendRow(stdRow);
}

void LennyGUI::on_zoomSlider_valueChanged(int value)
{
    float itemScale = (50.0+value)/100.0;
    qDebug() << itemScale;
    ui->quickWidget->rootContext()->setContextProperty("itemscale_",itemScale);
    emit scaleChanged();
//    for(int i=0;i<graphScene.items().count();i++){
//        QGraphicsItem *curr = graphScene.items().at(i);
//        curr->setScale(itemScale);
//        curr->setPos(i*300,3);
//    }
//    ui->label->setText(QString::number(itemScale));
//    graphScene.setSceneRect(ui->lennyCanvas->sceneRect());
}

void LennyGUI::on_actionFullscreen_triggered()
{
    ui->itemFrame->setHidden(!ui->itemFrame->isVisible());
    if(!isFullScreen()){
        showFullScreen();
    }else
        showNormal();
}

void LennyGUI::on_actionImport_objects_triggered()
{
    execLennyParser();
}
