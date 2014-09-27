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
#include <QProcess>
#include <QJsonObject>

#include <QQmlComponent>
#include <QQmlProperty>
#include <QQuickItem>
#include <QQmlEngine>
#include <QQmlContext>

#include <QStandardItemModel>
#include <QStandardItem>

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
    void initAll(QString filename);

private slots:
    void on_zoomSlider_valueChanged(int value);
    void on_actionFullscreen_triggered();
    void importObjects(QHash<QString,QVariant> importedHash);
    void importOptions(QJsonObject optionObject);

    void execLennyParser(QString filename);
    void createQmlRoot();

    void on_actionImport_objects_triggered();
    void on_actionInitialize_QML_triggered();

    void applyImportedOptions();

public slots:
    void executeItem(QString itemId);

signals:
    void shutDownEverything();
    void optionsImported();

private:
    Ui::LennyGUI *ui;
    QThread *workerThread;
    QTimer *progressTimer;

    QStandardItem *stdItem;
    QList<QStandardItem*> stdRow;
    QHash<QString,QVariant> startOpts;

    void initItemModel();
    void addToItemModel(QHash<QString,QVariant> importedHash);

    //QML-related


    //Posteritem
//    QLabel *posterLabel;
//    QGraphicsPixmapItem *posterItem;
//    QFrame *posterFrame;
};

#endif // LENNYGUI_H
