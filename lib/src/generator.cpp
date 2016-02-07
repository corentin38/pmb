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
 * @file generator.cpp
 */

#include <iostream>
#include <fstream>
#include <blog/generator.hpp>
#include <string>

basics::Generator::Generator() : buff_()
{
}

void basics::Generator::templatize_the_fucker(bfs::path template_path, 
                                              bfs::path destination_path,
                                              basics::Persistable_blog blog)
{
    init(template_path);
    
    // Config
    set_variable("title", "Ceci est mon titre !!!");
    
    // Posts
    for (int i=0; i<3; i++) {
        std::string titreline = "Ceci est mon titre #" + i;
        set_variable("post-title", titreline);
        feed_table("posts");
    }

    exec(destination_path, "index.html");    
    clear();
}

void basics::Generator::init(bfs::path template_path) 
{
    f_ptr_ = NULL;
    flateSetFile(&f_ptr_, fu(template_path.string()));
}

void basics::Generator::set_variable(std::string name, std::string value)
{
    flateSetVar(f_ptr_, fu(name), fu(value));
}

void basics::Generator::feed_table(std::string name) 
{
    flateDumpTableLine(f_ptr_, fu(name));
}

void basics::Generator::exec(bfs::path folder, std::string name) 
{
    bfs::path res = folder / bfs::path(name);
    std::string content(flatePage(f_ptr_));
    std::ofstream page(res.string());
    page << content;
    page.close();
}

    

char* basics::Generator::fu(std::string in) 
{
    char* another = new char [in.size() + 1];
    strcpy(another, in.c_str());
    buff_.push_back(another);
    return another;
}

void basics::Generator::clear() 
{
    flateFreeMem(f_ptr_);
    for (std::vector<char*>::iterator it = buff_.begin(); it != buff_.end(); ++it) {
        delete[] *it;
    }
}

    
