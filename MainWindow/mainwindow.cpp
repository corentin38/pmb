#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked() 
{
    std::cout << "Clicked !\n";
    std::cout << "field 1: " << ui->textEdit->toPlainText().toStdString() << "\n";
    std::cout << "field 2: " << ui->lineEdit->text().toStdString() << "\n";
    std::cout << "field 3: " << ui->lineEdit_2->text().toStdString() << "\n";
    
}
