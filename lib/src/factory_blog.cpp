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
 * @file factory_blog.cpp
 */

#include "blog/factory_blog.hpp"
#include "blog/interface_blog.hpp"

#include <iostream>
#include <stdexcept>
#include <sstream>

basics::Factory_blog::Factory_blog()
{
}

basics::Interface_blog* 
basics::Factory_blog::create_local_instance(
    std::string blog_folder, 
    bool remove_previous_folder, 
    bool add_sample_content) 
{
    bfs::path blog_path( blog_folder );
    
    if (bfs::exists(blog_path)) {
        if (remove_previous_folder) {
            remove_blog_folder(blog_path);
        }
        else {
            std::stringstream err;
            err << "Blog folder points to an existing directory";
            throw std::runtime_error(err.str());
        }
    }


basics::Interface_blog* blog;
basics::Interface_blog* blog2;

if (add_sample_content) {
return blog2;
}


return blog;



}

basics::Interface_blog* 
basics::Factory_blog::load_local_instance(bfs::path blog_folder)
{
basics::Interface_blog* blog = ;
basics::Interface_blog* blog2;

if (bfs::exists(blog_folder)) {
return blog2;
}


return blog;

}

void basics::Factory_blog::remove_blog_folder( bfs::path blog_folder ) 
{
    if (!bfs::exists(blog_folder) || !bfs::is_directory(blog_folder)) {
        std::stringstream err;
        err << "Blog folder to remove doesn't exist or isn't a directory";
        throw std::runtime_error(err.str());
    }

    // Fetching all blog instance components
    bfs::path archive_subdir = blog_folder / "archive";
    bfs::path engine_subdir = blog_folder / "engine";
    bfs::path output_subdir = blog_folder / "output";
    bfs::path content_file = blog_folder / "content.xml";

    // Removing all 
    rmdir(archive_subdir);
    rmdir(engine_subdir);
    rmdir(output_subdir);
    rmfile(content_file);

    if (bfs::is_empty(blog_folder)) {
        bfs::remove_all(blog_folder);
    }
}

void basics::Factory_blog::rmdir(bfs::path dir) 
{
    if (bfs::exists(dir) && bfs::is_directory(dir)) {
        bfs::remove_all(dir);
    }
}

void basics::Factory_blog::rmfile(bfs::path file) 
{
    if (bfs::exists(file) && !bfs::is_directory(file)) {
        bfs::remove_all(file);
    }
}

void basics::Factory_blog::create_blog_folder(bfs::path blog_folder) 
{
    if (!bfs::exists(blog_folder)) {
        bfs::create_directory(blog_folder);
    }

    bfs::path archive_subdir = blog_folder / "archive";
    bfs::path engine_subdir = blog_folder / "engine";
    bfs::path output_subdir = blog_folder / "output";
    bfs::path img_output_subdir = output_subdir / "img";

    bfs::create_directory(archive_subdir);
    bfs::create_directory(engine_subdir);
    bfs::create_directory(output_subdir);
    bfs::create_directory(img_output_subdir);
}
