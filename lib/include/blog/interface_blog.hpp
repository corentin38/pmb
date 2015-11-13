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

namespace basics {

class Interface_blog {
   
public:
    virtual ~Interface_blog() {};

    virtual void add_post(const std::string title, const std::string author, const std::string life) = 0;
    virtual void generate(const int post_per_page = 10, const std::string page_base_name = "index") = 0;
    
    virtual bool is_ready() = 0;
    
};

} // namespace

#endif
