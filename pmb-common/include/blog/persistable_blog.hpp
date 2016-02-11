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
 * @file persistable_blog.hpp
 */

#ifndef PERSISTABLE_BLOG_HPP
#define PERSISTABLE_BLOG_HPP

#include <blog/post.hpp>
#include <blog/configuration_blog.hpp>

namespace basics {

class Persistable_blog {
   
public:
    Persistable_blog(std::vector<basics::Post>, basics::Configuration_blog);

    inline std::vector<basics::Post> posts()
    {
        return posts_;
    }
    
    inline basics::Configuration_blog config() 
    {
        return config_;
    }
    
private:
    std::vector<basics::Post> posts_;
    basics::Configuration_blog config_;
};

} // namespace

#endif
