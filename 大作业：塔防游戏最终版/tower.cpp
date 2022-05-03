#include "tower.h"
#include "mainwindow.h"
#include "utility.h"

#include <QPoint>
#include <QPainter>
#include <QString>

const QSize Tower::m_fixedSize(35,35);

Tower::Tower()
{
}

Tower::Tower(QPoint pos,MainWindow * game,QString path,int damage,int rate):
     m_pos(pos),
     m_path(path),
     m_attackRange(150),//根据地图的大小，确定攻击范围
     m_game(game),
     m_attacking(false),
     m_damage(damage),//攻击力10
     m_fireRate(rate),//1000ms
     m_chooseEnemy(NULL),
     m_level(1)
{
    m_fireRateTime=new QTimer(this);
    connect(m_fireRateTime,SIGNAL(timeout()),this,SLOT(shootWeapon()));
}

void Tower::draw(QPainter *painter) const
{
    painter->save();
    painter->setPen(Qt::green);
    painter->drawEllipse(m_pos,m_attackRange,m_attackRange);//画出防御塔的攻击范围
    painter->drawPixmap(m_pos.x()-m_fixedSize.width()/2,m_pos.y()-m_fixedSize.height()/2-10,m_fixedSize.width(), m_fixedSize.height(),m_path);//画出防御塔的图片
}

Tower::~Tower()
{
    delete m_fireRateTime;
    m_fireRateTime=NULL;
    m_chooseEnemy=NULL;
    m_game=NULL;
}
void Tower::chooseEnemyFromAttack(QPointer<Enemy> enemy)
{
    m_chooseEnemy=enemy;
    attackEnemy();
    m_chooseEnemy->getAttacked(this);//该敌人受到该防御塔的攻击
}

void Tower::attackEnemy()
{
    m_fireRateTime->start(m_fireRate);//开始攻击
}

void Tower::shootWeapon()
{
    Bullet * bullet=new Bullet(m_pos,m_chooseEnemy->getPos(),m_damage,m_chooseEnemy,m_game);//构造一个子弹，准备攻击敌人
    bullet->move();
    m_game->addBullet(bullet);//将该子弹添加到mainwindow中
}

void Tower::targetKilled()
{
    if(m_chooseEnemy)
    {
        m_chooseEnemy=NULL;
    }
    m_fireRateTime->stop();//敌人死亡，停止开火
}

void Tower::lostSightOfEnemy()
{
    m_chooseEnemy->getLostSight(this);
    if(m_chooseEnemy)
    {
        m_chooseEnemy=NULL;
    }
    m_fireRateTime->stop();
}

void Tower::checkEnemyInRange()
{
    if(m_chooseEnemy)//如果有了攻击的敌人
        {
            QVector2D normalized(m_chooseEnemy->getPos()-m_pos);
            normalized.normalize();
            if(!collisionWithCircle(m_pos,m_attackRange,m_chooseEnemy->getPos(),1))//当敌人不在范围内的时候
            {
                lostSightOfEnemy();
            }
        }
        else//如果没有攻击的敌人，就遍历enemylist，找到在攻击范围内的敌人
        {
            QList<QPointer<Enemy> > enemyList=m_game->getEnemyList();
            foreach(QPointer<Enemy> enemy,enemyList)
                if(collisionWithCircle(m_pos,m_attackRange,enemy->getPos(),1))
                {
                    chooseEnemyFromAttack(enemy);
                    break;
                }
        }
}

QPointer<Enemy> Tower::getAttackedEnemy()
{
    return m_chooseEnemy;
}

void Tower::reSetDamage(int damage)
{
    m_damage=damage;
}

int Tower::getDamage()
{
    return m_damage;
}

void Tower::levelChange()
{
    m_level++;
}

int Tower::getLevel()
{
    return m_level;
}

void Tower::getRemoved()
{
    if(getAttackedEnemy())//这里要判断是不是空指针NULL
    {
        getAttackedEnemy()->getLostSight(this);//移除后，敌人被该防御塔丢失视野
    }
    m_game->removeTower(this);
}
