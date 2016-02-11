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
 * @file post.hpp
 */

#ifndef POST_HPP
#define POST_HPP

#include <boost/date_time.hpp>
#include <string>
#include <iostream>

namespace basics {

namespace bdt = boost::posix_time;

class Post {
   
public:
    Post() : title_(), author_(), life_(), timestamp_() {}

    Post(std::string title, std::string author, std::string life)
        : title_(title), author_(author), life_(life), timestamp_(bdt::second_clock::local_time())
    {}

    Post(std::string title, std::string author, std::string life, std::string timestamp_str)
        : title_(title), author_(author), life_(life), timestamp_()
    {
        std::istringstream input_stream(timestamp_str);

        //DO NOT delete this pointer, the locale will do it
        bdt::time_input_facet *xsl_time_facet = new bdt::time_input_facet("%Y-%m-%dT%H:%M:%S");

        std::locale loc(input_stream.getloc(), xsl_time_facet);    
        input_stream.imbue(loc);
        input_stream >> timestamp_;
    }

    inline std::string get_title() 
    {
        return title_;
    }
   
    inline std::string get_author() 
    {
        return author_;
    }

    inline std::string get_life() 
    {
        return life_;
    }
    
    inline bdt::ptime get_timestamp() const
    {
        return timestamp_;
    }
    
    inline std::string get_timestamp_str() 
    {
        std::stringstream stream;

        //DO NOT delete this pointer, the locale will do it
        bdt::time_facet *xsl_time_facet = new bdt::time_facet("%Y-%m-%dT%H:%M:%S");

        std::locale loc(stream.getloc(), xsl_time_facet);    
        stream.imbue(loc);
        stream << timestamp_;
        return stream.str();
    }

    bool operator <(const Post &other) const 
    {
        return timestamp_ > other.get_timestamp();
    }
    
   
private:
    std::string title_;
    std::string author_;
    std::string life_;
    bdt::ptime timestamp_;
};

} // namespace

#endif
