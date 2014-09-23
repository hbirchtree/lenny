#include "lennygui.h"
#include "ui_lennygui.h"

LennyGUI::LennyGUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LennyGUI)
{
    ui->setupUi(this);
    ui->centralWidget->setStyleSheet("background-color:black;");
    connect(ui->actionQuit,SIGNAL(triggered()),this,SLOT(close()));
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
    QRadialGradient gradientBackground;
    gradientBackground.setColorAt(1,QColor::fromRgb(0,0,0));
    gradientBackground.setColorAt(0,QColor::fromRgbF(0.3,0.3,0.3,0.6));
    gradientBackground.setRadius(ui->lennyCanvas->width()*ui->lennyCanvas->height()/3.8);
    QBrush *gradientBrush = new QBrush(gradientBackground);
    QGraphicsScene *graphScene = new QGraphicsScene;
    graphScene->setBackgroundBrush(*gradientBrush);
    ui->lennyCanvas->setScene(graphScene);
}

void LennyGUI::updateBackground(){
    graphScene->setFocus();
}
