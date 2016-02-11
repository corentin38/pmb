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
 * @file configuration_blog.cpp
 */

#include "blog/configuration_blog.hpp"

basics::Configuration_blog::Configuration_blog(std::string meta_desc,
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
                                               std::string links_headline,
                                               std::string philosophy,
                                               std::string back_to_top,
                                               int post_per_page) :
    meta_desc_(meta_desc),
    meta_author_(meta_author),
    meta_title_(meta_title),
    bootstrap_(bootstrap),
    css_(css),
    menu_(menu),
    title_(title),
    subtitle_(subtitle),
    about_(about),
    about_headline_(about_headline),
    links_(links),
    links_headline_(links_headline),
    philosophy_(philosophy),
    back_to_top_(back_to_top),
    post_per_page_(post_per_page) 
{
}
