/**
 * This file is part of PMB.
 * 
 * PMB is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * PMB is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with PMB.  If not, see <http://www.gnu.org/licenses/>. 
 */ 

/**
 * @author Corentin MARCIAU	<corentin@marciau.fr>
 */

/**
 * @file blogwizard.cpp
 */

#include "blogwizard.hpp"
#include "ui_blogwizard.h"
#include <iostream>
#include <QFileDialog>

BlogWizard::BlogWizard(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BlogWizard)
{
    ui->setupUi(this);
    
//    connect(ui->actionNouveau, SIGNAL(triggered()), this, SLOT(on_nouveauButton_clicked()));    
}

BlogWizard::~BlogWizard()
{
delete ui;
}
    
void BlogWizard::on_browseButton_clicked() 
{    
    ui->folderEdit->setText( 
        QFileDialog::getExistingDirectory(
            this,
            tr("Choisir un dossier pour le blog"),
            getenv("HOME")));
}

const std::string BlogWizard::get_blog_name() const
{
    return ui->nameEdit->text().toStdString();
}

const std::string BlogWizard::get_blog_path() const
{
    return ui->folderEdit->text().toStdString();
}

bool BlogWizard::get_override_checked() const
{
    return ui->overrideCheckbox->isChecked();
}

bool BlogWizard::get_sample_checked() const
{
    return ui->sampleCheckbox->isChecked();
}
