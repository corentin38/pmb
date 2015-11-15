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
 * @file boost_utils.cpp
 */

#include "utils/boost_utils.hpp"
#include <stdexcept>
#include <sstream>

void basics::copy_folder(const bfs::path& frompath, const bfs::path& topath) 
{
    // Check whether the function call is valid
    if (!bfs::exists(frompath) || !bfs::is_directory(frompath)) {
        std::stringstream err;
        err << "Source directory " << frompath.string() << " does not exist or is not a directory.";
        throw std::runtime_error(err.str());
    }
    if(bfs::exists(topath)) {
        std::stringstream err;
        err << "Destination directory " << topath.string() << " already exists.";
        throw std::runtime_error(err.str());
    }
    // Create the destination directory
    if(!bfs::create_directory(topath))
    {
        std::stringstream err;
        err << "Unable to create destination directory " << topath.string();
        throw std::runtime_error(err.str());
    }

    // Iterate through the source directory
    for(bfs::directory_iterator file(frompath); file != bfs::directory_iterator(); ++file) {
        bfs::path current(file->path());
        
        if(bfs::is_directory(current)) {
            // Found directory: Recursion
            copy_folder(current, topath / current.filename());
        }
        else {
            // Found file: Copy
            bfs::copy_file(current, topath / current.filename());
        }
    }
}

