#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <blog/controller_blog.hpp>
#include <QString>
#include <QModelIndex>
#include <vector>
#include <QStringList>
#include <QSettings>
#include <QCloseEvent>

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
    void post_changed(const QString&);
    void post_list_changed(std::vector<basics::Post>);
    void post_list_add(const basics::Post&);
    void post_list_remove(const QString&);
    void blog_changed(const QString&);

private slots:
    void empty_post_display();
    void on_actionGenerate_triggered();
    void on_actionNew_triggered();
    void on_actionOpen_triggered();
    void on_actionPublish_triggered();

    void on_blogCB_currentIndexChanged(const QString&);

    void on_addPostButton_clicked();
    void on_editButton_clicked();
    void on_remPostButton_clicked();

    /**
     * Slot to update post display. QString is the timestamp id of the post
     */
    void set_blog_display(const QString &blog_path);
    void set_post_display(const QString&);

protected:
    void closeEvent(QCloseEvent *event);

private:
    Ui::MainWindow *ui;
    basics::Simple_logger logger_;
    basics::Controller_blog ctrl_blog_;

    bool clearing_combo_;
    QStringList blog_history_;

    QSettings cfg_;

    void warning(std::string);
    void status(std::string, int seconds = 5);

    // helpers
    void gen();
    void create(std::string, std::string, bool, bool);
    void open(std::string);

    // Constants
    const QString BLOG = "last_blog";
    const QString AUTHOR = "last_author";
    const QString SERVER = "remote_host";
    const QString BLOG_PATH_ON_SERVER = "remote_blog_path";


};

#endif // MAINWINDOW_HPP
