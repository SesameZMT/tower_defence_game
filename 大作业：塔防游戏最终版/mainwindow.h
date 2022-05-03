#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPaintEvent>
#include <QMouseEvent>

#include "waypoint.h"
#include "towerposition.h"
#include "tower.h"
#include "enemy.h"
#include "bullet.h"
#include "selectbutton.h"
#include "selectbutton2.h"
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
class selectButton;

class Tower;

class wayPoint;//新增对wayPoint类的说明

class Enemy;

class Bullet;

class TowerPosition;

class selectButton2;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void addWayPoint1();//用来添加航点的函数
    void loadTowerPosition1();//用来加载防御塔坑的函数

    void addWayPoint2();
    void loadTowerPosition2();

    void loadTowerPosition3();
    void addWayPoint3();

    QString getPath();//得到地图图片路径
    void setPath(QString path);//设置地图图片路径

    void getHpDamaged();//敌人进入基地内部，基地要扣血
    void awardGlod();//敌人死亡，奖励金钱
    void removeEnemy(QPointer<Enemy> enemy);//敌人死亡，在mainwindow中要移除
    QList<QPointer<Enemy>> getEnemyList();//得到Enemy*的list

    bool loadWaves(int a);//加载敌人的函数
    int a;

    void removeBullet(QPointer<Bullet> bullet);
    void addBullet(QPointer<Bullet> bullet);

    void drawHp(QPainter * painter)const;//画出当前基地血量的信息
    void drawGlod(QPainter * painter)const;//画出当前玩家金钱的信息
    void drawWaves(QPainter * painter)const;//画出当前的波数信息
    bool canBuyTower();

    void doGameOver();//执行游戏结束

    bool canBuyTower2();//判断是否可以买第二种塔
    bool canBuyTower3();//判断是否可以买第三种塔
    void removeButton(selectButton * button);//在mainwindow中对button进行移除

    void removeButton2(selectButton2 * button);//在mainwindow中对button2进行移除
    void removeTower(Tower * tower);

    bool canUpdate1();//判断是否可以第一次升级
    bool canUpdate2();//判断是否可以第二次升级

private:
    Ui::MainWindow *ui;
    QList<wayPoint *> m_wayPointList;//用来储存航点的list
    QList<TowerPosition > m_towerPositionList;//用来储存防御塔坑的list
    QList<QPointer<Tower>> m_towerList;//用来储存防御塔的list

    QList<QPointer<Enemy>> m_enemyList;//用来储存敌人的list
    int m_playerHp;//基地的血量
    int m_playerGlod;//初始金钱

    int m_waves;//波数
    bool m_gameWin;
    bool m_gameLose;

    QList<QPointer<Bullet>> m_bulletList;//用来储存子弹的list

    QList<QPointer<selectButton>> m_selectButtonList;//用来储存selectButton的list

    QList<QPointer<selectButton2>> m_selectButton2List;//用来储存selectButton2的list

    QString m_path;

private slots://私有信号槽，将Enemy，Tower和后续的Bullet连接
    void updateMap();
    void gameStart();

protected:
    void paintEvent(QPaintEvent*);
    void mousePressEvent(QMouseEvent *);//鼠标点击类函数
};
#endif // MAINWINDOW_H
