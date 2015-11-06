#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    blog_(basics::Blog("/home/corentin/work/projects/basics/pmb/resources/content.xml"))
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_generateButton_clicked()
{
    std::cout << "Clicked !" << std::endl;
    
    std::string title =  ui->titleEdit->text().toStdString();
    std::string author =  ui->authorEdit->text().toStdString();
    std::string life =  ui->lifeEdit->toPlainText().toStdString();

    blog_.load_xsl("/home/corentin/work/projects/basics/pmb/resources/dom/my.xsl");
    blog_.add_post(title, author, life);
    blog_.generate("/home/corentin/work/projects/basics/pmb/resources/output/");
}

void MainWindow::on_clearButton_clicked() 
{
    ui->titleEdit->clear();
    ui->authorEdit->clear();
    ui->lifeEdit->clear();
}
