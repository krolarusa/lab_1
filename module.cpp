#include "module.h"
#include <QGridLayout>
#include <QString>
#include <QDoubleValidator>
#include <QMessageBox>
#include <iostream>
#include <cmath>

Module::Module():QWidget()
{
    //le - поля ввода, s - слайдеры
    QObject::connect(box1, SIGNAL(textEdited(QString)), this, SLOT(par1Changed()));
    QObject::connect(box2, SIGNAL(textEdited(QString)), this, SLOT(par2Changed()));
    QObject::connect(box3, SIGNAL(textEdited(QString)), this, SLOT(par3Changed()));
    QObject::connect(box4, SIGNAL(textEdited(QString)), this, SLOT(par4Changed()));
    QObject::connect(s1, SIGNAL(valueChanged(int)), this, SLOT(s1Moved()));
    QObject::connect(s2, SIGNAL(valueChanged(int)), this, SLOT(s2Moved()));
    QObject::connect(s3, SIGNAL(valueChanged(int)), this, SLOT(s3Moved()));
    QObject::connect(s4, SIGNAL(valueChanged(int)), this, SLOT(s4Moved()));

    //создали сетку и разместили всё в ней
    QGridLayout *l = new QGridLayout;

    //подпись с видом цвета
    l->addWidget(colorTypeName, 0, 1, 1, 1);
    //подписи каждого показателя
    l->addWidget(letter1, 1, 0, 1, 1);
    l->addWidget(letter2, 4, 0, 1, 1);
    l->addWidget(letter3, 7, 0, 1, 1);
    l->addWidget(letter4, 10, 0, 1, 1);
    l->addWidget(box1, 1, 1, 1, 2);
    l->addWidget(box2, 4, 1, 1, 2);
    l->addWidget(box3, 7, 1, 1, 2);
    l->addWidget(box4, 10, 1, 1, 2);
    l->addWidget(s1, 2, 0, 2, 3);
    l->addWidget(s2, 5, 0, 2, 3);
    l->addWidget(s3, 8, 0, 2, 3);
    l->addWidget(s4, 11, 0, 2, 3);
    this->setLayout(l);
}

//функции, получающие значения от бегунка и пересчитывающие число
void Module::s1Moved(){
    box1->setText(QString::number(s1->value()));
    //проверка флагов
    if(sliderRecalc){
        par1Changed(true);
    }
    sliderRecalc = true;
    emit sliderMoved();
}
void Module::s2Moved(){
    box2->setText(QString::number(s2->value()));
    if(sliderRecalc){
        par2Changed(true);
    }
    sliderRecalc = true;
    emit sliderMoved();
}
void Module::s3Moved(){
    box3->setText(QString::number(s3->value()));
    if(sliderRecalc){
        par3Changed(true);
    }
    sliderRecalc = true;
    emit sliderMoved();
}
void Module::s4Moved(){
    box4->setText(QString::number(s4->value()));
    if(sliderRecalc){
        par4Changed(true);
    }
    sliderRecalc = true;
    emit sliderMoved();
}

//функция для работы функций для работы со слайдерами
void Module::parChanged(QLineEdit* le, int min, int max, bool needRecalc){
    //проверка валидности значения
    if(le->text().toDouble() > max){
        outOfRangeError(75);
        //возвращение округления
        le->setText(QString::number(max));
    }
    if(le->text().toDouble() < min){
        outOfRangeError(79);
        le->setText(QString::number(min));
    }
    //формирование цвета
    switch(type){
    case RGB:
        color.setRgb(box1->text().toDouble(), box2->text().toDouble(), box3->text().toDouble());
        break;
    case CMYK:
        color.setCmyk(box1->text().toDouble(), box2->text().toDouble(), box3->text().toDouble(), box4->text().toDouble());
        break;
    case LAB:
        color = colorFromLAB(box1->text().toDouble(), box2->text().toDouble(), box3->text().toDouble());
        break;
    }
    //проверка состояния флагов
    if(!needRecalc){
        setSliders();
        emit changed();
    }
    recalc = true;
}

//функции пересчёта числового значения, по движению бегунка
void Module::par1Changed(bool a){
    switch(type){
    case RGB:
        parChanged(box1, 0, 255, a);
        break;
    case CMYK:
        parChanged(box1, 0, 255, a);
        break;
    case LAB:
        parChanged(box1, 0, 100, a);
        break;
    }
}
void Module::par2Changed(bool a){
    switch(type){
    case RGB:
        parChanged(box2, 0, 255, a);
        break;
    case CMYK:
        parChanged(box2, 0, 255, a);
        break;
    case LAB:
        parChanged(box2, -128, 127, a);
        break;
    }
}
void Module::par3Changed(bool a){
    switch(type){
    case RGB:
        parChanged(box3, 0, 255, a);
        break;
    case CMYK:
        parChanged(box3, 0, 255, a);
        break;
    case LAB:
        parChanged(box3, -128, 127, a);
        break;
    }
}
void Module::par4Changed(bool a){
    parChanged(box4, 0, 255, a);
}

//ошибка в случае неверного значения цвета
void Module::outOfRangeError(int s){
    QMessageBox::information(NULL,QObject::tr("Warning"),tr("Value out of range! " ));
    std::cout<<s;
}

//перевод чисел в слайдеры
void Module::setSliders(){
    //тригерим необходимость пересчёта
    setSliderRecalc();
    //пересчитываем
    s1->setValue(box1->text().toInt());
    setSliderRecalc();
    s2->setValue(box2->text().toInt());
    setSliderRecalc();
    s3->setValue(box3->text().toInt());
    setSliderRecalc();
    s4->setValue(box4->text().toInt());
}

//ввод типа для вывода на экран нужной сетки и ограничений
void Module::setType(enum::type t){
    type = t;
    //для контроля численных значений
    QDoubleValidator* v1 = new QDoubleValidator();
    QDoubleValidator* v2 = new QDoubleValidator();
    QDoubleValidator* v3 = new QDoubleValidator();
    QDoubleValidator* v4 = new QDoubleValidator();
    switch (t)
    {
    case type::RGB:
        letter4->hide();
        box4->hide();
        s4->hide();
        colorTypeName->setText("RGB");
        letter1->setText("R");
        letter2->setText("G");
        letter3->setText("B");
        v1->setRange(0.0,255.0, 2);
        v1->setNotation(QDoubleValidator::StandardNotation);
        s1->setRange(0, 255);
        v2->setRange(0.0,255.0, 2);
        v2->setNotation(QDoubleValidator::StandardNotation);
        s2->setRange(0, 255);
        v3->setRange(0.0,255.0, 2);
        v3->setNotation(QDoubleValidator::StandardNotation);
        s3->setRange(0, 255);
        box1->setValidator(v1);
        box2->setValidator(v2);
        box3->setValidator(v3);
        break;
    case type::CMYK:
        letter4->show();
        box4->show();
        s4->show();
        colorTypeName->setText("CMYK");
        letter1->setText("C");
        letter2->setText("M");
        letter3->setText("Y");
        letter4->setText("K");
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
        box1->setValidator(v1);
        box2->setValidator(v2);
        box3->setValidator(v3);
        box4->setValidator(v4);
        break;
    case type::LAB:
        letter4->hide();
        box4->hide();
        s4->hide();
        colorTypeName->setText("LAB");
        letter1->setText("L");
        letter2->setText("a");
        letter3->setText("b");
        v1->setRange(0.0,100.0, 2);
        v1->setNotation(QDoubleValidator::StandardNotation);
        s1->setRange(0, 100);
        v2->setRange(-128.0,127.0, 2);
        v2->setNotation(QDoubleValidator::StandardNotation);
        s2->setRange(-128, 127);
        v3->setRange(-128.0,127.0, 2);
        v3->setNotation(QDoubleValidator::StandardNotation);
        s3->setRange(-128, 127);
        box1->setValidator(v1);
        box2->setValidator(v2);
        box3->setValidator(v3);
        break;
    }
    setColor(color);
}

//настраивает текст по цвету и фиксирует флаг
void Module::setColor(QColor col){
    color = col;
    switch(type){
    case type::RGB:
        setRGB();
        break;
    case type::CMYK:
        setCMYK();
        break;
    case type::LAB:
        setLAB();
        break;
    }
    setSliders();
}

//функции сравнивают действующий текст с соответствующей цветовой составляющей цвета
//и меняет при необходимости
void Module::setRGB(){
    if(box1->text() != color.red()){
        box1->setText(QString::number(color.red()));
    }
    if(box2->text() != color.green()){
        box2->setText(QString::number(color.green()));
    }
    if(box3->text() != color.blue()){
        box3->setText(QString::number(color.blue()));
    }
}
void Module::setCMYK(){
    if(box1->text() != color.cyan()){
        box1->setText(QString::number(color.cyan()));
    }
    if(box2->text() != color.magenta()){
        box2->setText(QString::number(color.magenta()));
    }
    if(box3->text() != color.yellow()){
        box3->setText(QString::number(color.yellow()));
    }
    if(box4->text() != color.black()){
        box4->setText(QString::number(color.black()));
    }
}
void Module::setLAB(){
    double xw = 95.047;
    double yw = 100;
    double zw = 108.883;
    double r = color.red();
    double g = color.green();
    double b = color.blue();
    r/=255;
    b/=255;
    g/=255;
    if(r>0.04045){
        r = pow((r+0.055)/1.055, 2.4);
    }else{
        r/=12.92;
    }
    if(g>0.04045){
        g = pow((g+0.055)/1.055, 2.4);
    }else{
        g/=12.92;
    }
    if(b>0.04045){
        b = pow((b+0.055)/1.055, 2.4);
    }else{
        b/=12.92;
    }
    r*=100;
    g*=100;
    b*=100;
    double x = (int)(r * 0.4124 + g * 0.3576 + b * 0.1805);
    double y = (int)(r * 0.2126 + g * 0.7152 + b * 0.0722);
    double z = (int)(r * 0.0193 + g * 0.1192 + b * 0.9505);
    if(box1->text() != QString::number((int)(116*func_for_LAB2(y/yw) - 16))){
        box1->setText(QString::number((int)(116*func_for_LAB2(y/yw) - 16)));
    }
    if(box2->text() != QString::number((int)(500*(func_for_LAB2(x/xw) - func_for_LAB2(y/yw))))){
        box2->setText(QString::number((int)(500*(func_for_LAB2(x/xw) - func_for_LAB2(y/yw)))));
    }
    if(box3->text() != QString::number((int)(200*(func_for_LAB2(y/yw) - func_for_LAB2(z/zw))))){
        box3->setText(QString::number((int)(200*(func_for_LAB2(y/yw) - func_for_LAB2(z/zw)))));
    }
}

//перевод из LAB в RGB
QColor Module::colorFromLAB(double l, double a, double b){
    double xw = 95.047;
    double yw = 100;
    double zw = 108.883;
    double x = func_for_LAB1(a/500 + ((l+16)/116)) * yw;
    double y = func_for_LAB1((l + 16)/116) * xw;
    double z = func_for_LAB1((l + 16)/116 - b/200) * zw;
    double r;
    double g;
    double bl;
    x/=100;
    y/=100;
    z/=100;
    r = (int)(x*255);
    g = (int)(y*255);
    bl = (int)(z*255);
    if(r<0){
        r = 0;
        outOfRangeError(496);
    }else if(r>255){
        r = 255;
        outOfRangeError(499);
    }
    if(g<0){
        g = 0;
        outOfRangeError(503);
    }else if(g>255){
        g = 255;
        outOfRangeError(506);
    }
    if(bl<0){
        bl = 0;
        outOfRangeError(510);
    }else if(bl>255){
        bl = 255;
        outOfRangeError(513);
    }
    QColor col;
    col.setRgb(r, g, bl);
    return col;
}

//функции для расчётов в LAB
double Module::func_for_LAB1(double x) {
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
double Module::func_for_LAB2(double x){
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
