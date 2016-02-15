#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <blog/controller_blog.hpp>
#include <QString>
#include <QModelIndex>
#include <vector>

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
    explicit MainWindow(basics::Simple_logger, QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_actionGenerate_triggered();

//    void on_clearButton_clicked();
    void on_actionNew_triggered();
    void on_actionOpen_triggered();
    void on_blogCB_currentIndexChanged(const QString&);
    void on_postList_clicked(const QModelIndex &);
    
    void on_addPostButton_clicked();
    void on_editButton_clicked();
    void on_remPostButton_clicked();

private:
    Ui::MainWindow *ui;
    basics::Simple_logger logger_;
    basics::Controller_blog ctrl_blog_;

    bool clearing_combo_;
    std::vector<std::string> blog_history_;
    

//    void clear_fields();
    void update_blog_combobox();
    void update_post_list();
    void update_frame();
    void warning(std::string);
    void status(std::string, int seconds = 5);
};

#endif // MAINWINDOW_HPP
