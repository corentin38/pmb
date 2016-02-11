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

#include <blog/factory_blog.hpp>
#include <blog/interface_blog.hpp>
#include <blog/blog_local.hpp>
#include <blog_constants.hpp>
#include <blog/persistable_blog.hpp>
#include <utils/boost_utils.hpp>

#include <iostream>
#include <stdexcept>
#include <sstream>

#define BOOST_NO_CXX11_SCOPED_ENUMS
#define BOOST_NO_SCOPED_ENUMS

basics::Factory_blog::Factory_blog()
{
}

//   std::unique_ptr<basics::Data_prim> data_prim_ptr( new basics::I2osp_os2ip() );

std::unique_ptr<basics::Interface_blog> 
basics::Factory_blog::create_local_instance(
    std::string blog_path, 
    bool remove_previous_folder, 
    bool add_sample_content) 
{
    bfs::path blog_folder( blog_path );
    
    if (bfs::exists(blog_folder)) {
        if (remove_previous_folder) {
            remove_blog_folder(blog_folder);
        }
        else {
            throw std::runtime_error("Blog folder points to an existing directory");
        }
    }

    bfs::create_directory(blog_folder);

    // Fetching all blog instance components
    bfs::path archive_subdir = blog_folder / const_archive_subdir;
    bfs::path resources_subdir = blog_folder / const_resources_subdir;
    
    bfs::create_directory(archive_subdir);
    bfs::create_directory(resources_subdir);    

    // Copy default html template
    bfs::path template_resource( basics::getTemplateResource() );
    bfs::path template_dest = blog_folder / const_template_filename;
    bfs::copy_file(template_resource, template_dest);
    
    // Copy bootstrap directory and css
    bfs::path bootstrap_resource( basics::getBootstrapResource() );
    bfs::path bootstrap_dest = resources_subdir / const_bootstrap_subdir;
    basics::copy_folder(bootstrap_resource, bootstrap_dest);
    
    bfs::path css_resource( basics::getCssResource() );
    bfs::path css_dest = resources_subdir / const_css_filename;
    bfs::copy_file(css_resource, css_dest);
    
    bfs::path content_sample_resource( basics::getContentSampleResource() );
    bfs::path content_empty_resource( basics::getContentEmptyResource() );
    bfs::path content_dest = blog_folder / const_content_filename;
    
    if (add_sample_content) {
        bfs::copy_file(content_sample_resource, content_dest);        
    }
    else {
        bfs::copy_file(content_empty_resource, content_dest);        
    }

    basics::Persistor_blog persistor;
    basics::Persistable_blog blog = persistor.read_blog(content_dest);

    std::unique_ptr<basics::Interface_blog> local_blog_ptr( 
        new basics::Blog_local(
            blog_folder,
            content_dest,
            archive_subdir,
            resources_subdir,
            template_dest,
            blog.posts(),
            blog.config())
        );
    
    return std::move(local_blog_ptr);

}

std::unique_ptr<basics::Interface_blog> 
basics::Factory_blog::load_local_instance(std::string blog_folder_path)
{
    bfs::path blog_folder( blog_folder_path );
    
    if (!bfs::exists(blog_folder)) {
        std::stringstream err;
        err << "Provided blog folder doesn't exist";
        throw std::runtime_error( err.str() );
    }
    
    if (!bfs::is_directory(blog_folder)) {
        std::stringstream err;
        err << "Provided blog folder is not a directory";
        throw std::runtime_error( err.str() );
    }

    // Fetching all blog instance components
    bfs::path archive_subdir = blog_folder / const_archive_subdir;
    bfs::path resources_subdir = blog_folder / const_resources_subdir;
    
    if (!bfs::exists(archive_subdir) ||
        !bfs::exists(resources_subdir)) {
        std::stringstream err;
        err << "Corrupted blog instance : missing subdirectory";
        throw std::runtime_error( err.str() );
    }

    bfs::path content_file = blog_folder / const_content_filename;
    bfs::path template_file = blog_folder / const_template_filename;

    if (!bfs::exists(content_file) ||
        !bfs::exists(template_file)) {
        std::stringstream err;
        err << "Corrupted blog instance : missing "
            << const_content_filename << " or "
            << const_template_filename;
        throw std::runtime_error( err.str() );
    }    

    basics::Persistor_blog persistor;
    basics::Persistable_blog blog = persistor.read_blog(content_file);

    std::unique_ptr<basics::Interface_blog> local_blog_ptr( 
        new basics::Blog_local(
            blog_folder,
            content_file,
            archive_subdir,
            resources_subdir,
            template_file,
            blog.posts(),
            blog.config())
        );
    
    return std::move(local_blog_ptr);
}

void basics::Factory_blog::remove_blog_folder( bfs::path blog_folder ) 
{
    if (!bfs::exists(blog_folder) || !bfs::is_directory(blog_folder)) {
        std::stringstream err;
        err << "Blog folder to remove doesn't exist or isn't a directory";
        throw std::runtime_error(err.str());
    }

    // Fetching all blog instance components
    bfs::path archive_subdir = blog_folder / const_archive_subdir;
    bfs::path resources_subdir = blog_folder / const_resources_subdir;
    bfs::path content_file = blog_folder / const_content_filename;
    bfs::path template_file = blog_folder / const_template_filename;

    // Removing all 
    rmdir(archive_subdir);
    rmdir(resources_subdir);
    rmfile(content_file);
    rmfile(template_file);

    if (bfs::is_empty(blog_folder)) {
        bfs::remove_all(blog_folder);
    } else {
        std::stringstream err;
        err << "Blog directory not empty after removing all known blog files and dirs";
        throw std::runtime_error(err.str());
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

