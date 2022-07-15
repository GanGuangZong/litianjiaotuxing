#ifndef WIDGET_H
#define WIDGET_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPointF>
#include <QGraphicsPolygonItem>
#include "myitem.h"
//14
//23
class Widget : public QGraphicsView
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
protected:
    void mousePressEvent(QMouseEvent* e);
    void mouseMoveEvent(QMouseEvent* e);
    void mouseReleaseEvent(QMouseEvent* e);
public:
private:
    void addShape();
    void clear();
public slots:
    void on_rectBtn_clicked();

    void on_rhombusBtn_clicked();

    void on_squareBtn_clicked();

    void on_parallelogramBtn_clicked();

    void on_echelon_clicked();

    void on_equalEchelonBtn_clicked();

    void on_OrtEchelonBtn_clicked();
private:
    QGraphicsScene* m_scene;
    myItem* m_item = nullptr;
    double m_rotate = 0;
    int m_index = -1;
};
#endif // WIDGET_H
