#ifndef STARTFROM_H
#define STARTFROM_H

#include <QWidget>
#include <QMainWindow>
#include <QPaintEvent>

#include "mainwindow.h"//包含mainwindow文件


namespace Ui {class startfrom;}

class startfrom : public QMainWindow
{
    Q_OBJECT
public:
    startfrom(QWidget *parent = nullptr);
    ~startfrom();
    void paintEvent(QPaintEvent *event);//只用添加这个绘画类函数就可以了
public slots:
    void handler1() {
        mainwindow=new MainWindow();
        mainwindow->setPath(":/map.jpeg");
        mainwindow->loadTowerPosition1();
        mainwindow->addWayPoint1();
        mainwindow->a = 1;
        mainwindow->show();
    }
    void handler2() {
        mainwindow=new MainWindow();
        mainwindow->setPath(":/map2.jpeg");
        mainwindow->loadTowerPosition2();
        mainwindow->addWayPoint2();
        mainwindow->a = 2;
        mainwindow->show();
    }
    void handler3() {
        mainwindow=new MainWindow();
        mainwindow->setPath(":/map3.jpeg");
        mainwindow->loadTowerPosition3();
        mainwindow->addWayPoint3();
        mainwindow->a = 3;
        mainwindow->show();
    }
private:
    Ui::startfrom *ui;
    MainWindow *mainwindow;
};

#endif // STARTFROM_H
