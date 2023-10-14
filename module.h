#ifndef MODULE_H
#define MODULE_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QSlider>

enum type{
    RGB,
    CMYK,
    LAB
};

class Module:public QWidget
{
    Q_OBJECT

public:
    Module();
    void parChanged(QLineEdit*, int min, int max, bool);
    void outOfRangeError(int);
    void setType(type t);
    void setColor(QColor);
    //возврат цвета
    QColor getColor(){
        return color;
    }
    //флаг необходимости пересчёта
    void setRecalc(){
        recalc = false;
    }
    //флаг необходимости передвижения слайдера
    void setSliderRecalc(){
        sliderRecalc = false;
    }
signals:
    void changed();
    void sliderMoved();
private slots:
    void s1Moved();
    void s2Moved();
    void s3Moved();
    void s4Moved();

    void par1Changed(bool = false);
    void par2Changed(bool = false);
    void par3Changed(bool = false);
    void par4Changed(bool = false);

private:
    void setSliders();

    void setRGB();
    void setCMYK();
    void setLAB();
    //для получения цвета из CMYK и RGB есть встроенные функции
    QColor colorFromLAB(double l, double a, double b);
    double func_for_LAB1(double);
    double func_for_LAB2(double);

    bool recalc = true;
    bool sliderRecalc = false;

    QColor color;
    type type;

    QLabel* colorTypeName = new QLabel;
    QLabel* letter1 = new QLabel;
    QLabel* letter2 = new QLabel;
    QLabel* letter3 = new QLabel;
    QLabel* letter4 = new QLabel;

    QLineEdit* box1 = new QLineEdit;
    QLineEdit* box2 = new QLineEdit;
    QLineEdit* box3 = new QLineEdit;
    QLineEdit* box4 = new QLineEdit;

    QSlider* s1 = new QSlider(Qt::Horizontal);
    QSlider* s2 = new QSlider(Qt::Horizontal);
    QSlider* s3 = new QSlider(Qt::Horizontal);
    QSlider* s4 = new QSlider(Qt::Horizontal);
};

#endif // MODULE_H
