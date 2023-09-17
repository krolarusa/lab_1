#include "module.h"
#include <QGridLayout>
#include <QString>
#include <QDoubleValidator>
#include <QMessageBox>
#include <iostream>
#include <cmath>

Module::Module():QWidget()
{
    QObject::connect(le1, SIGNAL(textEdited(QString)), this, SLOT(le1Changed()));
    QObject::connect(le2, SIGNAL(textEdited(QString)), this, SLOT(le2Changed()));
    QObject::connect(le3, SIGNAL(textEdited(QString)), this, SLOT(le3Changed()));
    QObject::connect(le4, SIGNAL(textEdited(QString)), this, SLOT(le4Changed()));
    QObject::connect(s1, SIGNAL(valueChanged(int)), this, SLOT(s1Moved()));
    QObject::connect(s2, SIGNAL(valueChanged(int)), this, SLOT(s2Moved()));
    QObject::connect(s3, SIGNAL(valueChanged(int)), this, SLOT(s3Moved()));
    QObject::connect(s4, SIGNAL(valueChanged(int)), this, SLOT(s4Moved()));
    QGridLayout *l = new QGridLayout;
    lsystem->setAlignment(Qt::AlignCenter);
    l->addWidget(lsystem, 0, 1, 1, 1);
    l->addWidget(l1, 1, 0, 1, 1);
    l->addWidget(l2, 4, 0, 1, 1);
    l->addWidget(l3, 7, 0, 1, 1);
    l->addWidget(l4, 10, 0, 1, 1);
    l->addWidget(le1, 1, 1, 1, 2);
    l->addWidget(le2, 4, 1, 1, 2);
    l->addWidget(le3, 7, 1, 1, 2);
    l->addWidget(le4, 10, 1, 1, 2);
    l->addWidget(s1, 2, 0, 2, 3);
    l->addWidget(s2, 5, 0, 2, 3);
    l->addWidget(s3, 8, 0, 2, 3);
    l->addWidget(s4, 11, 0, 2, 3);
    this->setLayout(l);
}

void Module::s1Moved(){

}

void Module::s2Moved(){

}

void Module::s3Moved(){

}

void Module::s4Moved(){

}

void Module::leChanged(QLineEdit* le, int min, int max, bool needRecalc){

}

void Module::le1Changed(bool a){

}

void Module::le2Changed(bool a){

}

void Module::le3Changed(bool a){

}

void Module::le4Changed(bool a){

}

void Module::outOfRangeError(int s){
    QMessageBox::information(NULL,QObject::tr("Warning"),tr("Value out of range! " ));
    std::cout<<s;
}

void Module::setSliders(){
}

void Module::setType(enum::type t){
    type = t;
    QDoubleValidator* v1 = new QDoubleValidator();
    QDoubleValidator* v2 = new QDoubleValidator();
    QDoubleValidator* v3 = new QDoubleValidator();
    QDoubleValidator* v4 = new QDoubleValidator();
    switch (t)
    {
    case type::RGB:
        l4->hide();
        le4->hide();
        s4->hide();
        lsystem->setText("RGB");
        l1->setText("R");
        l2->setText("G");
        l3->setText("B");
        v1->setRange(0.0,255.0, 2);
        v1->setNotation(QDoubleValidator::StandardNotation);
        s1->setRange(0, 255);
        v2->setRange(0.0,255.0, 2);
        v2->setNotation(QDoubleValidator::StandardNotation);
        s2->setRange(0, 255);
        v3->setRange(0.0,255.0, 2);
        v3->setNotation(QDoubleValidator::StandardNotation);
        s3->setRange(0, 255);
        le1->setValidator(v1);
        le2->setValidator(v2);
        le3->setValidator(v3);
        break;
    case type::CMYK:
        l4->show();
        le4->show();
        s4->show();
        lsystem->setText("CMYK");
        l1->setText("C");
        l2->setText("M");
        l3->setText("Y");
        l4->setText("K");
        v1->setRange(0.0,255.0, 2);
        v1->setNotation(QDoubleValidator::StandardNotation);
        s1->setRange(0, 255);
        v2->setRange(0.0,255.0, 2);
        v2->setNotation(QDoubleValidator::StandardNotation);
        s2->setRange(0, 255);
        v3->setRange(0.0,255.0, 2);
        v3->setNotation(QDoubleValidator::StandardNotation);
        s3->setRange(0, 255);
        v4->setRange(0.0,255.0, 2);
        v4->setNotation(QDoubleValidator::StandardNotation);
        s4->setRange(0, 255);
        le1->setValidator(v1);
        le2->setValidator(v2);
        le3->setValidator(v3);
        le4->setValidator(v4);
        break;
    case type::LAB:
        l4->hide();
        le4->hide();
        s4->hide();
        lsystem->setText("LAB");
        l1->setText("L");
        l2->setText("a");
        l3->setText("b");
        v1->setRange(0.0,100.0, 2);
        v1->setNotation(QDoubleValidator::StandardNotation);
        s1->setRange(0, 100);
        v2->setRange(-128.0,127.0, 2);
        v2->setNotation(QDoubleValidator::StandardNotation);
        s2->setRange(-128, 127);
        v3->setRange(-128.0,127.0, 2);
        v3->setNotation(QDoubleValidator::StandardNotation);
        s3->setRange(-128, 127);
        le1->setValidator(v1);
        le2->setValidator(v2);
        le3->setValidator(v3);
        break;
    case type::HSV:
        l4->hide();
        le4->hide();
        s4->hide();
        lsystem->setText("HSV");
        l1->setText("H");
        l2->setText("S");
        l3->setText("V");
        v1->setRange(0.0,360.0, 2);
        v1->setNotation(QDoubleValidator::StandardNotation);
        s1->setRange(0, 359);
        v2->setRange(0.0,255.0, 2);
        v2->setNotation(QDoubleValidator::StandardNotation);
        s2->setRange(0, 255);
        v3->setRange(0.0,255.0, 2);
        v3->setNotation(QDoubleValidator::StandardNotation);
        s3->setRange(0, 255);
        le1->setValidator(v1);
        le2->setValidator(v2);
        le3->setValidator(v3);
        break;
    case type::HLS:
        l4->hide();
        le4->hide();
        s4->hide();
        lsystem->setText("HLS");
        l1->setText("H");
        l2->setText("L");
        l3->setText("S");
        v1->setRange(0.0,255.0, 2);
        v1->setNotation(QDoubleValidator::StandardNotation);
        s1->setRange(0, 255);
        v2->setRange(0.0,255.0, 2);
        v2->setNotation(QDoubleValidator::StandardNotation);
        s2->setRange(0, 255);
        v3->setRange(0.0,255.0, 2);
        v3->setNotation(QDoubleValidator::StandardNotation);
        s3->setRange(0, 255);
        le1->setValidator(v1);
        le2->setValidator(v2);
        le3->setValidator(v3);
        break;
    case type::XYZ:
        l4->hide();
        le4->hide();
        s4->hide();
        lsystem->setText("XYZ");
        l1->setText("X");
        l2->setText("Y");
        l3->setText("Z");
        v1->setRange(0.0,100.0, 2);
        v1->setNotation(QDoubleValidator::StandardNotation);
        s1->setRange(0, 100);
        v2->setRange(0.0,100.0, 2);
        v2->setNotation(QDoubleValidator::StandardNotation);
        s2->setRange(0, 100);
        v3->setRange(0.0,100.0, 2);
        v3->setNotation(QDoubleValidator::StandardNotation);
        s3->setRange(0, 100);
        le1->setValidator(v1);
        le2->setValidator(v2);
        le3->setValidator(v3);
        break;
    }
    setColor(color);
}

void Module::setColor(QColor col){

}

void Module::setRGB(){

}

void Module::setCMYK(){

}

void Module::setLAB(){

}

void Module::setXYZ(){

}

void Module::setHSV(){

}

void Module::setHLS(){

}

QColor Module::colorFromXYZ(double x, double y, double z){
    double r;
    double g;
    double b;
    x/=100;
    y/=100;
    z/=100;
    r = 3.2404542 * x - 0.4985314 * y - 0.4985314 * z;
    g = -0.9692660 * x + 1.8760108 * y + 0.0415560 * z;
    b = 0.0556434 * x - 0.2040259 * y + 1.0572252 * z;
    QColor col;
    col.setRgb(r,g,b);
    return col;
}

QColor Module::colorFromLAB(double l, double a, double b){
    double xw = 95.047;
    double yw = 100;
    double zw = 108.883;
    double x = func1(a/500 + ((l+16)/116)) * yw;
    double y = func1((l + 16)/116) * xw;
    double z = func1((l + 16)/116 - b/200) * zw;
    double r;
    double g;
    double bl;
    x/=100;
    y/=100;
    z/=100;
    r = 3.2404542 * x - 0.4985314 * y - 0.4985314 * z;
    g = -0.9692660 * x + 1.8760108 * y + 0.0415560 * z;
    bl = 0.0556434 * x - 0.2040259 * y + 1.0572252 * z;
    QColor col;
    col.setRgb(r, g, bl);
    return col;
}

double Module::func1(double x) {
    if (x >= 0.008856)
    {
    x = pow(x, 3);
    }
    else
    {
    x = (x - 16/116)/7.787;
    }
    return x;
}

double Module::func2(double x){
    if (x >= 0.008856)
    {
        x = pow(x, 1/3.0);
    }
    else
    {
        x = 7.787*x + 16/116;
    }
    return x;
}
