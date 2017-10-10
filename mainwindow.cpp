#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    button = new QPushButton;
    button->setFixedSize(200, 50);
    button->setText("test");
    connect(button, SIGNAL(clicked()), this, SLOT(test()));

    this->setCentralWidget(button);
}

MainWindow::~MainWindow()
{
    delete button;
}

void MainWindow::test()
{

}
