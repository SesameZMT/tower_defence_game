#include "begin.h"

#include <QApplication>
#include <QPushButton>
#include <QLabel>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    begin w(nullptr);
    QPushButton quit("退出",&w);
    QLabel lab(&w);//设置文本框

    quit.resize(100,40);//设置quit按钮的大小
    quit.setFont( QFont( "Times", 18, QFont::Bold ) );//设置quit的字体
    quit.move(500,320);//将quit按钮移至中央

    lab.setAlignment(Qt::AlignCenter);
    lab.setGeometry(450,10,200,200);
    lab.setStyleSheet("QLabel{font:50px;color:black;background-color:rgb(f9,f9,f9);}");
    lab.setText("塔防游戏");

    QObject::connect(&quit, &QPushButton::clicked, &a, &QApplication::quit);//将点击和退出进行关联
    w.show();

    lab.show();//显示文本框
    return a.exec();
}
