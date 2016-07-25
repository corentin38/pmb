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
#include <utils/boost_utils.hpp>
#include <blog/generator.hpp>
#include <blog/factory_blog.hpp>
#include <blog/persistable_blog.hpp>
#include <blog/ssh_moulinator.hpp>
#include <iostream>
#include <stdexcept>

basics::Controller_blog::Controller_blog(basics::Simple_logger logger)
    : logger_(logger), current_blog_(), persistor_()
{
}

// Blog Control --------------------------------------------------
bool basics::Controller_blog::has_blog() const
{
    if (current_blog_) {
        return true;
    }
    else {
        return false;
    }
}

std::string basics::Controller_blog::create_blog(std::string &blog_name, std::string &blog_parent_path, bool override, bool sample)
{
    bfs::path blog_parent_folder(blog_parent_path);
    bfs::path blog_folder = blog_parent_folder / blog_name;

    logger_.info("Début de la création du blog. Dossier : " + blog_folder.string());
    if (override) logger_.info("En supprimant un éventuel dossier existant");
    if (sample) logger_.info("En ajoutant un contenu d'exemple");

    basics::Factory_blog fact;
    current_blog_ = fact.create_local_instance(blog_folder.string(), override, sample);

    return current_blog_->get_blog_path();
}

std::string basics::Controller_blog::open_blog(std::string &blog_folder_path)
{
    bfs::path blog_folder(blog_folder_path);

    if (!bfs::exists(blog_folder) || !bfs::is_directory(blog_folder)) {
        throw new std::runtime_error("Invalid blog folder");
    }

    if (has_current_blog() && blog_folder == current_blog_->get_blog_folder()) {
        // Blog already loaded
        return blog_folder.string();
    }

    basics::Factory_blog fact;
    current_blog_ = fact.load_local_instance(blog_folder.string());

    logger_.info(std::string("Instance chargée : ") + blog_folder_path);
    return blog_folder.string();
}

void basics::Controller_blog::generate_blog()
{
    if (!this->has_current_blog()) {
        throw new std::runtime_error("No blog currently selected");
    }

    logger_.info("Début de la génération du blog");
    basics::Generator gen;
    basics::Persistable_blog blog(current_blog_->get_posts(),
                                  current_blog_->get_config());

    gen.templatize_the_fucker(current_blog_->get_template_file(),
                              current_blog_->get_blog_folder(),
                              blog);

    logger_.info("Blog généré");
}

// Blog Info --------------------------------------------------
std::vector<std::string> basics::Controller_blog::post_id_list()
{
    if (!has_blog()) {
        std::vector<std::string> empty;
        return empty;
    }

    return current_blog_->get_post_ids();
}

std::vector<basics::Post> basics::Controller_blog::post_list()
{
    if (!has_blog()) {
        std::vector<basics::Post> empty;
        return empty;
    }

    return current_blog_->get_posts();
}

// Post Control --------------------------------------------------

basics::Post basics::Controller_blog::post(std::string& timestamp_str)
{
    return current_blog_->get_post(timestamp_str);
}

basics::Post basics::Controller_blog::add_post(std::string& title,
                                              std::string& author,
                                              std::string& life)
{
    if (!has_blog()) {
        throw new std::runtime_error("No blog currently selected");
    }

    basics::Post post = current_blog_->add_post(title, author, life);
    persist_current_blog();
    return post;
}

basics::Post basics::Controller_blog::edit_post(std::string& timestamp_str,
                                        std::string& title,
                                        std::string& author,
                                        std::string& life)
{
    if (!has_blog()) {
        throw new std::runtime_error("No blog currently selected");
    }

    basics::Post post = current_blog_->edit_post(timestamp_str, title, author, life);
    persist_current_blog();
    return post;
}

void basics::Controller_blog::remove_post(std::string& timestamp_str)
{
    current_blog_->remove_post(timestamp_str);
    persist_current_blog();
}

// SSH ------------------------------------------------------
void basics::Controller_blog::submit_to_server(std::string& remote_address, std::string& remote_blog_path)
{
    if (!has_current_blog()) {
        return;
    }

    logger_.info("To the server !");
    basics::Ssh_moulinator ssh;

    std::string bp = blog_path();
    ssh.submit(remote_address, remote_blog_path, bp);
}

bool basics::Controller_blog::check_if_synchronized(std::string& remote_address, std::string& remote_blog_path)
{
    if (!has_current_blog()) {
        return false;
    }

    logger_.info("Let's get a look at the server...");
    basics::Ssh_moulinator ssh;

    std::string bp = blog_path();
    return ssh.is_synchronized(remote_address, remote_blog_path, bp);
}

// Private --------------------------------------------------
void basics::Controller_blog::persist_current_blog()
{
    if (!has_current_blog()) {
        return;
    }

    basics::Persistor_blog persistor;
    basics::Persistable_blog blog(current_blog_->get_posts(), current_blog_->get_config());

    persistor.write_blog(current_blog_->get_content_file(), blog);
}

// Deprecated --------------------------------------------------
std::string basics::Controller_blog::create_new_blog(std::string &blog_name, std::string &blog_parent_path, bool override, bool sample)
{
    return create_blog(blog_name, blog_parent_path, override, sample);
}

std::string basics::Controller_blog::get_post_content(std::string &timestamp)
{
    if (!has_current_blog()) {
        return "";
    }

    std::string life = current_blog_->get_post_content(timestamp);
    return life;
}

std::string
basics::Controller_blog::add_post_to_current_blog(
    std::string& title,
    std::string& author,
    std::string& life)
{
    add_post(title, author, life);
    return "greetings from add_post_to_current_blog";
}

bool basics::Controller_blog::has_current_blog() const
{
    return has_blog();
}

void basics::Controller_blog::generate_current_blog()
{
    generate_blog();
}

std::vector<std::string> basics::Controller_blog::get_post_id_list()
{
    return post_id_list();
}
