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
#include <blog/post.hpp>
#include <boost/filesystem.hpp>

namespace basics {

namespace bfs = boost::filesystem;

class Persistor_blog {
   
public:
    Persistor_blog(bfs::path);

    std::vector<basics::Post> read_posts();
    void write_posts(std::vector<basics::Post>);

private:
    bfs::path content_storage_file_;
    
};

} // namespace

#endif
