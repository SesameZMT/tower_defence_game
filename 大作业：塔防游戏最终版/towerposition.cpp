#include "towerposition.h"

#include <QSize>
#include <QPainter>
#include <QPixmap>

const QSize TowerPosition::m_fixedSize(35,35);//设置图片的大小

TowerPosition::TowerPosition(QPoint pos, QString path) :
    m_pos(pos),
    m_path(path),
    m_hasTower(false),
    m_hasButton(false),
    m_hasTower1(false),
    m_hasTower2(false),
    m_hasTower3(false),
    m_hasButton2(false),
    m_hasUpdate1(false),
    m_hasUpdate2(false)

{
}

bool TowerPosition::hasTower()
{
    return m_hasTower;
}

void TowerPosition::setHasTower(bool hasTower)
{
    m_hasTower=hasTower;
}

QPoint TowerPosition::getCenterPos()
{
    QPoint tmp;
    tmp.setX(m_pos.x()+m_fixedSize.width()/2);
    tmp.setY(m_pos.y()+m_fixedSize.height()/2);
    return tmp;
}

QPoint TowerPosition::getPos()
{
    return m_pos;
}

bool TowerPosition::ContainPos(QPoint pos)
{
    bool xInHere=pos.x()>m_pos.x() && pos.x()<m_pos.x()+m_fixedSize.width();
    bool yInHere=pos.y()>m_pos.y() && pos.y()<m_pos.y()+m_fixedSize.height();
    return xInHere && yInHere;
}

void TowerPosition::draw(QPainter *painter) const
{
    painter->drawPixmap(m_pos.x(),m_pos.y(),m_fixedSize.width(), m_fixedSize.height(),m_path);
}

bool TowerPosition::hasButton()
{
    return m_hasButton;
}

void TowerPosition::setHasButton(bool hasButton)
{
    m_hasButton=hasButton;
}

void TowerPosition::setButton(selectButton *button)
{
    m_button=button;
}

selectButton * TowerPosition::getButton()
{
    return m_button;
}

void TowerPosition::setHasTower1(bool hasTower1)
{
    this->m_hasTower1=hasTower1;
    setHasTower(hasTower1);
}


bool TowerPosition::hasTower1()
{
    return m_hasTower1;
}

void TowerPosition::setHasTower2(bool hasTower2)
{
    this->m_hasTower2=hasTower2;
    setHasTower(hasTower2);
}

bool TowerPosition::hasTower2()
{
    return m_hasTower2;
}

void TowerPosition::setHasTower3(bool hasTower3)
{
    m_hasTower3=hasTower3;
    setHasTower(hasTower3);
}

bool TowerPosition::hasTower3()
{
    return m_hasTower3;
}

void TowerPosition::setHasButton2(bool hasButton2)
{
    m_hasButton2=hasButton2;
}

bool TowerPosition::hasButton2()
{
    return m_hasButton2;
}

void TowerPosition::setHasUpdate1(bool hasUpdate1)
{
    m_hasUpdate1=hasUpdate1;
}

bool TowerPosition::hasUpdate1()
{
    return m_hasUpdate1;
}

void TowerPosition::setHasUpdate2(bool hasUpdate2)
{
    m_hasUpdate2=hasUpdate2;
}

bool TowerPosition::hasUpdate2()
{
    return m_hasUpdate2;
}

void TowerPosition::setButton2(selectButton2 *button)
{
    m_button2=button;
}

void TowerPosition::setTower(QPointer<Tower> tower)
{
    m_tower=tower;
}

Tower * TowerPosition::getTower()
{
    return m_tower;
}

selectButton2 * TowerPosition::getButton2()
{
    return m_button2;
}

void TowerPosition::setRemoveTower()
{
    setTower(NULL);
    setHasTower(false);
    setHasTower1(false);
    setHasTower2(false);
    setHasTower3(false);
    setHasUpdate1(false);
    setHasUpdate2(false);
}

