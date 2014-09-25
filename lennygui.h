#ifndef LENNYGUI_H
#define LENNYGUI_H

#include <QMainWindow>
#include <QRadialGradient>
#include <QBrush>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QTimer>
#include <QDebug>
#include <QThread>
#include <QFile>
#include <QPixmap>
#include <QLabel>
#include <QFrame>

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
    void createBackground();
    void updateBackground();
    void canvasAddItem(QString title,QPixmap poster,QString itemId);
    void on_actionUpdate_triggered();
    void importEntry(QString title,QStringList imageLocations,QString itemId);

    void on_zoomSlider_valueChanged(int value);

    void on_actionFullscreen_triggered();

signals:
    void shutDownEverything();

private:
    Ui::LennyGUI *ui;

    QString inputFile;
    QThread *workerThread;
    QGraphicsScene graphScene;
    QBrush *gradientBrush;
    QRadialGradient *gradientBackground;
    QTimer *progressTimer;

    //Posteritem
    QLabel *posterLabel;
    QGraphicsPixmapItem *posterItem;
    QFrame *posterFrame;
};

#endif // LENNYGUI_H
