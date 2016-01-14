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

#include <blog/interface_blog.hpp>
#include <boost/filesystem.hpp>
#include <string>
#include <vector>
#include <map>
#include <blog/post.hpp>
#include <blog/persistor_blog.hpp>

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

    std::vector<basics::Post> get_posts();

    void add_post(std::string, std::string, std::string);

    void generate(const int post_per_page = 10, const std::string page_base_name = "index");

    inline std::string get_blog_path() 
    {
        return blog_instance_folder_.string();
    }

    inline bfs::path get_blog_folder() 
    {
        return blog_instance_folder_;
    }

    // Utility
    template<class U, class T>
    static std::vector<T> map_values( const std::map<U, T> &input_map );
    
private:
    std::map<bdt::ptime, basics::Post> post_index_;    

    bfs::path blog_instance_folder_;
    bfs::path content_file_;
    bfs::path archive_folder_;
    bfs::path engine_folder_;
    bfs::path output_folder_;
    bfs::path xsl_file_;

    basics::Persistor_blog persistor_;   
};

} // namespace

#endif
