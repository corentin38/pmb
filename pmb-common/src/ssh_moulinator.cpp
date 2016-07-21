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
 * @file ssh_moulinator.cpp
 */

#include "blog/ssh_moulinator.hpp"

#include <iostream>

basics::Ssh_moulinator::Ssh_moulinator()
{
   std::cout << "Passage dans le constructeur de Ssh_moulinator !\n";
}

bool basics::Ssh_moulinator::is_synchronized(basics::Persistable_blog& blog, std::string& address)
{
}

void basics::Ssh_moulinator::submit(basics::Persistable_blog& blog, std::string& address)
{
}
