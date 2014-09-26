#ifndef LENNYGUI_H
#define LENNYGUI_H

#include <QMainWindow>

#include <QTimer>
#include <QDebug>
#include <QThread>
#include <QFile>
#include <QPixmap>
#include <QLabel>
#include <QFrame>
#include <QEventLoop>

#include <QQmlComponent>
#include <QQmlProperty>

namespace Ui {
class LennyGUI;
}

class LennyGUI : public QMainWindow
{
    Q_OBJECT

public:
    explicit LennyGUI(QWidget *parent = 0);
    ~LennyGUI();

private slots:
    void importEntry(QString title,QStringList imageLocations,QString itemId);
    void on_zoomSlider_valueChanged(int value);
    void on_actionFullscreen_triggered();
    void importObjects();

    void createQmlRoot();

    void on_actionImport_objects_triggered();

signals:
    void shutDownEverything();

private:
    Ui::LennyGUI *ui;
    QString inputFile;
    QThread *workerThread;
    QTimer *progressTimer;

    //QML-related


    //Posteritem
//    QLabel *posterLabel;
//    QGraphicsPixmapItem *posterItem;
//    QFrame *posterFrame;
};

#endif // LENNYGUI_H
