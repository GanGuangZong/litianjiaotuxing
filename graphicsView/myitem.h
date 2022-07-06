#ifndef MYITEM_H
#define MYITEM_H

#include <QGraphicsPolygonItem>
#include <QPolygonF>

class myItem : public QGraphicsPolygonItem
{
public:
    myItem();

private:
    QPolygonF m_poly;
};

#endif // MYITEM_H
