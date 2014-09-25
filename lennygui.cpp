#include "lennygui.h"
#include "ui_lennygui.h"
#include "lennyparser.h"

LennyGUI::LennyGUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LennyGUI)
{
    ui->setupUi(this);
    ui->centralWidget->setStyleSheet("background-color:black;");
//    createBackground();
    ui->loadBar->setMaximum(0);
    ui->loadBar->setFormat(tr("Running"));
    ui->loadBar->hide();
//    LennyParser testParser;
//    QThread *workerThread = new QThread(this);
//    testParser.moveToThread(workerThread);
//    connect(workerThread,SIGNAL(started()),&testParser,SLOT(parseFile()));
//    connect(this,SIGNAL(shutDownEverything()),workerThread,SLOT(quit()));
//    testParser.insertStartOpts("testfile.json");
    QStringList imageList;
    imageList.append("Final Feels X.png");
    importEntry("test",imageList,"test");
    imageList.append("Avatar.png");
    importEntry("test",imageList,"test");
    imageList.clear();
//    workerThread->start();
}

LennyGUI::~LennyGUI()
{
    emit shutDownEverything();
    delete ui;
}

void LennyGUI::createBackground(){
//    updateBackground();
//    ui->lennyCanvas->setScene(&graphScene);
}

void LennyGUI::updateBackground(){
    //This is the fun-function, although quite expensive. Only decent way of updating the background gradient so far without making it too big for smaller windows or too small for big windows.
//    QRadialGradient *gradientBackground = new QRadialGradient(0.5,1,ui->lennyCanvas->width()*ui->lennyCanvas->height()/3.8);
//    gradientBackground->setColorAt(1,QColor::fromRgb(0,0,0));
//    gradientBackground->setColorAt(0,QColor::fromRgbF(0.3,0.3,0.3,0.1)); //Definitely want to make this background customizable.
//    QBrush *gradientBrush = new QBrush(*gradientBackground);
//    graphScene.setBackgroundBrush(*gradientBrush);
//    ui->lennyCanvas->resize(graphScene.itemsBoundingRect().width(),graphScene.itemsBoundingRect().width());

    QTimer *progressTimer = new QTimer(this);
    connect(progressTimer,SIGNAL(timeout()),ui->loadBar,SLOT(hide()));
    connect(progressTimer,SIGNAL(timeout()),progressTimer,SLOT(stop()));
    ui->loadBar->show();
    progressTimer->start(500);
}

void LennyGUI::canvasAddItem(QString title, QPixmap poster, QString itemId){
    QLabel *posterLabel = new QLabel;
    QFrame *posterFrame = new QFrame;
    QGraphicsPixmapItem *posterItem = new QGraphicsPixmapItem;
    posterItem->setPixmap(poster);
    qreal itemScale = (50.0+ui->zoomSlider->value())/100.0;
    posterItem->setScale(itemScale);
//    graphScene.addItem(posterItem);
}

void LennyGUI::on_actionUpdate_triggered()
{
    updateBackground();
}

void LennyGUI::importEntry(QString title, QStringList imageLocations, QString itemId){
    QFile imageFile;
    if(!imageLocations.isEmpty())
        foreach(QString file,imageLocations)
            imageFile.setFileName(file);
    if(!imageFile.open(QIODevice::ReadOnly))
        return;
    canvasAddItem(title,QPixmap::fromImage(QImage::fromData(imageFile.readAll())),itemId);
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
