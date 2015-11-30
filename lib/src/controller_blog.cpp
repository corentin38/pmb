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
 * @file controller_blog.cpp
 */

#include <blog/controller_blog.hpp>

#include <blog/factory_blog.hpp>
#include "blogwizard.hpp"
#include <iostream>
#include <stdexcept>

basics::Controller_blog::Controller_blog(basics::Simple_logger logger, ) 
    : logger_(logger), current_blog_(), all_blogs()
{
}

bool basics::Controller_blog::has_current_blog()
{
    return current_blog_;
}
    
void basics::Controller_blog::generate_current_blog()
{
    if (!this.has_current_blog()) {
        throw new std::runtime_error("No blog currently selected");
    }

    logger_.info("Début de l'ajout d'un nouveau post et de la génération du blog");

    current_blog_->generate();
    
//    std::string title =  ui->titleEdit->text().toStdString();
//    std::string author =  ui->authorEdit->text().toStdString();
//    std::string life =  ui->lifeEdit->toPlainText().toStdString();
//    logger_.info("Titre : " + title);
//    logger_.info("Auteur : " + author);
//    logger_.info("life : " + life);

//    blog_->add_post(title, author, life);


    logger_.info("Post ajouté et blog généré");
}

    
std::string basics::Controller_blog::create_new_blog(std::string &blog_name, std::string &blog_parent_path, bool override, bool sample)
{
    bfs::path blog_parent_folder(blog_parent_path);
    bfs::path blog_folder = blog_parent_folder / blog_name;

    logger_.info("Début de la création du blog. Dossier : " + blog_folder.string());
    if (override) logger_.info("En supprimant un éventuel dossier existant");
    if (sample) logger_.info("En ajoutant un contenu d'exemple");

    basics::Factory_blog fact;
    current_blog_ = fact.create_local_instance(blog_folder.string(), override, sample);

    all_blogs_->insert(current_blog_);

    return current_blog_->get_blog_path();
}

    
std::string basics::Controller_blog::open_blog(std::string &blog_folder_path)
{
    bfs::path blog_folder(blog_folder_path);

    if (!bfs::exists(blog_folder) || !bfs::is_directory(blog_folder)) {
        throw new std::runtime_error("Invalid blog folder");
    }    

    if (has_current_blog() && blog_folder == blog_->get_blog_folder()) {
        // Blog already loaded
        return;
    }

    basics::Factory_blog fact;
    current_blog_ = fact.load_local_instance(blog_folder.string());

    all_blogs_->insert(current_blog_);

    logger_.info(std::string("Instance chargée : ") + blog_folder_path);

    return blog_folder.string();
}
    
void basics::Controller_blog::select_blog(std::string &blog_folder_path)
{
    return open_blog(blog_folder_path);
}

std::vector<std::string> basics::Controller_blog::get_blog_names()
{
    std::vector<std::string> paths;
    
    std::vector<std::string>::const_iterator it = all_blogs_.begin();
    std::vector<std::string>::const_iterator end = all_blogs_.end();
    
    for (; it != end; ++it) {
        paths.push_back(*it);
    }
    
    return paths;
}

