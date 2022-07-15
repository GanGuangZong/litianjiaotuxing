#include "toolview.h"
#include "ui_toolview.h"

toolView::toolView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::toolView)
{
    ui->setupUi(this);
}

toolView::~toolView()
{
    delete ui;
}

QPushButton* toolView::getButton(Model::shapeType type)
{
    QPushButton* btn = nullptr;
    switch(type)
    {
    case Model::shapeType::Rect:
        btn = ui->rectBtn;
        break;
    case Model::shapeType::Rhombus:
        btn = ui->rhombusBtn;
        break;
    case Model::shapeType::Square:
        btn = ui->squareBtn;
        break;
    case Model::shapeType::Parallelogram:
        btn = ui->parallelogramBtn;
        break;
    case Model::shapeType::Echelon:
        btn = ui->echelonBtn;
        break;
    case Model::shapeType::EqualEchelon:
        btn = ui->equalEchelonBtn;
        break;
    case Model::shapeType::OrthometricEchelon:
        btn = ui->OrtEchelonBtn;
        break;
    }
    return btn;
}

