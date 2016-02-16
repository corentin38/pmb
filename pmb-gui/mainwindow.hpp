#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <blog/controller_blog.hpp>
#include <QString>
#include <QModelIndex>
#include <vector>
#include <QStringList>

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

signals:
    void post_list_changed(std::vector<basics::Post>);
    void post_list_add(const basics::Post&);
    void post_list_remove(const basics::Post&);
    void blog_changed(const QString&);

private slots:

    void on_actionGenerate_triggered();
    void on_actionNew_triggered();
    void on_actionOpen_triggered();

    void on_blogCB_currentIndexChanged(const QString&);
    
    void on_addPostButton_clicked();
    void on_editButton_clicked();
    void on_remPostButton_clicked();

    /**
     * Slot to update post display. QString is the timestamp id of the post
     */
    void set_blog_display(const QString &blog_path);
    void set_post_display(const QString&);

private:
    Ui::MainWindow *ui;
    basics::Simple_logger logger_;
    basics::Controller_blog ctrl_blog_;

    bool clearing_combo_;
    QStringList blog_history_;
    

    void warning(std::string);
    void status(std::string, int seconds = 5);
};

#endif // MAINWINDOW_HPP
