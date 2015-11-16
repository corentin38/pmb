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
 */

/**
 * @file simple_logger.hpp
 */

#ifndef SIMPLE_LOGGER_HPP
#define SIMPLE_LOGGER_HPP

// Probably that most of these includes are pointless ...
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/attributes/attribute.hpp>
#include <boost/log/attributes/current_thread_id.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/move/utility.hpp>

namespace basics {

class Simple_logger {
   
public:
    Simple_logger(int log_level, std::string config_folder_path = "");
   
    void info(std::string);
    void warn(std::string);
    void error(std::string);

private:
    int log_level_;
    std::string config_folder_path_;
    boost::log::sources::severity_logger_mt< boost::log::trivial::severity_level > logger_;
    void init_file_logger();
};

} // namespace

#endif
