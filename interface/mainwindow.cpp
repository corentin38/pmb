#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include "blog/factory_blog.hpp"
#include "blogwizard.hpp"
#include <QMessageBox>
#include <iostream>
#include <boost/filesystem.hpp>
#include "utils/simple_logger.hpp"

namespace bfs = boost::filesystem;

MainWindow::MainWindow(QWidget *parent, int log_level, std::string blog_folder_path) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    logger_(log_level, blog_folder_path)
//    blog_(basics::Blog("/home/corentin/work/projects/basics/pmb/resources/content.xml"))
{
    ui->setupUi(this);

    logger_.info("Démarrage de l'application Pimp My Blog");
    logger_.info("Version : EN COURS DE DEVELOPPEMENT");
    
    
//    connect(ui->actionNouveau, SIGNAL(triggered()), this, SLOT(on_nouveauButton_clicked()));
    
//    Config config;
//    std::string last_edited_blog = config.get_last_edited_blog();

//    if (!last_edited_blog.isEmpty()) {
        

//    Factory_blog factory;
//    blog_ = factory.load_local_instance(last_edited_blog);
//}

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_generateButton_clicked()
{
    logger_.info("Début de l'ajout d'un nouveau post et de la génération du blog");
    
    std::string title =  ui->titleEdit->text().toStdString();
    std::string author =  ui->authorEdit->text().toStdString();
    std::string life =  ui->lifeEdit->toPlainText().toStdString();
    logger_.info("Titre : \n\t" + title);
    logger_.info("Auteur : \n\t" + author);
    logger_.info("life : \n\t" + life);

    blog_->add_post(title, author, life);
    blog_->generate();

    clear_fields();

    logger_.info("Post ajouté et blog généré");
}

void MainWindow::on_clearButton_clicked() 
{
    clear_fields();
}

void MainWindow::on_actionNew_triggered() 
{
    logger_.info("Ouverture de l'assistant de création de blog");

    BlogWizard *wiz = new BlogWizard(this);
    int code = wiz->exec();
    if (code == QDialog::Rejected) {
        logger_.info("Annulé");
        return;
    }

    std::string name = wiz->get_blog_name();
    std::string blog_path = wiz->get_blog_path();
    bool override = wiz->get_override_checked();
    bool sample = wiz->get_sample_checked();

    if (name.empty()) {
        warning("Aucun nom de blog n'a été fourni !\n"
                "Abandon de la création du blog.");
        return;
    }

    if (blog_path.empty()) {
        warning("Aucun dossier de blog n'a été fourni !\n"
                "Abandon de la création du blog.");
        return;
    }
    
    bfs::path blog_parent_folder(blog_path);
    bfs::path blog_folder = blog_parent_folder / name;

    try {
        basics::Factory_blog fact;
        logger_.info("Début de la création du blog. Dossier : " + blog_folder.string());
        if (override) logger_.info("En supprimant un éventuel dossier existant");
        if (sample) logger_.info("En ajoutant un contenu d'exemple");
        blog_ = fact.create_local_instance(blog_folder.string(), override, sample);
    }
    catch (const std::exception& e) {
        warning(std::string("Impossible de créer le blog !\n") + std::string(e.what()));
    }
    
    logger_.info("Nouveau blog créé avec succès");
}

void MainWindow::on_actionOpen_triggered() 
{
    logger_.info("Chargement d'une instance existante de blog");
    basics::Factory_blog fact;
    blog_ = fact.load_local_instance("/home/corentin/blog/testor/");
    logger_.info("Instance chargée : /home/mes couilles");
}

void MainWindow::clear_fields() 
{
    ui->titleEdit->clear();
    ui->authorEdit->clear();
    ui->lifeEdit->clear();
}

void MainWindow::warning(std::string message) 
{
    QMessageBox::information(this, QString::fromStdString("Warning !"), QString::fromStdString(message));
}

