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
 * @file blog.cpp
 */

#include "blog/blog.hpp"


#include "post/post.h"

#include <iostream>
#include <stdexcept>
#include <sstream>

basics::Blog::Blog(const std::string content_path)
    : content_path_(content_path)
{
    try {
        load_content(content_path_);
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
    
    content_loaded_ = true;
    root_loaded_ = true;
}

basics::Blog::~Blog()
{
    if (content_loaded_) {
        xmlFreeDoc(doc_ptr_);
    }
}

void basics::Blog::load_content(std::string content_path)
{
    // Keep indentation
    xmlKeepBlanksDefault(0);

    // Ouverture du fichier XML
    doc_ptr_ = xmlParseFile(content_path.c_str());
    if (doc_ptr_ == NULL) {
        content_loaded_ = false;
        std::stringstream err;
        err << "Document XML invalide";
        throw std::runtime_error(err.str());
    }
}

void basics::Blog::load_root() 
{
    // Récupération de la racine
    rootnode_ptr_ = xmlDocGetRootElement(doc_ptr_);
    if (rootnode_ptr_ == NULL) {
        root_loaded_ = false;
        xmlFreeDoc(doc_ptr_);
        std::stringstream err;
        err << "Document XML vierge";
        throw std::runtime_error(err.str());
    }
}

void basics::Blog::add_post(std::string author, std::string title, std::string life) 
{
    xmlNodePtr post;
    
    // On appelle notre super fonction qui fait le node toute seule
    if ((post = createPostNode(author.c_str(), title.c_str(), life.c_str())) == NULL) {
        std::stringstream err;
        err << "Impossible de créer un nouveau post";
        throw std::runtime_error(err.str());
    }
    
    // Et on rajoute le noeud à la racine
    if (xmlAddChild(rootnode_ptr_, post) == NULL) {
        std::stringstream err;
        err << "Impossible d'ajouter le nouveau post à la racine";
        throw std::runtime_error(err.str());
    }
}

void basics::Blog::load_xsl(std::string xsl_path) 
{
    xsl_ptr_ = xsltParseStylesheetFile(BAD_CAST xsl_path.c_str());
    if (xsl_ptr_ == NULL) {
        xsl_loaded_ = false;
        std::stringstream err;
        err << "Feuille de style invalide";
        throw std::runtime_error(err.str());
    }
    xsl_loaded_ = true;
}

int basics::Blog::generate(const std::string output_path, const int post_per_page, const std::string page_base_name)
{
    // On tri pour avoir le post le plus récent en premier
    NodeList *posts = getPostsOrderByDate(doc_ptr_);

    // On découpe en content1.xml content2.xml ...
    DocList *pages = splitPostsByPage(posts, post_per_page);
   
    // On set les pagers (next, prev)
    setPagerAttributes(pages, page_base_name.c_str());

    // On save comme content0.xml, content1.xml ...
    for (int i=0; i<pages->docNr; i++) {        
        std::stringstream current_page_path;
        if (i>0) {
            current_page_path << output_path << page_base_name << i << ".html";
        }
        else {
            current_page_path << output_path << page_base_name << ".html";
        }

        xmlDocPtr res = xsltApplyStylesheet(xsl_ptr_, pages->docs[i], NULL);
        // Gérer les foirages IO
        xsltSaveResultToFilename(current_page_path.str().c_str(), res, xsl_ptr_, 0);
    }
    
    freeDocList(pages);

    return 0;
}

