#pragma once
#include <vector>
#include <QPointF>


class SKTransform
{
public:
	SKTransform();
	~SKTransform();
	void Translate(double dx, double dy);
	void Scale(double sx, double sy);
	void rotate(double angle);
    void symmetry(double l[]);
    void transForm(QVector<QPointF> *points);
    QPointF transForm(QPointF p);
    double *transForm(double v1[]);
private:
    void matrixMulti(double m1[][3]);
	void matrixMultiVector(double[3], double out[3]);
private:
	double matrix[3][3] = { {1,0,0} , {0,1,0} , {0,0,1} };
};

