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
 * @file persistor_blog.hpp
 */

#ifndef PERSISTOR_BLOG_HPP
#define PERSISTOR_BLOG_HPP

#include <vector>
#include <rapidxml/rapidxml.hpp>
#include <boost/filesystem.hpp>
#include <blog/persistable_blog.hpp>

namespace basics {

namespace bfs = boost::filesystem;

class Persistor_blog {
   
public:
    Persistor_blog();

    basics::Persistable_blog read_blog(bfs::path);
    void write_blog(bfs::path, basics::Persistable_blog);
private:

    /** get node value */
    std::string nv(rapidxml::xml_node<> *parent, std::string name);
    
    /** get attribute value */
    std::string av(rapidxml::xml_node<> *parent, std::string name);

    /** get node values from xml "map"
     * <mymap>
     *   <value key="this is a key">this is a value</value>
     *   ...
     * </mymap>
     * 
     * works with any name for value and key as long as there is just
     * a list of single elements with single attributes
     */
    std::map<std::string, std::string> nvs(rapidxml::xml_node<> *parent, std::string name);

    /** write node of name "name" and value "value" with optional attribute */
    void wn(rapidxml::xml_node<> *parent,
            std::string name,
            std::string value,
            std::string attr_name = "",
            std::string attr_value = "");

    /** write xml map of nodes */
    void wns(rapidxml::xml_node<> *parent,
             std::string map_name,
             std::string key_name,
             std::string val_name,
             std::map<std::string, std::string> key_val,
             std::string attr_name = "",
             std::string attr_value = "");
};

} // namespace

#endif
