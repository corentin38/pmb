#include "mainwindow.hpp"
#include <ui_mainwindow.h>
#include <QMessageBox>
#include <QFileDialog>
#include <stdexcept>
#include <QStringList>
#include <vector>
//#include "blogwizard.hpp"
  //#include "posteditor.hpp"

namespace bfs = boost::filesystem;

MainWindow::MainWindow(basics::Simple_logger logger, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    logger_(logger),
    ctrl_blog_(logger)
{
    ui->setupUi(this);

    logger_.info("Démarrage de l'application Pimp My Blog");
    logger_.info("Version : EN COURS DE DEVELOPPEMENT");    

    status("Aucun blog chargé");
    
    ui->blogCB->addItem(tr("(Aucun)"));
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

    clear_fields();
    status("Blog publié !");
}

void MainWindow::on_clearButton_clicked() 
{
    clear_fields();
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
    
    try {
        std::string new_blog_path = ctrl_blog_.create_new_blog(name, blog_path, override, sample);
    }
    catch (const std::exception& e) {
        warning(std::string("Impossible de créer le blog !\n") + std::string(e.what()));
        delete wiz;
        return;
    }
    
    add_and_select_item(new_blog_path);
    
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

    status("Blog chargé !");
    
    add_and_select_item(blog_folder.string());
}

void MainWindow::on_addPostButton_clicked()
{
    PostEditor *editor = new PostEditor(this);
    int code = editor->exec();
    if (code == QDialog::Rejected) {
        delete editor;
        return;
    }
}

void MainWindow::on_remPostButton_clicked()
{
}

void MainWindow::on_blogCB_currentIndexChanged(const QString &text) 
{
    std::string blog_folder_path = text.toUtf8().constData();

    if (blog_folder_path == "(Aucun)") 
        return;
 
    if (blog_folder_path == ctrl_blog_->get_current_blog_path()) {
        status("Blog déjà chargé !");
        return;
    }
    
    ctr_blog_->select_blog(text);
}

void MainWindow::update_blog_list()
{
    ui->blogCB->clear();

    std::vector<std::string> blog_list = ctrl_blog_.get_blog_names();
    std::vector<std::string>::const_iterator it = blog_list.begin();
    std::vector<std::string>::const_iterator end = blog_list.end();
    
    QStringList fucking_qt_list;
    
    for (; it != end; ++it) {
        fucking_qt_list << QString::fromStdString(*it);
    }
    
    ui->blogCB->addItems(fucking_qt_list);

    int curr_index = ui->blogCB->findText(QString::fromStdString(ctrl_blog_->get_current_blog_path()));
    ui->blogCB->setCurrentIndex(curr_index);
}

void MainWindow::warning(std::string message) 
{
    QMessageBox::information(this, QString::fromStdString("Warning !"), QString::fromStdString(message));
}

void MainWindow::status(std::string status, int seconds)
{
    ui->statusBar->showMessage(QString::fromStdString(status), seconds * 1000);
}

