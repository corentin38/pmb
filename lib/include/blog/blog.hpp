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
 * @file blog.hpp
 */

#ifndef _BLOG_HPP_
#define _BLOG_HPP_

#include <string>
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <libxml/tree.h>
#include <libxslt/transform.h>
#include <libxslt/xsltutils.h>

namespace basics {

class Blog {
   
public:
    Blog(std::string content_path);
    ~Blog();

    void add_post(std::string, std::string, std::string);
    void load_xsl(std::string);
    int generate(const std::string output_path, const int post_per_page = 10, const std::string page_base_name = "index");
    
private:
    std::string content_path_;

    xmlDocPtr doc_ptr_;
    bool content_loaded_;

    xmlNodePtr rootnode_ptr_;
    bool root_loaded_;

    xsltStylesheetPtr xsl_ptr_;
    bool xsl_loaded_;
    
    void load_content(std::string);
    void load_root();
    
    

   
};

} // namespace

#endif
