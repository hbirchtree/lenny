#include "lennygui.h"
#include "ui_lennygui.h"

LennyGUI::LennyGUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LennyGUI)
{
    ui->setupUi(this);
    ui->centralWidget->setStyleSheet("background-color:black;");
    createBackground();
    ui->progressBar->setMaximum(0);
    ui->progressBar->setFormat(tr("Running"));
    updateBackground();
}

LennyGUI::~LennyGUI()
{
    delete ui;
}

void LennyGUI::createBackground(){
    QRadialGradient *gradientBackground = new QRadialGradient(0.5,1,ui->lennyCanvas->width()*ui->lennyCanvas->height()/3.8);
    gradientBackground->setColorAt(1,QColor::fromRgb(0,0,0));
    gradientBackground->setColorAt(0,QColor::fromRgbF(0.5,0.5,0.5,0.4));
//    gradientBackground.setRadius(ui->lennyCanvas->width()*ui->lennyCanvas->height()/3.8);
    QBrush *gradientBrush = new QBrush(*gradientBackground);
    QGraphicsScene *graphScene = new QGraphicsScene(this);
    graphScene->setBackgroundBrush(*gradientBrush);
    ui->lennyCanvas->setScene(graphScene);
}

void LennyGUI::updateBackground(){
    //I have no idea what I am doing here.
//    QRadialGradient *gradBack = gradientBackground;
//    gradBack->setColorAt(1,QColor::fromRgb(0,0,0));
//    gradBack->setColorAt(0,QColor::fromRgbF(0.5,0.5,0.5,0.4));
//    gradBack->setRadius(ui->lennyCanvas->width()*ui->lennyCanvas->height()/3.8);
//    QBrush newBrush(*gradBack);
//    gradientBrush->swap(newBrush);
}
