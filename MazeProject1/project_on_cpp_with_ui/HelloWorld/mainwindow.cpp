#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    private slots:
        void button1_clicked(bool checked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

