#ifndef TOWER_H
#define TOWER_H

#include <QObject>
#include <QPoint>
#include <QSize>
#include <QString>
#include <QTimer>

#include "mainwindow.h"
#include "enemy.h"

class MainWindow;
class QPainter;
class Enemy;
class QTimer;
class Tower;

class Tower : public QObject
{
    Q_OBJECT
public:
    Tower(QPoint pos,MainWindow * game,QString path,int damage,int rate);
    Tower();
    ~Tower();

    void draw(QPainter * painter)const;//画出防御塔

    void attackEnemy();//攻击敌人
    void targetKilled();//当目标被击杀后
    void chooseEnemyFromAttack(QPointer<Enemy> enemy);//从可以攻击的敌人中，选出攻击的敌人

    void removeBullet();//移除防御塔产生的子弹
    void lostSightOfEnemy();//丢失攻击目标的视野
    void checkEnemyInRange();//检查敌人是否在攻击范围内
    QPointer<Enemy> getAttackedEnemy();//得到正在攻击的敌人

    void reSetDamage(int damage);//重新设置攻击力
    int getDamage();//得到防御塔的攻击力
    void levelChange();//防御塔升级
    int getLevel();//得到防御塔的等级

    void getRemoved();//防御塔被移除

private:
    QPoint m_pos;//防御塔的中心点
    QString m_path;//防御塔图片的路径

    int m_attackRange;//攻击范围
    static const QSize m_fixedSize;//防御塔图片的固定大小
    MainWindow * m_game;//指向mainwindow的指针

    bool m_attacking;//是否在攻击
    int m_damage;//防御塔的攻击力
    int m_fireRate;//射速
    QPointer<Enemy> m_chooseEnemy;//正在攻击的敌人
    QTimer * m_fireRateTime;
    int m_level;

private slots:
    void shootWeapon();//私有信号槽，实现和子弹类的连接
};

#endif // TOWER_H
