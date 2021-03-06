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
#include <blog/persistor_blog.hpp>
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

    // Blog Control
    bool has_blog() const;
    std::string create_blog(std::string&, std::string&, bool, bool);
    std::string open_blog(std::string&);
    void generate_blog();

    // Blog Info
    std::vector<std::string> post_id_list();
    std::vector<basics::Post> post_list();

    inline std::string blog_path()
    {
        if (has_blog()) {
            return current_blog_->get_blog_path();
        }
        return "";
    }

    // Post Control
    basics::Post add_post(std::string&, std::string&, std::string&);
    basics::Post post(std::string&);
    basics::Post edit_post(std::string&, std::string&, std::string&, std::string&);
    void remove_post(std::string&);

    // SSH
    void submit_to_server(std::string&, std::string&);
    bool check_if_synchronized(std::string&, std::string&);

    // Deprecated
    std::string create_new_blog(std::string&, std::string&, bool, bool);
    std::string get_post_content(std::string&);
    std::string add_post_to_current_blog(std::string&, std::string&, std::string&);
    bool has_current_blog() const;
    void generate_current_blog();
    std::vector<std::string> get_post_id_list();

    inline std::string get_blog_path()
    {
        return blog_path();
    }

private:
    basics::Simple_logger logger_;

    std::unique_ptr<basics::Interface_blog> current_blog_;

    basics::Persistor_blog persistor_;

    void persist_current_blog();
};

} // namespace

#endif
