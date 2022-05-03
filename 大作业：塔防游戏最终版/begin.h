#ifndef BEGIN_H
#define BEGIN_H

#include <QWidget>
#include <QMainWindow>
#include <QPaintEvent>

#include "startfrom.h"

namespace Ui {
class begin;
}

class startfrom;

class begin : public QMainWindow
{
    Q_OBJECT

public:
    explicit begin(QWidget *parent = nullptr);
    ~begin();
    void paintEvent(QPaintEvent *event);//只用添加这个绘画类函数就可以了

public slots:
    void handler() {
        startFrom = new startfrom();
        startFrom->show();
    }

private:
    Ui::begin *ui;
    startfrom *startFrom;
};

#endif // BEGIN_H
