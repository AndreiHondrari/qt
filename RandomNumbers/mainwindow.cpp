#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_ui(new Ui::MainWindow),
    m_randomNumbersWidget(new RandomNumbersWidget)
{
    m_ui->setupUi(this);

    setFixedSize(400, 300);
    m_randomNumbersWidget->setFixedSize(size());
    setCentralWidget(m_randomNumbersWidget);
}

MainWindow::~MainWindow()
{
    delete m_ui;
    delete m_randomNumbersWidget;
}
