#include "begin.h"
#include "ui_begin.h"


begin::begin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::begin)
{
    ui->setupUi(this);
    this->setFixedSize(1050,800);
    setWindowTitle("开始");
    connect(ui->pushButton,&QPushButton::clicked,this, &begin::handler);
}

begin::~begin()
{
}

void begin::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    QString path(":/background.jpeg");
    painter.drawPixmap(0,0,1050,800,path);
}

