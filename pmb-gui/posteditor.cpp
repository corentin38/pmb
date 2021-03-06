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
 * @file posteditor.cpp
 */

#include "posteditor.hpp"
#include "ui_posteditor.h"
#include <iostream>
#include <QDateTime>

PostEditor::PostEditor(QWidget *parent, QString last_author) :
    QDialog(parent),
    ui(new Ui::PostEditor)
{
    ui->setupUi(this);

    if (!last_author.isEmpty()) {
        ui->authorEdit->setText(last_author);
    }

}

PostEditor::PostEditor(QString title, QString author, QString life, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PostEditor)
{
    ui->setupUi(this);

    ui->titleEdit->setText(title);
    ui->authorEdit->setText(author);
    ui->lifeEdit->setText(life);
}

PostEditor::~PostEditor()
{
    delete ui;
}

void PostEditor::on_clearButton_clicked()
{
    ui->titleEdit->clear();
    ui->authorEdit->clear();
    ui->lifeEdit->clear();
}

const std::string PostEditor::get_post_title() const
{
    return ui->titleEdit->text().toStdString();
}

const std::string PostEditor::get_post_author() const
{
    return ui->authorEdit->text().toStdString();
}

const std::string PostEditor::get_post_life() const
{
    return ui->lifeEdit->toPlainText().toStdString();
}
