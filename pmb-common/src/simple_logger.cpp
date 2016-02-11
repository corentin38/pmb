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
 * @file simple_logger.cpp
 */

#include "utils/simple_logger.hpp"

namespace logging = boost::log;
namespace src = boost::log::sources;
namespace sinks = boost::log::sinks;
namespace keywords = boost::log::keywords;
namespace expr = boost::log::expressions;

using namespace logging::trivial;

basics::Simple_logger::Simple_logger(int log_level, std::string config_folder_path)
    : log_level_(log_level), config_folder_path_(config_folder_path), logger_(src::severity_logger_mt< severity_level >())
{
//    std::cout << log_level << " " << config_folder_path << std::endl;

    logging::core::get()->set_filter(
        severity >= log_level_); //logging::trivial::info);

    if (!config_folder_path.empty()) {
        init_file_logger();
    }
}

void basics::Simple_logger::init_file_logger() 
{
   logging::add_file_log
       (
            keywords::file_name = config_folder_path_ + "log/pmb_%N.log",
            keywords::rotation_size = 5 * 1024 * 1024,
            keywords::time_based_rotation = sinks::file::rotation_at_time_point(0, 0, 0),
            keywords::format = 
            (
                expr::stream
                << expr::format_date_time< boost::posix_time::ptime >("TimeStamp", "[%Y-%m-%d %H:%M:%S.%f]")
                << " [" << expr::attr< logging::attributes::current_thread_id::value_type >("ThreadID") << "]"
                << " [" << severity << "]"
                << " - " << expr::smessage));

    logging::add_common_attributes();
}


void basics::Simple_logger::info(std::string msg) 
{
    logging::record rec = logger_.open_record(keywords::severity = logging::trivial::info);
    if (rec)
    {
        logging::record_ostream strm(rec);
        strm << msg;
        strm.flush();
        logger_.push_record(boost::move(rec));
    }
}

void basics::Simple_logger::warn(std::string msg) 
{
    logging::record rec = logger_.open_record(keywords::severity = logging::trivial::warning);
    if (rec)
    {
        logging::record_ostream strm(rec);
        strm << msg;
        strm.flush();
        logger_.push_record(boost::move(rec));
    }
}

void basics::Simple_logger::error(std::string msg) 
{
    logging::record rec = logger_.open_record(keywords::severity = logging::trivial::error);
    if (rec)
    {
        logging::record_ostream strm(rec);
        strm << msg;
        strm.flush();
        logger_.push_record(boost::move(rec));
    }
}
