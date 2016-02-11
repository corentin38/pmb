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
 * @file configuration_blog.hpp
 */

#ifndef CONFIGURATION_BLOG_HPP
#define CONFIGURATION_BLOG_HPP

#include <string>
#include <map>

namespace basics {

class Configuration_blog {
   
public:
    Configuration_blog(std::string meta_desc,
                       std::string meta_author,
                       std::string meta_title,
                       std::string bootstrap,
                       std::string css,
                       std::map<std::string, std::string> menu,
                       std::string title,
                       std::string subtitle,
                       std::string about,
                       std::string about_headline,
                       std::map<std::string, std::string> links,
                       std::string links_headline_,
                       std::string philosophy,
                       std::string back_to_top,
                       int post_per_page);

    std::string meta_desc_;
    std::string meta_author_;
    std::string meta_title_;
    std::string bootstrap_;
    std::string css_;
    std::map<std::string, std::string> menu_;
    std::string title_;
    std::string subtitle_;
    std::string about_;
    std::string about_headline_;
    std::map<std::string, std::string> links_;
    std::string links_headline_;
    std::string philosophy_;
    std::string back_to_top_;
    int post_per_page_;   
   
};

} // namespace

#endif
