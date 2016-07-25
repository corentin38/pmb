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

#include <blog/ssh_moulinator.hpp>
#include <gen/script_constants.hpp>

#include <iostream>
#include <stdexcept>

basics::Ssh_moulinator::Ssh_moulinator()
{
   std::cout << "Passage dans le constructeur de Ssh_moulinator !\n";
}

bool basics::Ssh_moulinator::is_synchronized(std::string& address, std::string& remote_path, std::string& local_path)
{
   std::string cmd = getSyncScript() + " " + address + " " + remote_path + " " + local_path;
   int ret = system(cmd.c_str());

   if (ret == 0) return true;
   if (ret == 1) return false;

   throw new std::runtime_error("Unknown error from the sync script, see logs");
}

void basics::Ssh_moulinator::submit(std::string& address, std::string& remote_path, std::string& local_path)
{
   std::string cmd = getSubmitScript() + " " + address + " " + remote_path + " " + local_path;
   int ret = system(cmd.c_str());

   if (ret != 0) {
      throw new std::runtime_error("Unknown error from the sync script, see logs");
   }
}
