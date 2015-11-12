#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)//,
//    blog_(basics::Blog("/home/corentin/work/projects/basics/pmb/resources/content.xml"))
{
    ui->setupUi(this);
    
//    Config config;
//    std::string last_edited_blog = config.get_last_edited_blog();

//    if (!last_edited_blog.isEmpty()) {
        

//    Factory_blog factory;
//    blog_ = factory.load_local_instance(last_edited_blog);
}
    
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_generateButton_clicked()
{
    std::string title =  ui->titleEdit->text().toStdString();
    std::string author =  ui->authorEdit->text().toStdString();
    std::string life =  ui->lifeEdit->toPlainText().toStdString();

    blog_.add_post(title, author, life);
    blog_.generate();
}

void MainWindow::on_clearButton_clicked() 
{
    ui->titleEdit->clear();
    ui->authorEdit->clear();
    ui->lifeEdit->clear();
}
