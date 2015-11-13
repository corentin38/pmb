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
 * @file blog_local.cpp
 */

#include "blog/blog_local.hpp"

#include <iostream>
#include <stdexcept>
#include <sstream>

basics::Blog_local::Blog_local(
    bfs::path blog_instance_folder, 
    bfs::path content_file, 
    bfs::path archive_folder,
    bfs::path engine_folder,
    bfs::path output_folder,
    bfs::path xsl_file)
    : Interface_blog(), 
      content_ptr_(NULL),
      root_ptr_(NULL),
      xsl_ptr_(NULL),
      blog_instance_folder_(blog_instance_folder), 
      content_file_(content_file), 
      archive_folder_(archive_folder),
      engine_folder_(engine_folder),
      output_folder_(output_folder),
      xsl_file_(xsl_file),
      content_loaded_(false),
      root_loaded_(false),
      xsl_loaded_(false)
{
    try {
        load_content();
    }
    catch (const std::exception& e) {
        content_loaded_ = false;
        return;
    }

    try {
        load_root();
    }
    catch (const std::exception& e) {
        root_loaded_ = false;
        return;
    }

    try {
        load_xsl();
    }
    catch (const std::exception& e) {
        xsl_loaded_ = false;
        return;
    }
}

basics::Blog_local::~Blog_local()
{
    if (content_loaded_) {
        freeBlogContent(content_ptr_);
    }
}

void basics::Blog_local::load_content()
{
    content_ptr_ = loadBlogContent(content_file_.string().c_str());
    if (content_ptr_ == NULL) {
        content_loaded_ = false;
        std::stringstream err;
        err << "Document XML invalide";
        throw std::runtime_error(err.str());
    }

    content_loaded_ = true;
}

void basics::Blog_local::load_root() 
{
    // Récupération de la racine
    root_ptr_ = loadBlogRoot(content_ptr_);
    if (root_ptr_ == NULL) {
        root_loaded_ = false;
        content_loaded_ = false;
        freeBlogContent(content_ptr_);
        std::stringstream err;
        err << "Document XML vierge";
        throw std::runtime_error(err.str());
    }
    
    root_loaded_ = true;
}

void basics::Blog_local::load_xsl() 
{
    xsl_ptr_ = loadBlogXsl(xsl_file_.string().c_str());
    if (xsl_ptr_ == NULL) {
        xsl_loaded_ = false;
        std::stringstream err;
        err << "Feuille de style invalide";
        throw std::runtime_error(err.str());
    }

    xsl_loaded_ = true;
}

void basics::Blog_local::add_post(std::string title, std::string author, std::string life) 
{
    if (!content_loaded_ || !root_loaded_) {
        std::stringstream err;
        err << "Unable to add post. Content missing";
        throw std::runtime_error(err.str());
    }
    
    BlogPost post;
    
    // On appelle notre super fonction qui fait le node toute seule
    if ((post = createPost(author.c_str(), title.c_str(), life.c_str())) == NULL) {
        std::stringstream err;
        err << "Impossible de créer un nouveau post";
        throw std::runtime_error(err.str());
    }
    
    // Et on rajoute le noeud à la racine
    if (addPostToRoot(root_ptr_, post) == NULL) {
        std::stringstream err;
        err << "Impossible d'ajouter le nouveau post à la racine";
        throw std::runtime_error(err.str());
    }
}

void basics::Blog_local::generate(const int post_per_page, const std::string page_base_name)
{
    if (!xsl_loaded_) {
        load_xsl();
    }

    if (!xsl_loaded_) {
        std::stringstream err;
        err << "Unable to generate. XSLT sheet missing";
        throw std::runtime_error(err.str());
    }    

    // On sauvegarde le contenu précédent dans le dossier d'archive
    // TODO
    //xmlSaveFormatFile(BAD_CAST archiveFolder, content_ptr_, 1);


    // On tri pour avoir le post le plus récent en premier
    NodeList *posts = getPostsOrderByDate(content_ptr_);

    // On découpe en content1.xml content2.xml ...
    DocList *pages = splitPostsByPage(posts, post_per_page);
   
    // On set les pagers (next, prev)
    setPagerAttributes(pages, page_base_name.c_str());

    // On save comme content0.xml, content1.xml ...
    for (int i=0; i<pages->docNr; i++) {        
        std::stringstream current_page_path;
        if (i>0) {
            current_page_path << output_folder_.string() << "/" << page_base_name << i << ".html";
        }
        else {
            current_page_path << output_folder_.string() << "/" << page_base_name << ".html";
        }

        BlogHtmlPage res = runXslOnPage(xsl_ptr_, pages, i);
        // Gérer les foirages IO
        saveBlogHtmlPage(current_page_path.str().c_str(), res, xsl_ptr_);
    }
    
    freeDocList(pages);
}

bool basics::Blog_local::is_ready() 
{
    return true;
}
