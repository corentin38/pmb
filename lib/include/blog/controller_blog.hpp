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
 * @file controller_blog.hpp
 */

#ifndef CONTROLLER_BLOG_HPP
#define CONTROLLER_BLOG_HPP

#include <memory>
#include <blog/interface_blog.hpp>
#include <boost/filesystem.hpp>
#include <vector>
#include <set>

#ifndef Q_MOC_RUN
#include "utils/simple_logger.hpp"
#endif

namespace basics {

namespace bfs = boost::filesystem;

class Controller_blog {
   
public:
    Controller_blog(basics::Simple_logger);
    
    bool has_current_blog() const;
    
    void generate_current_blog();
    
    std::string create_new_blog(std::string&, std::string&, bool, bool);
    
    std::string open_blog(std::string&);
    
    std::string select_blog(std::string&);
    
    std::vector<std::string> get_blog_names();

    inline std::string get_current_blog_path() 
    {
        if (has_current_blog()) {
            return current_blog_->get_blog_path();
        }
        return "";
    }
    

private:
    basics::Simple_logger logger_;
    
    std::unique_ptr<basics::Interface_blog> current_blog_;
    std::set<bfs::path> all_blogs_;    

};

} // namespace

#endif
