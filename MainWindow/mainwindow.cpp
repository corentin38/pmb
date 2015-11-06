#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    blog_(basics::Blog("/home/corentin/work/projects/basics/pmb/resources/dom/content_sample.xml"))
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked() 
{
    std::cout << "Clicked !" << std::endl;
    
    std::string title =  ui->lineEdit->text().toStdString();
    std::string author =  ui->lineEdit_2->text().toStdString();
    std::string life =  ui->textEdit->toPlainText().toStdString();

    blog_.load_xsl("/home/corentin/work/projects/basics/pmb/resources/dom/my.xsl");
    blog_.add_post(title, author, life);
    blog_.generate("/home/corentin/work/projects/basics/pmb/resources/output/");
}
