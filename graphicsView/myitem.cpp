#include "myitem.h"
#include <QPainter>
#include <QColor>

myItem::myItem()
{

}

void myItem::refresh(QList<QPointF> *points)
{
    QPolygonF poly(*points);
    setPolygon(poly);
    setPos(0,0);
    update();
}
