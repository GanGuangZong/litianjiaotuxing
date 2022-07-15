#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "model.h"
#include <QSizePolicy>
#include <QPushButton>

mainWindow::mainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mainWindow)
{
    ui->setupUi(this);
    m_graphicsView = new Widget(this);
    m_graphicsView->setFixedSize(500,900);
    m_toolView = new toolView(this);
    ui->mainLayout->addWidget(m_graphicsView);
    ui->mainLayout->addWidget(m_toolView);
    connect(m_toolView->getButton(Model::shapeType::Rect),&QPushButton::clicked,
            m_graphicsView,&Widget::on_rectBtn_clicked);
    connect(m_toolView->getButton(Model::shapeType::Rhombus),&QPushButton::clicked,
            m_graphicsView,&Widget::on_rhombusBtn_clicked);
    connect(m_toolView->getButton(Model::shapeType::Parallelogram),&QPushButton::clicked,
            m_graphicsView,&Widget::on_parallelogramBtn_clicked);
    connect(m_toolView->getButton(Model::shapeType::Square),&QPushButton::clicked,
            m_graphicsView,&Widget::on_squareBtn_clicked);
    connect(m_toolView->getButton(Model::shapeType::Echelon),&QPushButton::clicked,
            m_graphicsView,&Widget::on_echelon_clicked);
    connect(m_toolView->getButton(Model::shapeType::EqualEchelon),&QPushButton::clicked,
            m_graphicsView,&Widget::on_equalEchelonBtn_clicked);
    connect(m_toolView->getButton(Model::shapeType::OrthometricEchelon),&QPushButton::clicked,
            m_graphicsView,&Widget::on_OrtEchelonBtn_clicked);
}

mainWindow::~mainWindow()
{
    delete ui;
}
