#include "widget.h"
#include "myitem.h"
#include "model.h"
#include "shapebuilder.h"
#include <QMouseEvent>
#include <QDebug>
Widget::Widget(QWidget *parent)
    : QGraphicsView(parent)
{
    m_rotate = ( 0 * PI) / 180.0;
    setSceneRect(QRectF(0, 0, 200, 200));
    m_scene = new QGraphicsScene(this);
    m_scene->setSceneRect(QRectF(0, 0, 200, 200));
    this->setScene(m_scene);
}

Widget::~Widget()
{

}

void Widget::mousePressEvent(QMouseEvent *e)
{
    QPointF p = e->pos();
    p = mapToScene(p.toPoint());
    QRectF posR(p.x() - 3,p.y() -3, 6, 6);
    QList<QPointF> points = m_item->polygon();
    for(int i=0; i<points.count(); i++)
    {
        if(posR.contains(points.at(i)))
            m_index = i;
    }
}

void Widget::mouseMoveEvent(QMouseEvent *e)
{
    if(m_index == -1)
    {
        return;
    }
    QPointF actionP = mapToScene( e->pos());
    QList<QPointF> points = m_item->polygon();
    points.removeAt(m_index);
    points.insert(m_index,actionP);
    m_item->reSetShape(&points,m_index,m_rotate);
    m_scene->update(m_item->boundingRect());
}

void Widget::mouseReleaseEvent(QMouseEvent *e)
{
    Q_UNUSED(e)
    m_index = -1;
}

void Widget::addShape()
{
    m_scene->addItem(m_item);
    m_scene->update(m_item->boundingRect());
}

void Widget::clear()
{
    m_index = -1;
    m_rotate = 0;
    if(m_item != nullptr)
    {
        m_scene->removeItem(m_item);
        m_scene->update(m_item->boundingRect());
    }
    delete m_item;
    m_item = nullptr;
}

void Widget::on_rectBtn_clicked()
{
    clear();
    shapeBuilder builder;
    m_item = builder.createShape(Model::shapeType::Rect, m_rotate);
    addShape();
}


void Widget::on_rhombusBtn_clicked()
{
    clear();
    shapeBuilder builder;
    m_item = builder.createShape(Model::shapeType::Rhombus,m_rotate);
    addShape();
}


void Widget::on_squareBtn_clicked()
{
    clear();
    shapeBuilder builder;
    m_item = builder.createShape(Model::shapeType::Square,m_rotate);
    addShape();
}


void Widget::on_parallelogramBtn_clicked()
{
    clear();
    shapeBuilder builder;
    m_item = builder.createShape(Model::shapeType::Parallelogram,m_rotate);
    addShape();
}


void Widget::on_echelon_clicked()
{
    clear();
    shapeBuilder builder;
    m_item = builder.createShape(Model::shapeType::Echelon,m_rotate);
    addShape();
}


void Widget::on_equalEchelonBtn_clicked()
{
    clear();
    shapeBuilder builder;
    m_item = builder.createShape(Model::shapeType::EqualEchelon,m_rotate);
    addShape();
}


void Widget::on_OrtEchelonBtn_clicked()
{
    clear();
    shapeBuilder builder;
    m_item = builder.createShape(Model::shapeType::OrthometricEchelon,m_rotate);
    addShape();
}
