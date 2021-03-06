/**
 * This file is part of [[[PROJECT]]].
 * 
 * [[[PROJECT]]] is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * [[[PROJECT]]] is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with [[[PROJECT]]].  If not, see <http://www.gnu.org/licenses/>. 
 */ 

/**
 * @author Corentin MARCIAU	<corentin@marciau.fr>
 */

/**
 * @file interface_blog.hpp
 */

#ifndef INTERFACE_BLOG_HPP
#define INTERFACE_BLOG_HPP

#include <string>
#include <boost/filesystem.hpp>
#include <blog/post.hpp>
#include <blog/configuration_blog.hpp>

namespace basics {

namespace bfs = boost::filesystem;

class Interface_blog {
   
public:
    virtual ~Interface_blog() {};

    virtual std::vector<basics::Post> get_posts() = 0;
    virtual std::vector<std::string> get_post_ids() = 0;
    virtual std::string get_post_content(std::string) = 0;
    virtual basics::Post get_post(std::string&) = 0;
    
    virtual basics::Post add_post(const std::string title, const std::string author, const std::string life) = 0;
    virtual basics::Post edit_post(std::string&, std::string&, std::string&, std::string&) = 0;
    virtual void remove_post(std::string&) = 0;

    virtual std::string get_blog_path() = 0;
    virtual bfs::path get_blog_folder() = 0;
    virtual bfs::path get_template_file() = 0;

    virtual bfs::path get_content_file() = 0;

    virtual basics::Configuration_blog get_config() = 0;
    
};

} // namespace

#endif
