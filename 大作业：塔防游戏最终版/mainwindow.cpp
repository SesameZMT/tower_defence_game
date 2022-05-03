#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMainWindow>
#include <QPainter>
#include <QTimer>

#include "waypoint.h"
#include"towerposition.h"
#include "enemy.h"
#include "selectbutton.h"
#include "selectbutton2.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      m_playerHp(5),
      m_playerGlod(1000),
      m_waves(0),
      m_gameWin(false),
      m_gameLose(false)
{
    ui->setupUi(this);

    QTimer * timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(updateMap()));
    timer->start(30);
    QTimer::singleShot(300,this,SLOT(gameStart()));
    this->setFixedSize(1050,800);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent*)
{
    if(m_gameLose || m_gameWin)//画出游戏结束的画面
        {
            QString text=m_gameLose ? "YOU LOST":"YOU WIN";
            QPainter painter(this);
            painter.setPen(Qt::red);
            painter.drawText(rect(),Qt::AlignCenter,text);
            return ;
        }

    QPainter painter(this);
    QString path=getPath();//path是图片的路径

    painter.drawPixmap(0,0,1050,800,path);//drawPixmap的前四个参数代表的分别是，图片左上角的横坐标，图片左上角的纵坐标，图片的width，图片的height。我们一般把width和height，与图片的真实大小匹配起来

    foreach(const wayPoint * waypoint,m_wayPointList)
            waypoint->draw(&painter);
    foreach(const TowerPosition towerposition,m_towerPositionList)
           towerposition.draw(&painter);
    foreach(const QPointer<Tower> tower, m_towerList)
            tower->draw(&painter);
    foreach(const QPointer<Enemy> enemy,m_enemyList)
            enemy->draw(&painter);
    foreach(const QPointer<Bullet> bullet,m_bulletList)
        bullet->draw(&painter);
    foreach(const selectButton * button,m_selectButtonList)
            button->draw(&painter);
    foreach(const selectButton2 * button2,m_selectButton2List)
        button2->draw(&painter);

    drawHp(&painter);
    drawGlod(&painter);
    drawWaves(&painter);
}

//函数的实现
void MainWindow::addWayPoint1()
{
    wayPoint * waypoint11=new wayPoint(QPoint(0,305));
    m_wayPointList.push_back(waypoint11);

    wayPoint * waypoint12=new wayPoint(QPoint(310,305));
    waypoint11->setNextWayPoint(waypoint12);
    m_wayPointList.push_back(waypoint12);

    wayPoint * waypoint13=new wayPoint(QPoint(310,540));
    waypoint12->setNextWayPoint(waypoint13);
    m_wayPointList.push_back(waypoint13);

    wayPoint * waypoint14=new wayPoint(QPoint(650,540));
    waypoint13->setNextWayPoint(waypoint14);
    m_wayPointList.push_back(waypoint14);

    wayPoint * waypoint15=new wayPoint(QPoint(650,370));
    waypoint14->setNextWayPoint(waypoint15);
    m_wayPointList.push_back(waypoint15);

    wayPoint * waypoint16=new wayPoint(QPoint(1020,370));
    waypoint15->setNextWayPoint(waypoint16);
    m_wayPointList.push_back(waypoint16);
}

void MainWindow::loadTowerPosition1()
{
    //这里和找航点是一样的，制作者需要自己不断尝试
    //找到比较合适的防御塔坑点
    QPoint pos[]=
    {
        QPoint(100,190),
        QPoint(190,190),
        QPoint(280,190),
        QPoint(365,240),
        QPoint(105,380),
        QPoint(223,380),
        QPoint(365,400),
        QPoint(575,400),
        QPoint(365,319),
        QPoint(575,319),
        QPoint(625,240),
        QPoint(800,240),
        QPoint(750,425),
        QPoint(850,425)
    };
    int len=sizeof(pos)/sizeof(pos[0]);
    for(int i=0;i<len;i++)
    {
        m_towerPositionList.push_back(pos[i]);
    }
}

void MainWindow::addWayPoint2()
{
    wayPoint * waypoint21=new wayPoint(QPoint(0,450));
    m_wayPointList.push_back(waypoint21);

    wayPoint * waypoint22=new wayPoint(QPoint(540,450));
    waypoint21->setNextWayPoint(waypoint22);
    m_wayPointList.push_back(waypoint22);

    wayPoint * waypoint23=new wayPoint(QPoint(540,220));
    waypoint22->setNextWayPoint(waypoint23);
    m_wayPointList.push_back(waypoint23);

    wayPoint * waypoint24=new wayPoint(QPoint(700,220));
    waypoint23->setNextWayPoint(waypoint24);
    m_wayPointList.push_back(waypoint24);

    wayPoint * waypoint25=new wayPoint(QPoint(700,370));
    waypoint24->setNextWayPoint(waypoint25);
    m_wayPointList.push_back(waypoint25);

    wayPoint * waypoint26=new wayPoint(QPoint(1020,370));
    waypoint25->setNextWayPoint(waypoint26);
    m_wayPointList.push_back(waypoint26);
}

void MainWindow::loadTowerPosition2()
{
    //这里和找航点是一样的，制作者需要自己不断尝试
    //找到比较合适的防御塔坑点
    QPoint pos[]=
    {
        QPoint(120,330),
        QPoint(223,330),
        QPoint(336,330),
        QPoint(439,240),
        QPoint(600,400),
        QPoint(439,330),
        QPoint(600,319),
        QPoint(850,240),
        QPoint(800,240),
        QPoint(750,445),
        QPoint(850,445)
    };
    int len=sizeof(pos)/sizeof(pos[0]);
    for(int i=0;i<len;i++)
    {
        m_towerPositionList.push_back(pos[i]);
    }
}

void MainWindow::addWayPoint3()
{
    wayPoint * waypoint1=new wayPoint(QPoint(0,470));
    m_wayPointList.push_back(waypoint1);

    wayPoint * waypoint2=new wayPoint(QPoint(200,470));
    waypoint1->setNextWayPoint(waypoint2);
    m_wayPointList.push_back(waypoint2);

    wayPoint * waypoint3=new wayPoint(QPoint(200,260));
    waypoint2->setNextWayPoint(waypoint3);
    m_wayPointList.push_back(waypoint3);

    wayPoint * waypoint4=new wayPoint(QPoint(550,260));
    waypoint3->setNextWayPoint(waypoint4);
    m_wayPointList.push_back(waypoint4);

    wayPoint * waypoint5=new wayPoint(QPoint(550,440));
    waypoint4->setNextWayPoint(waypoint5);
    m_wayPointList.push_back(waypoint5);

    wayPoint * waypoint6=new wayPoint(QPoint(840,440));
    waypoint5->setNextWayPoint(waypoint6);
    m_wayPointList.push_back(waypoint6);

    wayPoint * waypoint7=new wayPoint(QPoint(840,300));
    waypoint6->setNextWayPoint(waypoint7);
    m_wayPointList.push_back(waypoint7);

    wayPoint * waypoint8=new wayPoint(QPoint(1020,300));
    waypoint7->setNextWayPoint(waypoint8);
    m_wayPointList.push_back(waypoint8);
}

void MainWindow::loadTowerPosition3()
{
    //这里和找航点是一样的，制作者需要自己不断尝试
    //找到比较合适的防御塔坑点
    QPoint pos[]=
    {
        QPoint(100,210),
        QPoint(100,280),
        QPoint(100,350),
        QPoint(260,350),
        QPoint(465,470),
        QPoint(465,350),
        QPoint(625,320),
        QPoint(625,240),
        QPoint(760,240),
        QPoint(760,320)
    };
    int len=sizeof(pos)/sizeof(pos[0]);
    for(int i=0;i<len;i++)
    {
        m_towerPositionList.push_back(pos[i]);
    }
}

void MainWindow::mousePressEvent(QMouseEvent * event)
{
    QPoint pressPos=event->pos();//得到鼠标点击的位置
    auto it=m_towerPositionList.begin();
    while(it!=m_towerPositionList.end())//遍历所有的防御塔坑
        {
            if(Qt::LeftButton==event->button())//如果是鼠标左键点击
            {
                if(!it->hasButton() && it->ContainPos(pressPos) && !it->hasTower())//如果没有button，点击的点在防御塔坑的内部
                {
                    QPoint tmp(it->getPos().x()+15,it->getPos().y()-35);//得到该防御塔坑处的button的左上点
                    selectButton * button=new selectButton(tmp,this);//创建一个button
                    it->setHasButton(true);//设置该位置有button
                    it->setButton(button);//设置该位置的button
                    m_selectButtonList.push_back(button);//把这个button加入到mainwidnow中
                    update();
                    break;
                }
                else if(it->hasButton() && it->getButton()->containPos(pressPos) && !it->hasTower())//如果这个位置有button，并且没有防御塔
                {
                    if(pressPos.x()>it->getButton()->getPos().x()-52.5 && pressPos.x()<it->getButton()->getPos().x()-17.5 && canBuyTower())//如果鼠标点击的地方在第一张图片内，创造第一个防御塔
                    {
                        it->setHasTower1(true);
                        m_playerGlod-=300;
                        QString path=":/defencetower.jpeg";
                        QPointer<Tower> tower=new Tower(it->getCenterPos(),this,path,10,1000);//攻击力为10的第一种防御塔
                        m_towerList.push_back(tower);
                    }
                    if(pressPos.x()>it->getButton()->getPos().x()-17.5 && pressPos.x()<it->getButton()->getPos().x()+17.5 && canBuyTower2())//鼠标点击点在第二张图片内，创建第二种防御塔
                    {
                        it->setHasTower2(true);
                        m_playerGlod-=400;
                        QString path=":/defencetower2.jpeg";
                        QPointer<Tower> tower=new Tower(it->getCenterPos(),this,path,5,250);//攻击力为5的第二种防御塔
                        m_towerList.push_back(tower);
                    }
                    if(pressPos.x()>it->getButton()->getPos().x()+17.5 && pressPos.x()<it->getButton()->getPos().x()+52.5 && canBuyTower3())
                    {
                        it->setHasTower3(true);
                        m_playerGlod-=500;
                        QString path=":/defencetower3.jpeg";
                        QPointer<Tower> tower=new Tower(it->getCenterPos(),this,path,40,1500);
                        m_towerList.push_back(tower);
                    }
                    //构造完防御塔后，原来的button就要消失，下面对该button进行移除
                    it->getButton()->getRemoved();
                    it->setButton(NULL);
                    it->setHasButton(false);
                    update();
                    break;
                }
            }
            else if(Qt::RightButton==event->button())//如果是鼠标右键点击
                    {//在有防御塔的情况下，右键会出现选择框，升级还有移除
                        if(it->ContainPos(pressPos) && (!it->hasButton2()) && it->hasTower())
                        {
                            it->setHasButton2(true);
                            QPoint tmp(it->getPos().x()+15,it->getPos().y()-35);//我是把防御塔坑的左上顶点当作button2的端点
                            selectButton2 * button2=new selectButton2(tmp,this);
                            button2->setTower(it->getTower());//写这个setTower()的目的是得到防御塔的等级，不同等级的updatecost不一样
                            m_selectButton2List.push_back(button2);
                            it->setButton2(button2);
                            update();
                            break;
                        }
                        else if(it->hasButton2() && it->getButton2()->containPos(pressPos) && !it->hasButton() && !it->ContainPos(pressPos) &&it->hasTower())
                        {//在有button2的情况下，点击button2的内部
                            if(pressPos.y()<(it->getButton2()->getPos().y()+25))//设置了第一个选择框的height是25，这里就直接用25了
                            {//对防御塔进行升级
                                if(canUpdate1() && !it->hasUpdate1() && it->hasTower())
                                {
                                    it->setHasUpdate1(true);
                                    m_playerGlod-=300;
                                    it->getTower()->reSetDamage(it->getTower()->getDamage()+10);
                                    it->getTower()->levelChange();
                                }
                                else if(canUpdate2() && it->hasUpdate1() && !it->hasUpdate2())
                                {
                                    it->setHasUpdate2(true);
                                    m_playerGlod-=400;
                                    it->getTower()->reSetDamage(it->getTower()->getDamage()+20);
                                    it->getTower()->levelChange();
                                }
                            }
                            else if(pressPos.y()>it->getButton2()->getPos().y()+25)
                            {//对防御塔进行移除
                                awardGlod();//移除防御塔奖励200
                                it->getTower()->getRemoved();//这个移除和前面写的几个移除都是一样的
                                it->setRemoveTower();//设置移除防御塔带来的其他变化
                            }
                            //点击了button2的内部，button2就要被移除
                            it->getButton2()->getRemoved();
                            it->setButton2(NULL);
                            it->setHasButton2(false);
                            update();
                            break;
                        }
                    }
            ++it;
        }
}

void MainWindow::getHpDamaged()
{
    m_playerHp-=1;//敌人进入基地，扣一滴血
}

void MainWindow::awardGlod()
{
    m_playerGlod+=200;//杀死一个敌人，奖励200，制作者可以自由更改数值
}

void MainWindow::removeEnemy(QPointer<Enemy>enemy)
{
    Q_ASSERT(enemy);
    m_enemyList.removeOne(enemy);//死亡的敌人从enemylist中移除

    if(m_enemyList.empty()){
        ++m_waves;
        if(!loadWaves(a)){
            m_gameWin=true;
        }
    }
}

QList<QPointer<Enemy>> MainWindow::getEnemyList()
{
    return m_enemyList;
}

bool MainWindow::loadWaves(int a)
{
    if(a == 1){
    if(m_waves>=6)
    {
        return false;
    }
    if(m_waves == 0){
        int enemyStartInterval[]={100,500,600,1000,3000,6000,6600,7200,7600,8400,8800,9400,9800,10200,10600,11200,12000,12400,12800,13200};//敌人出现的时间
        for(int i=0;i<20;++i)
        {
            wayPoint * startWayPoint;
            startWayPoint=m_wayPointList.first();
            QPointer<Enemy> enemy=new Enemy(startWayPoint,this,1,40,":/monster.png");//创建一个新得enemy
            m_enemyList.push_back(enemy);
            QTimer::singleShot(enemyStartInterval[i],enemy,SLOT(doActive()));
        }
        return true;
    }
    else if(m_waves == 1){
        int enemyStartInterval[]={100,500,600,1000,3000,6000,6600,7200,7600,8400};//敌人出现的时间
        for(int i=0;i<10;++i)
        {
            wayPoint * startWayPoint;
            startWayPoint=m_wayPointList.first();
            QPointer<Enemy> enemy=new Enemy(startWayPoint,this,3,80,":/monster.png");//创建一个新得enemy
            m_enemyList.push_back(enemy);
            QTimer::singleShot(enemyStartInterval[i],enemy,SLOT(doActive()));
        }
        return true;
    }
    else if(m_waves == 2){
        int enemyStartInterval[]={100,500,600,1000,3000,6000,6600,7200,7600,8400,8800,9000};//敌人出现的时间
        for(int i=0;i<12;++i)
        {
            wayPoint * startWayPoint;
            startWayPoint=m_wayPointList.first();
            QPointer<Enemy> enemy=new Enemy(startWayPoint,this,2,120,":/monster.png");//创建一个新得enemy
            m_enemyList.push_back(enemy);
            QTimer::singleShot(enemyStartInterval[i],enemy,SLOT(doActive()));
        }
        return true;
    }
    else if(m_waves >= 3){
        for(int i=0;i<8;++i)
        {
            int enemyStartInterval[]={100,500,600,1000,3000,6000,6600,7200};//敌人出现的时间
            wayPoint * startWayPoint;
            startWayPoint=m_wayPointList.first();
            QPointer<Enemy> enemy=new Enemy(startWayPoint,this,1,300,":/monster.png");//创建一个新得enemy
            m_enemyList.push_back(enemy);
            QTimer::singleShot(enemyStartInterval[i],enemy,SLOT(doActive()));
        }
        return true;
    }}

    if(a == 2){
    if(m_waves>=8)
    {
        return false;
    }
    if(m_waves == 0){
        int enemyStartInterval[]={100,500,600,1000,3000,6000,6600,7200,7600,8400,8800,9400,9800,10200,10600,11200,12000,12400,12800,13200};//敌人出现的时间
        for(int i=0;i<20;++i)
        {
            wayPoint * startWayPoint;
            startWayPoint=m_wayPointList.first();
            QPointer<Enemy> enemy=new Enemy(startWayPoint,this,1,40,":/monsters2.jpeg");//创建一个新得enemy
            m_enemyList.push_back(enemy);
            QTimer::singleShot(enemyStartInterval[i],enemy,SLOT(doActive()));
        }
        return true;
    }
    else if(m_waves == 1){
        int enemyStartInterval[]={100,500,600,1000,3000,6000,6600,7200,7600,8400};//敌人出现的时间
        for(int i=0;i<10;++i)
        {
            wayPoint * startWayPoint;
            startWayPoint=m_wayPointList.first();
            QPointer<Enemy> enemy=new Enemy(startWayPoint,this,3,80,":/monsters2.jpeg");//创建一个新得enemy
            m_enemyList.push_back(enemy);
            QTimer::singleShot(enemyStartInterval[i],enemy,SLOT(doActive()));
        }
        return true;
    }
    else if(m_waves == 2){
        int enemyStartInterval[]={100,500,600,1000,3000,6000,6600,7200,7600,8400,8800,9000};//敌人出现的时间
        for(int i=0;i<12;++i)
        {
            wayPoint * startWayPoint;
            startWayPoint=m_wayPointList.first();
            QPointer<Enemy> enemy=new Enemy(startWayPoint,this,2,120,":/monsters2.jpeg");//创建一个新得enemy
            m_enemyList.push_back(enemy);
            QTimer::singleShot(enemyStartInterval[i],enemy,SLOT(doActive()));
        }
        return true;
    }
    else if(m_waves >= 3){
        for(int i=0;i<8;++i)
        {
            int enemyStartInterval[]={100,500,600,1000,3000,6000,6600,7200};//敌人出现的时间
            wayPoint * startWayPoint;
            startWayPoint=m_wayPointList.first();
            QPointer<Enemy> enemy=new Enemy(startWayPoint,this,1,300,":/monsters2.jpeg");//创建一个新得enemy
            m_enemyList.push_back(enemy);
            QTimer::singleShot(enemyStartInterval[i],enemy,SLOT(doActive()));
        }
        return true;
    }}

    if(a == 3){
    if(m_waves>=12)
    {
        return false;
    }
    if(m_waves == 0){
        int enemyStartInterval[]={100,500,600,1000,3000,6000,6600,7200,7600,8400,8800,9400,9800,10200,10600,11200,12000,12400,12800,13200};//敌人出现的时间
        for(int i=0;i<20;++i)
        {
            wayPoint * startWayPoint;
            startWayPoint=m_wayPointList.first();
            QPointer<Enemy> enemy=new Enemy(startWayPoint,this,1,40,":/monster3.jpeg");//创建一个新得enemy
            m_enemyList.push_back(enemy);
            QTimer::singleShot(enemyStartInterval[i],enemy,SLOT(doActive()));
        }
        return true;
    }
    else if(m_waves == 1){
        int enemyStartInterval[]={100,500,600,1000,3000,6000,6600,7200,7600,8400};//敌人出现的时间
        for(int i=0;i<10;++i)
        {
            wayPoint * startWayPoint;
            startWayPoint=m_wayPointList.first();
            QPointer<Enemy> enemy=new Enemy(startWayPoint,this,3,80,":/monster3.jpeg");//创建一个新得enemy
            m_enemyList.push_back(enemy);
            QTimer::singleShot(enemyStartInterval[i],enemy,SLOT(doActive()));
        }
        return true;
    }
    else if(m_waves == 2){
        int enemyStartInterval[]={100,500,600,1000,3000,6000,6600,7200,7600,8400,8800,9000};//敌人出现的时间
        for(int i=0;i<12;++i)
        {
            wayPoint * startWayPoint;
            startWayPoint=m_wayPointList.first();
            QPointer<Enemy> enemy=new Enemy(startWayPoint,this,2,120,":/monster3.jpeg");//创建一个新得enemy
            m_enemyList.push_back(enemy);
            QTimer::singleShot(enemyStartInterval[i],enemy,SLOT(doActive()));
        }
        return true;
    }
    else if(m_waves >= 3){
        for(int i=0;i<8;++i)
        {
            int enemyStartInterval[]={100,500,600,1000,3000,6000,6600,7200};//敌人出现的时间
            wayPoint * startWayPoint;
            startWayPoint=m_wayPointList.first();
            QPointer<Enemy> enemy=new Enemy(startWayPoint,this,1,400,":/monster3.jpeg");//创建一个新得enemy
            m_enemyList.push_back(enemy);
            QTimer::singleShot(enemyStartInterval[i],enemy,SLOT(doActive()));
        }
        return true;
    }}
    return true;
}

void MainWindow::gameStart()
{
    loadWaves(a);
}

void MainWindow::updateMap()
{
    foreach(QPointer<Enemy> enemy,m_enemyList)
        enemy->move();
    update();
    foreach(QPointer<Tower> tower,m_towerList)
        tower->checkEnemyInRange();
}

void MainWindow::doGameOver()
{
    if(!m_gameLose)
    {
        m_gameLose=true;
    }
}

bool MainWindow::canBuyTower()
{
    if(m_playerGlod>=300)
    {
        return true;
    }
    return false;
}

void MainWindow::drawWaves(QPainter *painter) const
{
    painter->save();
    painter->setPen(Qt::red);
    painter->drawText(QRect(500,5,100,25),QString("WAVES: %1").arg(m_waves+1));
    painter->restore();
}

void MainWindow::drawHp(QPainter *painter) const
{
    painter->save();
    painter->setPen(Qt::red);
    painter->drawText(QRect(30,5,100,25),QString("HP: %1").arg(m_playerHp));
    painter->restore();
}

void MainWindow::drawGlod(QPainter *painter) const
{
    painter->save();
    painter->setPen(Qt::red);
    painter->drawText(QRect(300,5,100,25),QString("GLOD: %1").arg(m_playerGlod));
}

void MainWindow::removeBullet(QPointer<Bullet> bullet)
{
    Q_ASSERT(bullet);
    m_bulletList.removeOne(bullet);

}

void MainWindow::addBullet(QPointer<Bullet> bullet)
{
    Q_ASSERT(bullet);
    m_bulletList.push_back(bullet);
}

bool MainWindow::canBuyTower2()
{
    if(m_playerGlod>=400)
    {
        return true;
    }
    return false;
}

bool MainWindow::canBuyTower3()
{
    if(m_playerGlod>=500)
    {
        return true;
    }
    return false;
}

void MainWindow::removeButton(selectButton * button)
{
    m_selectButtonList.removeOne(button);
}

void MainWindow::removeTower(Tower *tower)
{
    m_towerList.removeOne(tower);
}

void MainWindow::removeButton2(selectButton2 *button)
{
    m_selectButton2List.removeOne(button);
}

bool MainWindow::canUpdate1()
{
    if(m_playerGlod>=300)
    {
        return true;
    }
    return false;
}

bool MainWindow::canUpdate2()
{
    if(m_playerGlod>=400)
    {
        return true;
    }
    return false;
}

void MainWindow::setPath(QString path)
{
    m_path=path;
}

QString MainWindow::getPath()
{
    return m_path;
}
