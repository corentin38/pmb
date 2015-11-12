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
 * @file blog_local.hpp
 */

#ifndef BLOG_LOCAL_HPP
#define BLOG_LOCAL_HPP

#include <string>

extern "C" {    
#include "post/post.h"
}

namespace basics {

class Blog_local : Interface_blog {
   
public:
    Blog_local(std::string content_path);
    ~Blog_local();

    void add_post(std::string, std::string, std::string);
    int generate(const std::string output_path, const int post_per_page = 10, const std::string page_base_name = "index");

    inline void set_content_file(path content_file) 
    {
        content_file_ = content_file;
    }

    inline void set_xsl_file(path xsl_file) 
    {
        xsl_file_ = xsl_file;
    }

    inline void set_blog_instance_folder(path blog_instance_folder) 
    {
        blog_instance_folder_ = blog_instance_folder;
    }

    inline void set_archive_folder(path archive_folder) 
    {
        archive_folder_ = archive_folder;
    }

    inline void set_engine_folder(path engine_folder) 
    {
        engine_folder_ = engine_folder;
    }


    
private:
    // Wrapper C structures for all libxml2 stuff
    BlogContent content_ptr_;
    BlogRoot root_ptr_;
    BlogXsl xsl_ptr_;

    std::string content_path_;
    
    bool content_loaded_;
    bool root_loaded_;
    bool xsl_loaded_;

    path content_file_;
    path xsl_file_;

    path blog_instance_folder_;
    path archive_folder_;
    path engine_folder_;

    void load_content(std::string);
    void load_root();
    void load_xsl(std::string);
    
    

   
};

} // namespace

#endif
