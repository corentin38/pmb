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
 * @file factory_blog.hpp
 */

#ifndef FACTORY_BLOG_HPP
#define FACTORY_BLOG_HPP

#include "blog/interface_blog.hpp"
#include <boost/filesystem.hpp>

namespace basics {

namespace bfs = boost::filesystem;

const std::string const_archive_subdir = "archive";
const std::string const_engine_subdir = "engine";
const std::string const_output_subdir = "output";
const std::string const_content_filename = "content.xml";
const std::string const_config_filename = "config.xml";
const std::string const_xsl_filename = "stylesheet.xsl";
const std::string const_img_subdir = "img";
const std::string const_save_sufix = "_content_archive.xml";
const std::string const_bootstrap_subdir = "dist";
const std::string const_css_filename = "blog.css";

class Factory_blog {

public:
    Factory_blog();

    std::unique_ptr<basics::Interface_blog> create_local_instance(
        std::string blog_path, 
        bool remove_previous_folder = false, 
        bool add_sample_content = true);

    std::unique_ptr<basics::Interface_blog> load_local_instance(std::string blog_folder_path);

    //Blog_ssh create_distant_instance(ssh_path blog_remote_folder);
    
private:
    void remove_blog_folder(bfs::path);
    void rmdir(bfs::path);
    void rmfile(bfs::path);
    void create_blog_folder(bfs::path);
    


   
};

} // namespace

#endif
