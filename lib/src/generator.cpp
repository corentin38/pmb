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
extern "C" {    
#include <flate.h>
}


basics::Generator::Generator() : buff_()
{
}

void basics::Generator::templatize_the_fucker(bfs::path template_path, 
                                              bfs::path destination_path,
                                              basics::Persistable_blog blog)
{
    Flate *f = NULL;
    flateSetFile(&f, fu( template_path.string() ));

    // Config
    flateSetVar(f, fu("title"), fu("Ceci est mon titre !!!"));
    
    // Posts
    for (int i=0; i<3; i++) {
        flateSetVar(f, fu("post-title"), fu("Ceci est le titre #" + i));
        flateDumpTableLine(f, fu("posts"));
    }

    std::string blabla(flatePage(f));
    
    std::ofstream page("index.html");
    page << blabla;
    page.close();
    
    flateFreeMem(f);
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
    for (std::vector<char*>::iterator it = buff_.begin(); it != buff_.end(); ++it) {
        free(*it);
    }
}

    
