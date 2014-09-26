#include "lennygui.h"
#include "ui_lennygui.h"
#include "lennyparser.h"

LennyGUI::LennyGUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LennyGUI)
{
    ui->setupUi(this);
    ui->centralWidget->setStyleSheet("background-color:black;");
    ui->loadBar->setMaximum(0);
    ui->loadBar->setFormat(tr("Running"));
    ui->loadBar->hide();
    QStringList imageList;
    imageList.append("Final Feels X.png");
    importEntry("test",imageList,"test");
    imageList.append("Avatar.png");
    importEntry("test",imageList,"test");
    imageList.clear();
    createQmlRoot();
}

void LennyGUI::createQmlRoot(){

}

LennyGUI::~LennyGUI()
{
    emit shutDownEverything();
    delete ui;
}

void LennyGUI::importObjects(){
    LennyParser testParser;
    QThread *workerThread = new QThread;
    testParser.moveToThread(workerThread);
    testParser.inputFile = "entries.json";
    connect(workerThread,SIGNAL(started()),&testParser,SLOT(parseFile()),Qt::QueuedConnection);
    connect(this,SIGNAL(shutDownEverything()),workerThread,SLOT(quit()),Qt::QueuedConnection);
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
    qDebug() << "end";
}

void LennyGUI::importEntry(QString title, QStringList imageLocations, QString itemId){
    QFile imageFile;
    if(!imageLocations.isEmpty())
        foreach(QString file,imageLocations)
            imageFile.setFileName(file);
    if(!imageFile.open(QIODevice::ReadOnly))
        return;
}

void LennyGUI::on_zoomSlider_valueChanged(int value)
{
    float itemScale = (50.0+value)/100.0;
    qDebug() << itemScale;
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
    importObjects();
}
