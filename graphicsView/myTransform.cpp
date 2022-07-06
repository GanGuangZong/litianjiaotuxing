#include "SKTransform.h"
#include <math.h>
#include <QVector>

SKTransform::SKTransform()
{
}

SKTransform::~SKTransform()
{
}

void SKTransform::Translate(double dx, double dy)
{
    double transM[3][3] = { {1,0,0}, {0,1,0}, {dx,dy,1} };
    matrixMulti(transM);
}

void SKTransform::Scale(double sx, double sy)
{
	double scaleM[3][3] = {{sx,0,0}
						  ,{0,sy,0}
						  ,{0,0,1} };
	matrixMulti(scaleM);
}

void SKTransform::rotate(double angle)
{
	double rotateM[3][3] = { {cos(angle),-sin(angle),0}
							,{sin(angle),cos(angle),0}
							,{0,         0,         1} };
    matrixMulti(rotateM);
}

void SKTransform::symmetry(double l[])
{
    double rotateM[3][3] = { {1-2*l[0]*l[0],-2*l[0]*l[1],0}
                            ,{-2*l[0]*l[1],1-2*l[1]*l[1],0}
                            ,{0,         0,         1} };
    matrixMulti(rotateM);
}

void SKTransform::transForm(QVector<QPointF>* points)
{
    QVector<QPointF>::iterator it;
	for (it = points->begin(); it != points->end(); it++)
	{
        double vp[3] = { (*it).x(),(*it).y(),1 };
		double np[3];
		matrixMultiVector(vp, np);
		(*it).setX(np[0]);
		(*it).setY(np[1]);
	}
}

QPointF SKTransform::transForm(QPointF p)
{
        double vp[3] = { p.x(),p.y(),1 };
        double np[3];
        matrixMultiVector(vp, np);
        p.setX(np[0]);
        p.setY(np[1]);
        return p;
}

double* SKTransform::transForm(double v1[])
{
    double* nv = new double[3];
    matrixMultiVector(v1, nv);
    return nv;
}

void SKTransform::matrixMulti(double m1[][3])
{
	double out[3][3];
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			out[i][j] = 0;
			for (int k = 0; k < 3; k++)
			{
                out[i][j] += matrix[i][k] * m1[k][j];
			}
		}
	}

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			matrix[i][j] = out[i][j];
}

void SKTransform::matrixMultiVector(double v1[3], double out[3])
{
	for (int i = 0; i < 3; i++)
	{
		out[i] = 0;
		for (int j = 0; j < 3; j++)
		{
			out[i] += v1[j] * matrix[j][i];
		}
	}
}
