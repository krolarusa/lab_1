#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include "module.h"
#include <QColor>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setwColor();

private slots:
    //смена цвета по кнопке
    void colorButtonClicked();
    //смена двух модулей по смене одного
    void changeColorRGB();
    void changeColorLab();
    void changeColorCMYK();

private:
    void setColors();
    Ui::MainWindow *ui;
    Module* rgbMod = new Module;
    Module* labMod = new Module;
    Module* cmykMod = new Module;
    QWidget* wColor = new QWidget;
    QPushButton* colorButton = new QPushButton;
    QColor color;
};
#endif // MAINWINDOW_H
