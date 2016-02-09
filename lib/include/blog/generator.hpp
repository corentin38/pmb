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
 * @file generator.hpp
 */

#ifndef GENERATOR_HPP
#define GENERATOR_HPP

#include <boost/filesystem.hpp>
#include <blog/persistable_blog.hpp>
#include <blog/configuration_blog.hpp>
#include <blog/post.hpp>
#include <vector>
#include <string>

extern "C" {    
#include <flate.h>
}

namespace basics {

namespace bfs = boost::filesystem;

class Generator {
   
public:
    Generator();
   
    void templatize_the_fucker(bfs::path template_path, 
                               bfs::path destination_path,
                               basics::Persistable_blog blog);

private:
    std::vector<char*> buff_;
    Flate *f_ptr_;

    void templatize_page(bfs::path, std::string, basics::Configuration_blog&, std::vector<basics::Post>&, std::string, std::string);
    
    void init(bfs::path);
    void set_variable(std::string, std::string);
    void feed_table(std::string);
    void exec(bfs::path, std::string);

    char* fu(std::string in);
    void clear();    
    void destroy();    

};

} // namespace

#endif
