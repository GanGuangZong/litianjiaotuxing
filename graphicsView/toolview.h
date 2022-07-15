#ifndef TOOLVIEW_H
#define TOOLVIEW_H

#include <QWidget>
#include <QPushButton>
#include "model.h"

namespace Ui {
class toolView;
}

class toolView : public QWidget
{
    Q_OBJECT

public:
    explicit toolView(QWidget *parent = nullptr);
    ~toolView();
    QPushButton* getButton(Model::shapeType type );
private:
    Ui::toolView *ui;
};

#endif // TOOLVIEW_H
