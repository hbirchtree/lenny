#include "lennygui.h"
#include "ui_lennygui.h"
#include "lennyparser.h"


LennyGUI::LennyGUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LennyGUI)
{
    ui->setupUi(this);
    ui->loadBar->hide();
}

LennyGUI::~LennyGUI()
{
    emit shutDownEverything();
    delete ui;
}

void LennyGUI::initAll(QString filename){
    if(!filename.isEmpty()){
        execLennyParser(filename);
    }
}

void LennyGUI::createQmlRoot(){
    QQmlContext *rootContext = ui->quickWidget->rootContext();
    int itemScaleMin = startOpts.value("zoomlevel.min").toDouble()*100;
    if(itemScaleMin == 0)
        itemScaleMin=80;
    ui->zoomSlider->setMinimum(itemScaleMin);
    int itemScaleMax = startOpts.value("zoomlevel.max").toDouble()*100;
    if(itemScaleMax == 0)
        itemScaleMax=400;
    ui->zoomSlider->setMaximum(itemScaleMax);

    double itemScaleDefault = startOpts.value("zoomlevel.default").toDouble();
    if(itemScaleDefault == 0)
        itemScaleDefault=1.3;
    rootContext->setContextProperty("itemscale_",itemScaleDefault); //CONFIGURABLE
    ui->zoomSlider->setValue(itemScaleDefault*100);
    QUrl qmlSource = QUrl(startOpts.value("qml.source").toString()).fileName();
    if(qmlSource.isEmpty())
        qmlSource=QUrl("qrc:/qml/lenny-canvas.qml");
    ui->quickWidget->setSource(qmlSource); //CONFIGURABLE
    connect(ui->quickWidget->rootObject(),SIGNAL(itemSelected(QString)),this,SLOT(executeItem(QString)));
}

void LennyGUI::execLennyParser(QString filename){
    LennyParser testParser;
    QThread *workerThread = new QThread;
    testParser.moveToThread(workerThread);
    testParser.inputFile = filename;
    connect(workerThread,SIGNAL(started()),&testParser,SLOT(parseFile()),Qt::QueuedConnection);
    connect(this,SIGNAL(shutDownEverything()),workerThread,SLOT(quit()),Qt::QueuedConnection);
    connect(&testParser,SIGNAL(exportObjects(QHash<QString,QVariant>)),this,SLOT(importObjects(QHash<QString,QVariant>)));
    connect(&testParser,SIGNAL(exportOptions(QJsonObject)),this,SLOT(importOptions(QJsonObject)));
    connect(this,SIGNAL(optionsImported()),SLOT(applyImportedOptions()));
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

void LennyGUI::importOptions(QJsonObject optionObject){
    foreach(QString key, optionObject.keys()){
        if(key=="qml.source")
            startOpts.insert(key,optionObject.value(key).toString());
        if(key=="widget.stylesheet")
            startOpts.insert(key,optionObject.value(key).toString());
        if(key=="shell.program")
            startOpts.insert(key,optionObject.value(key).toString());
        if(key=="shell.argument")
            startOpts.insert(key,optionObject.value(key).toString());
        if(key=="zoomlevel.min")
            startOpts.insert(key,optionObject.value(key).toDouble());
        if(key=="zoomlevel.default")
            startOpts.insert(key,optionObject.value(key).toDouble());
        if(key=="zoomlevel.max")
            startOpts.insert(key,optionObject.value(key).toDouble());
    }
    emit optionsImported();
}

void LennyGUI::applyImportedOptions(){
    initItemModel();
    createQmlRoot();
    if(startOpts.value("widget.stylesheet").toString().isEmpty()){
        ui->centralWidget->setStyleSheet("background-color:black;"); //CONFIGURABLE
    }else
        ui->centralWidget->setStyleSheet(startOpts.value("widget.stylesheet").toString());
}

void LennyGUI::importObjects(QHash<QString, QVariant> importedHash){
    itemGridModel.clear();
    foreach(QString key, importedHash.keys()){
        QJsonObject launchObject = importedHash.value(key).toJsonObject();
        QString title,exec;
        QHash<QString,QString> images;
        foreach(QString obKey,launchObject.keys()){
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
        }
        QHash<QString,QVariant> thisEntry;
        thisEntry.insert("title",title);
        if(!images.value("icon").isEmpty())
            thisEntry.insert("icon",images.value("icon"));
        if(!images.value("banner").isEmpty())
            thisEntry.insert("banner",images.value("banner"));
        if(!images.value("poster").isEmpty())
            thisEntry.insert("poster",images.value("poster"));
        thisEntry.insert("itemId",key);
        thisEntry.insert("exec",exec);
        addToItemModel(thisEntry);
    }
}

void LennyGUI::executeItem(QString itemId){
    QProcess launcher;
    for(int r=0;r<itemGridModel.rowCount();r++)
        if(itemGridModel.item(r,0)->data().toString()==itemId){ //Check to see if the itemId matches
            if(!itemGridModel.item(r,2)->data().toString().isEmpty()){
                QString program = startOpts.value("shell.program").toString();//CONFIGURABLE
                if(program.isEmpty())
                    program="sh";
                QStringList arguments;
                QString shellArg = startOpts.value("shell.argument").toString();//CONFIGURABLE
                if(shellArg.isEmpty())
                    shellArg="-c";
                arguments.append(shellArg);
                arguments.append("--");
                arguments.append(itemGridModel.item(r,2)->data().toString());
                qDebug() << arguments;
                launcher.startDetached(program,arguments);
                launcher.waitForStarted();
            }
        }
}

void LennyGUI::initItemModel(){
    QQmlContext *rootContext = ui->quickWidget->rootContext();
    rootContext->setContextProperty("items_",&itemGridModel);
    QHash<int,QByteArray> roleNames;
    roleNames.insert(0,"itemId");
    roleNames.insert(1,"title");
    roleNames.insert(2,"exec");
    roleNames.insert(3,"icon");
    roleNames.insert(4,"banner");
    roleNames.insert(5,"poster");
//    QStringList roleNameList;
//    roleNameList << "itemId" << "title" << "exec" << "icon" << "banner" << "poster";
    itemGridModel.setItemRoleNames(roleNames);
//    itemGridModel.setHorizontalHeaderLabels(roleNameList);
}

void LennyGUI::addToItemModel(QHash<QString, QVariant> importedHash){
    QList<QStandardItem*> *stdRow = new QList<QStandardItem*>;
    for(int i=0;i<6;i++){
        QStandardItem *stdItem = new QStandardItem;
        stdRow->insert(i,stdItem);
    }
    foreach(QString key,importedHash.keys()){
        if(key=="itemId")
            stdRow->at(0)->setData(importedHash.value(key));
        if(key=="title")
            stdRow->at(1)->setData(importedHash.value(key));
        if(key=="exec")
            stdRow->at(2)->setData(importedHash.value(key));
        if(key=="icon")
            stdRow->at(3)->setData(importedHash.value(key));
        if(key=="banner")
            stdRow->at(4)->setData(importedHash.value(key));
        if(key=="poster")
            stdRow->at(5)->setData(importedHash.value(key));
    }
    itemGridModel.appendRow(*stdRow);
//    ui->quickWidget->rootContext()->setContextProperty("items_",&itemGridModel);
}

void LennyGUI::on_zoomSlider_valueChanged(int value)
{
    float itemScale = (50.0+value)/100.0;
    ui->quickWidget->rootContext()->setContextProperty("itemscale_",itemScale);
}

void LennyGUI::on_actionFullscreen_triggered()
{
    ui->menuBar->setHidden(!ui->menuBar->isVisible());
    if(!isFullScreen()){
        showFullScreen();
    }else
        showNormal();
}

void LennyGUI::on_actionImport_objects_triggered()
{
    QFileDialog getInputFile;
    execLennyParser(getInputFile.getOpenFileName(this,tr("Select a Lenny-compatible JSON file"),QDir::currentPath(),tr("JSON files %1").arg("(*.json)")));
}

void LennyGUI::on_actionInitialize_QML_triggered()
{
    createQmlRoot();
}
