#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include "blog/blog.hpp"

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
    

private:
    Ui::MainWindow *ui;
    basics::Blog blog_;
    

};

#endif // MAINWINDOW_HPP
