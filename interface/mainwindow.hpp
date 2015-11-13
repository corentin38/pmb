#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <memory>
#include <QMainWindow>
#include "blog/interface_blog.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_generateButton_clicked();
    void on_clearButton_clicked();
    void on_actionNouveau_triggered();

private:
    Ui::MainWindow *ui;
    std::unique_ptr<basics::Interface_blog> blog_;
    

};

#endif // MAINWINDOW_HPP
