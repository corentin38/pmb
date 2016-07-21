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
 * @file ssh_moulinator.hpp
 */

#ifndef SSH_MOULINATOR_HPP
#define SSH_MOULINATOR_HPP

#include <blog/persistable_blog.hpp>

namespace basics {

class Ssh_moulinator {

public:
   Ssh_moulinator();

   bool is_synchronized(basics::Persistable_blog&, std::string&);
   void submit(basics::Persistable_blog&, std::string&);

};

} // namespace

#endif
