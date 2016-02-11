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

// TO DEL
#include <iostream>

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

    logger_.info("Démarrage de l'application Pimp My Blog");
    logger_.info("Version : EN COURS DE DEVELOPPEMENT");    

    status("Aucun blog chargé");
    
//    ui->blogCB->addItem(tr("(Aucun)"));
    update_frame();
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


    blog_history_.push_back(new_blog_path);
    update_frame();
    
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
    if(std::find(blog_history_.begin(), blog_history_.end(), blog_folder_path) == blog_history_.end()) {
        blog_history_.push_back(blog_folder_path);
    }
    
    status("Blog chargé !");
    update_frame();
}

void MainWindow::on_addPostButton_clicked()
{
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
        std::string new_blog_path = ctrl_blog_.add_post_to_current_blog(title, author, life);
    }
    catch (const std::exception& e) {
        warning(std::string("Impossible de créer le blog !\n") + std::string(e.what()));
        delete editor;
        return;
    }
    
    update_frame();
    
    logger_.info("Nouveau blog créé avec succès");
    delete editor;
}

void MainWindow::on_remPostButton_clicked()
{
    update_frame();
}

void MainWindow::on_blogCB_currentIndexChanged(const QString &text) 
{
    if (clearing_combo_) return;

    std::string blog_folder_path = text.toUtf8().constData();

    if (blog_folder_path == ctrl_blog_.get_blog_path()) {
        status("Blog déjà chargé !");
        return;
    }
    
    std::string text_str = text.toStdString();
    ctrl_blog_.open_blog(text_str);

    update_frame();
}

void MainWindow::on_postList_clicked(const QModelIndex & index) 
{
    std::string post_id = index.data().toString().toStdString();
    try {
        ui->postDisplay->setText(QString::fromStdString(ctrl_blog_.get_post_content(post_id)));    
    }
    catch (const std::exception& e) {
        warning(std::string("Impossible d'afficher le post !\n") + std::string(e.what()));
        return;
    }
}

void MainWindow::update_post_list()
{
    std::vector<std::string> post_ids = ctrl_blog_.get_post_id_list();
    std::vector<std::string>::const_iterator it = post_ids.begin();
    std::vector<std::string>::const_iterator end = post_ids.end();
 
    QStringListModel *model = new QStringListModel();
    QStringList post_id_list;

    for (; it != end; ++it) {
        post_id_list << QString::fromStdString(*it);
    }
    
    model->setStringList(post_id_list);
    ui->postList->setModel(model);    
}

void MainWindow::update_blog_combobox() 
{
    clearing_combo_ = true;
    ui->blogCB->clear();

    if (!ctrl_blog_.has_current_blog() && blog_history_.size() == 0) {
        ui->blogCB->setEnabled(false);
        clearing_combo_ = false;
        return;
    }

    ui->blogCB->setEnabled(true);
    
    std::vector<std::string>::const_iterator it = blog_history_.begin();
    std::vector<std::string>::const_iterator end = blog_history_.end();
    
    QStringList fucking_qt_list;
    
    for (; it != end; ++it) {
        fucking_qt_list << QString::fromStdString(*it);
    }
    
    ui->blogCB->addItems(fucking_qt_list);

    int curr_index = ui->blogCB->findText(QString::fromStdString(ctrl_blog_.get_blog_path()));
    ui->blogCB->setCurrentIndex(curr_index);

    clearing_combo_ = false;
}

void MainWindow::update_frame() 
{
    update_post_list();
    update_blog_combobox();
}

void MainWindow::warning(std::string message) 
{
    QMessageBox::information(this, QString::fromStdString("Warning !"), QString::fromStdString(message));
}

void MainWindow::status(std::string status, int seconds)
{
    ui->statusBar->showMessage(QString::fromStdString(status), seconds * 1000);
}

