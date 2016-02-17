#include "mainwindow.hpp"
#include "blogwizard.hpp"
#include "posteditor.hpp"
#include <ui_mainwindow.h>
#include <QMessageBox>
#include <QFileDialog>
#include <stdexcept>
#include <QStringList>
#include <QStringListModel>
#include <algorithm>

namespace bfs = boost::filesystem;

MainWindow::MainWindow(basics::Simple_logger logger, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    logger_(logger),
    ctrl_blog_(logger),
    clearing_combo_(false),
    blog_history_()
{
    ui->setupUi(this);

    connect(ui->postList, SIGNAL (selected_post_changed(const QString&)), this, SLOT (set_post_display(const QString&)));
    connect(ui->postList, SIGNAL (empty()), this, SLOT (empty_post_display()));
    connect(this, SIGNAL (post_changed(const QString&)), this, SLOT (set_post_display(const QString&)));
    connect(this, SIGNAL (blog_changed(const QString&)), this, SLOT (set_blog_display(const QString&)));
    connect(this, SIGNAL (post_list_changed(std::vector<basics::Post>)), ui->postList, SLOT (set_post_list(std::vector<basics::Post>)));
    connect(this, SIGNAL (post_list_add(const basics::Post&)), ui->postList, SLOT (add_post(const basics::Post&)));
    connect(this, SIGNAL (post_list_remove(const QString&)), ui->postList, SLOT (remove_post(const QString&)));

    logger_.info("Démarrage de l'application Pimp My Blog");
    logger_.info("Version : EN COURS DE DEVELOPPEMENT");    

    status("Aucun blog chargé");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionGenerate_triggered()
{
    status("Génération du blog ...");
    
    try {
        ctrl_blog_.generate_current_blog();
    }
    catch (const std::exception &err) {
        warning("Aucun blog n'est actuellement chargé.\n"
                "Vous pouvez créer un blog en cliquant sur "
                "Nouveau ou en charger un en cliquant sur Ouvrir.");
        status("Impossible de générer le blog");
        return;
    }

    status("Blog publié !");
}

void MainWindow::on_actionNew_triggered() 
{
    BlogWizard *wiz = new BlogWizard(this);
    int code = wiz->exec();
    if (code == QDialog::Rejected) {
        delete wiz;
        return;
    }

    std::string name = wiz->get_blog_name();
    std::string blog_path = wiz->get_blog_path();
    bool override = wiz->get_override_checked();
    bool sample = wiz->get_sample_checked();

    if (name.empty()) {
        warning("Aucun nom de blog n'a été fourni !\n"
                "Abandon de la création du blog.");
        delete wiz;
        return;
    }

    if (blog_path.empty()) {
        warning("Aucun dossier de blog n'a été fourni !\n"
                "Abandon de la création du blog.");
        delete wiz;
        return;
    }

    std::string new_blog_path = "";
    try {
        new_blog_path = ctrl_blog_.create_new_blog(name, blog_path, override, sample);
    }
    catch (const std::exception& e) {
        warning(std::string("Impossible de créer le blog !\n") + std::string(e.what()));
        delete wiz;
        return;
    }


    blog_history_ << QString::fromStdString(new_blog_path);
    //emit post_list_changed(ctrl_blog_.post_list());
    emit blog_changed(QString::fromStdString(ctrl_blog_.get_blog_path()));
    
    logger_.info("Nouveau blog créé avec succès");
    delete wiz;
}

void MainWindow::on_actionOpen_triggered() 
{
    logger_.info("Chargement d'une instance existante de blog");

    // Asking for the new blog path
    QString q_blog_folder_path = QFileDialog::getExistingDirectory(
        this,
        tr("Choisir un blog"),
        getenv("HOME"));
    std::string blog_folder_path = q_blog_folder_path.toUtf8().constData();

    // Checks for blog validity and inexistence
    if (blog_folder_path.empty()) {
        return;
    }
    
    try {
        ctrl_blog_.open_blog(blog_folder_path);
    }
    catch (const std::exception& e) {
        warning(std::string("Impossible d'ouvrir le blog !\n") + std::string(e.what()));
        return;
    }

    // Add to history if does not exist already
    if(blog_history_.indexOf(q_blog_folder_path) < 0) {
        blog_history_ << q_blog_folder_path;
    }

    //emit post_list_changed(ctrl_blog_.post_list());
    emit blog_changed(QString::fromStdString(ctrl_blog_.get_blog_path()));
    status("Blog chargé !");
}

void MainWindow::on_addPostButton_clicked()
{
    if (!ctrl_blog_.has_blog()) return;

    PostEditor *editor = new PostEditor(this);
    int code = editor->exec();
    if (code == QDialog::Rejected) {
        delete editor;
        return;
    }

    std::string title = editor->get_post_title();
    std::string author = editor->get_post_author();
    std::string life = editor->get_post_life();

    try {
        basics::Post post = ctrl_blog_.add_post(title, author, life);
        emit post_list_add(post);
    }
    catch (const std::exception& e) {
        warning(std::string("Impossible de créer le post !\n") + std::string(e.what()));
        delete editor;
        return;
    }

    logger_.info("Nouveau post créé avec succès");
    delete editor;
}

void MainWindow::on_remPostButton_clicked()
{
    if (!ctrl_blog_.has_blog()) return;

    QString post_id = ui->postList->selected_post_id();
    if (post_id == "") return;

    std::string post_id_str = post_id.toStdString();
    ctrl_blog_.remove_post(post_id_str);

    emit post_list_remove(post_id);
}

void MainWindow::on_editButton_clicked()
{
    if (!ctrl_blog_.has_blog()) return;

    std::string post_id = ui->postList->currentIndex().data().toString().toStdString();

    basics::Post cur = ctrl_blog_.post(post_id);
    QString orig_title = QString::fromStdString(cur.get_title());
    QString orig_author = QString::fromStdString(cur.get_author());
    QString orig_life = QString::fromStdString(cur.get_life());

    PostEditor *editor = new PostEditor(orig_title, orig_author, orig_life, this);
    int code = editor->exec();
    if (code == QDialog::Rejected) {
        delete editor;
        return;
    }

    std::string title = editor->get_post_title();
    std::string author = editor->get_post_author();
    std::string life = editor->get_post_life();

    try {
        cur = ctrl_blog_.edit_post(post_id, title, author, life);
    }
    catch (const std::exception& e) {
        warning(std::string("Impossible de mettre à jour le post :\n") + std::string(e.what()));
        delete editor;
        return;
    }

    QString post_id_updated = QString::fromStdString(cur.get_timestamp_str());
    emit post_changed(post_id_updated);
    logger_.info("Post édité avec succès");
    delete editor;
}

void MainWindow::on_blogCB_currentIndexChanged(const QString &text) 
{
    std::string blog_folder_path = text.toStdString();
    if (blog_folder_path == ctrl_blog_.get_blog_path()) {
        status("Blog déjà chargé !");
        return;
    }
    
    if (blog_history_.indexOf(text) < 0) {
        blog_history_ << text;
    }

    ctrl_blog_.open_blog(blog_folder_path);

    emit post_list_changed(ctrl_blog_.post_list());
}


void MainWindow::set_blog_display(const QString& blog_path)
{
    if (blog_history_.indexOf(blog_path) < 0) {
        blog_history_ << blog_path;
    }

    bool old_state = ui->blogCB->blockSignals(true);

    int index = ui->blogCB->findText(blog_path);
    if (index < 0) {
        ui->blogCB->addItem(blog_path);
        index = ui->blogCB->findText(blog_path);
    }

    ui->blogCB->setCurrentIndex(index);
    emit post_list_changed(ctrl_blog_.post_list());

    ui->blogCB->blockSignals(old_state);
}

void MainWindow::set_post_display(const QString& post_id)
{
    try {
        std::string post_id_str = post_id.toStdString();
        basics::Post post = ctrl_blog_.post(post_id_str);
        std::string post_content_str = post.get_life();
        QString post_content = QString::fromStdString(post_content_str);
        ui->postDisplay->setText(post_content);
    }
    catch (const std::exception& e) {
        warning(std::string("Impossible d'afficher le post !\n") + std::string(e.what()));
        return;
    }
}

void MainWindow::empty_post_display()
{
    ui->postDisplay->clear();
}

void MainWindow::warning(std::string message) 
{
    QMessageBox::information(this, QString::fromStdString("Warning !"), QString::fromStdString(message));
}

void MainWindow::status(std::string status, int seconds)
{
    ui->statusBar->showMessage(QString::fromStdString(status), seconds * 1000);
}

