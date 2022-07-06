#ifndef WIDGET_H
#define WIDGET_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPointF>
#include <QGraphicsPolygonItem>
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
    QVector<QPointF> *createShape(double rotate);
    void reSetShape(QVector<QPointF> * points, int index, double rotate);
    QPointF getCenterPoint(QVector<QPointF> * points);
    double* getLine(QPointF p1,QPointF p2);
    double* getLineFromVector(double v1[], QPointF p1);
    double* VectorOuter(double v1[], double v2[]);
    int vectorInner(double v1[], double v2[]);
    double* middlePoint(QPointF p1,QPointF p2);
    double* normalFoot(double l[],QPointF p);
    double* getVector(QPointF p1, QPointF p2);
    int positionPointAndLine(QPointF p, double l[]);
private:
    void computeRectangle(QVector<QPointF> * points, int index, double rotate);
    void computeRhombus(QVector<QPointF> * points, int index, double rotate);
    void computeSquare(QVector<QPointF> * points, int index, double rotate);
    void computeParallelogram(QVector<QPointF> * points, int index, double rotate);
    void computeEchelon(QVector<QPointF> * points, int index, double rotate);
    void computeEqualEchelon(QVector<QPointF> * points, int index, double rotate);
    void computeOrthometricEchelon(QVector<QPointF> * points, int index, double rotate);
    QVector<QPointF> *createRhombus(double rotate);
    QVector<QPointF> *createRect(double rotate);
    QVector<QPointF> *createSquare(double rotate);
    QVector<QPointF> *createParallelogram(double rotate);
    QVector<QPointF> *createEchelon(double rotate);
    QVector<QPointF> *createEqualEchelon(double rotate);
    QVector<QPointF> *createOrthometricEchelon(double rotate);
private:
    QGraphicsScene* m_scene;
    QGraphicsPolygonItem* m_item;
    QVector<QPointF> *m_points;
    double m_rotate = 0;
    int m_t = 4;
    int m_index = -1;
};
#endif // WIDGET_H
