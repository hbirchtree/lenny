#ifndef LENNYGUI_H
#define LENNYGUI_H

#include <QMainWindow>
#include <QRadialGradient>
#include <QBrush>
#include <QGraphicsScene>
#include <QGraphicsItem>

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

private:
    Ui::LennyGUI *ui;

    QGraphicsScene *graphScene;
    QBrush *gradientBrush;
    QRadialGradient *gradientBackground;
};

#endif // LENNYGUI_H
