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
 * @file blogwizard.hpp
 */

#ifndef BLOGWIZARD_HPP
#define BLOGWIZARD_HPP

#include <QDialog>

namespace Ui {
class BlogWizard;
}

class BlogWizard : public QDialog
{
    Q_OBJECT

public:
    explicit BlogWizard(QWidget *parent = 0);
    ~BlogWizard();

    const std::string get_blog_name() const;
    const std::string get_blog_path() const;
    bool get_override_checked() const;
    bool get_sample_checked() const;

private slots:
    void on_browseButton_clicked();

private:
    Ui::BlogWizard *ui;


};

#endif
