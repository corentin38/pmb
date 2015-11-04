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
 * @file blog.cpp
 */

#include "blog/blog.hpp"

#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <libxml/tree.h>

#include <iostream>

basics::Blog::Blog(std::string content_path) :
   content_path_(content_path)
{
   std::cout << "Passage dans le constructeur de Blog !\n";
}

int basics::Blog::add_post(std::string title, std::string author, std::string life) 
{
   return 42;
}
