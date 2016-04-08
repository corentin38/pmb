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
 * @file posteditor.hpp
 */

#ifndef POSTEDITOR_HPP
#define POSTEDITOR_HPP

#include <QDialog>

namespace Ui {
class PostEditor;
}

class PostEditor : public QDialog
{
    Q_OBJECT

public:
    explicit PostEditor(QWidget *parent = 0, QString last_author = "");
    PostEditor(QString title, QString author, QString life, QWidget *parent = 0);
    ~PostEditor();

    const std::string get_post_title() const;
    const std::string get_post_author() const;
    const std::string get_post_life() const;

private slots:
    void on_clearButton_clicked();

private:
    Ui::PostEditor *ui;
};

#endif
