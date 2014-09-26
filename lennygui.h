#ifndef LENNYGUI_H
#define LENNYGUI_H

#include <QMainWindow>

#include <QTimer>
#include <QDebug>
#include <QThread>
#include <QFile>
#include <QFileDialog>
#include <QPixmap>
#include <QLabel>
#include <QFrame>
#include <QEventLoop>

#include <QQmlComponent>
#include <QQmlProperty>
#include <QQuickItem>
#include <QQmlEngine>
#include <QQmlContext>

#include <QStandardItemModel>

namespace Ui {
class LennyGUI;
}

class LennyGUI : public QMainWindow
{
    Q_OBJECT

public:
    explicit LennyGUI(QWidget *parent = 0);
    ~LennyGUI();

    QStandardItemModel itemGridModel;

private slots:
    void on_zoomSlider_valueChanged(int value);
    void on_actionFullscreen_triggered();
    void importObjects(QHash<QString,QVariant> importedHash);

    void execLennyParser();
    void createQmlRoot();

    void on_actionImport_objects_triggered();
public slots:
    void executeItem(QString itemId);

signals:
    void shutDownEverything();

    void scaleChanged();

private:
    Ui::LennyGUI *ui;
    QString inputFile;
    QThread *workerThread;
    QTimer *progressTimer;

    QStandardItem *stdItem;

    QQmlComponent *initComponent;
    QHash<QString,QVariant> currentItems;

    void initItemModel();
    void addToItemModel(QHash<QString,QVariant> importedHash);

    //QML-related


    //Posteritem
//    QLabel *posterLabel;
//    QGraphicsPixmapItem *posterItem;
//    QFrame *posterFrame;
};

#endif // LENNYGUI_H
