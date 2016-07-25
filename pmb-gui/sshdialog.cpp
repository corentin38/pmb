#include "sshdialog.hpp"
#include "ui_sshdialog.h"

SshDialog::SshDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SshDialog)
{
    ui->setupUi(this);
}

SshDialog::~SshDialog()
{
    delete ui;
}

std::string SshDialog::get_host() {
    return ui->host->text().toStdString();
}

std::string SshDialog::get_host_path() {
    return ui->path->text().toStdString();
}
