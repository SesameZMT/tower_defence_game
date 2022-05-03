#include "startfrom.h"
#include "ui_startfrom.h"


startfrom::startfrom(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::startfrom)
{
    ui->setupUi(this);
    this->setFixedSize(1050,800);
        setWindowTitle("选择关卡");
        connect(ui->pushButton,&QPushButton::clicked,this, &startfrom::handler1);
        connect(ui->pushButton_2,&QPushButton::clicked,this, &startfrom::handler2);
        connect(ui->pushButton_3,&QPushButton::clicked,this, &startfrom::handler3);
}

startfrom::~startfrom() {

}

void startfrom::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    QString path(":/background.jpeg");
    painter.drawPixmap(0,0,1050,800,path);
}
