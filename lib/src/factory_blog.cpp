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
#include "blog/blog_local.hpp"
#include "blog_constants.hpp"
#include "utils/boost_utils.hpp"

#include <iostream>
#include <stdexcept>
#include <sstream>

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
    bfs::path engine_subdir = blog_folder / const_engine_subdir;
    bfs::path output_subdir = blog_folder / const_output_subdir;
    bfs::path img_subdir = output_subdir / const_img_subdir;
    
    bfs::create_directory(archive_subdir);
    bfs::create_directory(engine_subdir);
    bfs::create_directory(output_subdir);
    bfs::create_directory(img_subdir);    

    // Copy xsl and config default file
    bfs::path xsl_resource( basics::getStylesheetResource() );
    bfs::path xsl_dest = engine_subdir / const_xsl_filename;
    bfs::copy_file(xsl_resource, xsl_dest);
    
    bfs::path config_resource( basics::getConfigResource() );
    bfs::path config_dest = engine_subdir / const_config_filename;
    bfs::copy_file(config_resource, config_dest);

    // Copy bootstrap directory and css
    bfs::path bootstrap_resource( basics::getBootstrapResource() );
    bfs::path bootstrap_dest = output_subdir / const_bootstrap_subdir;
    basics::copy_folder(bootstrap_resource, bootstrap_dest);
    
    bfs::path css_resource( basics::getCssResource() );
    bfs::path css_dest = output_subdir / const_css_filename;
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

    std::unique_ptr<basics::Interface_blog> local_blog_ptr( 
        new basics::Blog_local(
            blog_folder,
            content_dest,
            archive_subdir,
            engine_subdir,
            output_subdir,
            xsl_dest) 
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
    bfs::path engine_subdir = blog_folder / const_engine_subdir;
    bfs::path output_subdir = blog_folder / const_output_subdir;
    bfs::path img_subdir = output_subdir / const_img_subdir;
    
    if (!bfs::exists(archive_subdir) ||
        !bfs::exists(engine_subdir) ||
        !bfs::exists(output_subdir) ||
        !bfs::exists(img_subdir)) {
        std::stringstream err;
        err << "Corrupted blog instance : missing subdirectory";
        throw std::runtime_error( err.str() );
    }

    bfs::path content_file = blog_folder / const_content_filename;
    bfs::path xsl_file = engine_subdir / const_xsl_filename;

    if (!bfs::exists(content_file) ||
        !bfs::exists(xsl_file)) {
        std::stringstream err;
        err << "Corrupted blog instance : missing content.xml or stylesheet.xsl";
        throw std::runtime_error( err.str() );
    }    

    std::unique_ptr<basics::Interface_blog> local_blog_ptr( 
        new basics::Blog_local(
            blog_folder,
            content_file,
            archive_subdir,
            engine_subdir,
            output_subdir,
            xsl_file)
        );
    
    return std::move(local_blog_ptr);
}
/*
void basics::Factory_blog::create_blog_arbo( bfs::path blog_folder ) 
{
    // Fetching all blog instance components
    bfs::path archive_subdir = blog_folder / const_archive_subdir;
    bfs::path engine_subdir = blog_folder / const_engine_subdir;
    bfs::path output_subdir = blog_folder / const_output_subdir;
    bfs::path img_subdir = output_subdir / const_img_subdir;
    
    bfs::create_directory(archive_subdir);
    bfs::create_directory(engine_subdir);
    bfs::create_directory(output_subdir);
    bfs::create_directory(img_subdir);    
}

*/

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
