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

#include "blog/interface_blog.hpp"
#include <boost/filesystem.hpp>
#include <string>

extern "C" {    
#include "post/post.h"
}

namespace basics {

namespace bfs = boost::filesystem;

class Blog_local : public Interface_blog {
   
public:
    Blog_local(bfs::path blog_instance_folder, 
               bfs::path content_file, 
               bfs::path archive_folder,
               bfs::path engine_folder,
               bfs::path output_folder,
               bfs::path xsl_file);
    
    ~Blog_local();

    Blog_local(const basics::Blog_local&) = delete;
    Blog_local& operator=(const basics::Blog_local&) = delete;

    void add_post(std::string, std::string, std::string);
    void generate(const int post_per_page = 10, const std::string page_base_name = "index");
    bool is_ready();
    
private:
    // Wrapper C structures for all libxml2 stuff
    BlogContent content_ptr_;
    BlogRoot root_ptr_;
    BlogXsl xsl_ptr_;

    bfs::path blog_instance_folder_;
    bfs::path content_file_;
    bfs::path archive_folder_;
    bfs::path engine_folder_;
    bfs::path output_folder_;
    bfs::path xsl_file_;

    bool content_loaded_;
    bool root_loaded_;
    bool xsl_loaded_;

    void load_content();
    void load_root();
    void load_xsl();
    
    

   
};

} // namespace

#endif
