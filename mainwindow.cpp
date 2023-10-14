#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "module.h"
#include <QGridLayout>
#include <QPalette>
#include <QColorDialog>
#include <QObject>
#include <QFont>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    //соеденили кнопки и бегунки
    QObject::connect(colorButton, SIGNAL(clicked()), this, SLOT(colorButtonClicked()));
    QObject::connect(rgbMod, SIGNAL(changed()), this, SLOT(changeColorRGB()));
    QObject::connect(labMod, SIGNAL(changed()), this, SLOT(changeColorLab()));
    QObject::connect(cmykMod, SIGNAL(changed()), this, SLOT(changeColorCMYK()));
    QObject::connect(rgbMod, SIGNAL(sliderMoved()), this, SLOT(changeColorRGB()));
    QObject::connect(labMod, SIGNAL(sliderMoved()), this, SLOT(changeColorLab()));
    QObject::connect(cmykMod, SIGNAL(sliderMoved()), this, SLOT(changeColorCMYK()));

    QPalette p = QPalette();
    //выбрали для окна белый цвет
    p.setBrush(QPalette::Background, Qt::white);
    //закрасили белым
    wColor->setAutoFillBackground(true);
    wColor->setPalette(p);
    //вывели в окно цветовой прямоугольник
    ui->setupUi(this);

    //создали сетчатый макет, чтобы настроить размещение различных виджетов внутри этого макета
    QGridLayout* l = new QGridLayout;
    //создали текстовый виджет
    QLabel* selectedColorLabel = new QLabel;
    //подписали виджет
    selectedColorLabel->setText("Selected color:");
    //подписали кнопку выбора цвета
    colorButton->setText("Choose color");
    rgbMod->setType(type::RGB);
    labMod->setType(type::LAB);
    cmykMod->setType(type::CMYK);

    //размещение в сетке, где первое число номер строки, второе столбца,
    //третье число строк, четвёртое число столбцов
    l->addWidget(selectedColorLabel, 0, 1, 1, 2);
    l->addWidget(wColor, 1, 1, 2, 2);
    l->addWidget(colorButton, 1, 4, 2, 1);
    l->addWidget(rgbMod, 3, 0, 4, 2);
    l->addWidget(labMod, 3, 2, 4, 2);
    l->addWidget(cmykMod, 3, 4, 4, 2);
    //выводим в окно макет
    ui->centralwidget->setLayout(l);
}

//выбор цвета нажатием
void MainWindow::colorButtonClicked(){
    //открыли выбор
    color = QColorDialog::getColor();
    //поменяли все 3 значения
    setColors();
    //перекрасили цвет
    setwColor();
}

//меняем  цвета, если пользователь численно поменял один цвет
void MainWindow::changeColorRGB(){
    //пересчитываем
    labMod->setRecalc();
    cmykMod->setRecalc();
    //двигаем слайдеры
    labMod->setSliderRecalc();
    cmykMod->setSliderRecalc();
    //ввели введённый цвет в переменную
    color = rgbMod->getColor();
    //переключили остальный показатели
    labMod->setColor(color);
    cmykMod->setColor(color);
    //вывели цвет в окне
    setwColor();
}
void MainWindow::changeColorLab(){
    rgbMod->setRecalc();
    cmykMod->setRecalc();
    rgbMod->setSliderRecalc();
    cmykMod->setSliderRecalc();
    color = labMod->getColor();
    rgbMod->setColor(color);
    cmykMod->setColor(color);
    setwColor();
}
void MainWindow::changeColorCMYK(){
    labMod->setRecalc();
    rgbMod->setRecalc();
    labMod->setSliderRecalc();
    rgbMod->setSliderRecalc();
    color = cmykMod->getColor();
    labMod->setColor(color);
    rgbMod->setColor(color);
    setwColor();
}

//ввод цвета в три модели сразу, используется при смене цвета через окно
void MainWindow::setColors(){
    rgbMod->setColor(color);
    labMod->setColor(color);
    cmykMod->setColor(color);
}
//перекрашиваем прямоугольник
void MainWindow::setwColor(){
    QPalette p = QPalette();
    p.setBrush(QPalette::Background, color);
    wColor->setAutoFillBackground(true);
    wColor->setPalette(p);
}

//закрыли окно
MainWindow::~MainWindow()
{
    delete ui;
}
