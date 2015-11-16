#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <memory>
#include <QMainWindow>
#include "blog/interface_blog.hpp"

#ifndef Q_MOC_RUN
#include "utils/simple_logger.hpp"
#endif

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0, int log_level = 2, std::string blog_folder_path = "");
    ~MainWindow();

private slots:
    void on_generateButton_clicked();
    void on_clearButton_clicked();
    void on_actionNew_triggered();
    void on_actionOpen_triggered();

private:
    Ui::MainWindow *ui;
    std::unique_ptr<basics::Interface_blog> blog_;
    basics::Simple_logger logger_;

    void clear_fields();
    void warning(std::string);
    
};

#endif // MAINWINDOW_HPP
