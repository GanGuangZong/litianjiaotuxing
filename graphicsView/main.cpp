#include "widget.h"

#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
//    double* line = w.getLine(QPointF(25,14),QPointF(25,14));
//    for(int i=0;i<3;i++)
//    {
//        qDebug() << line[i];
//    }
    return a.exec();
}
