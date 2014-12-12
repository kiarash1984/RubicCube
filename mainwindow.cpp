#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_pVisualizer = new Visualizer(this);
    setCentralWidget(m_pVisualizer);
}

MainWindow::~MainWindow()
{
    delete ui;
}
