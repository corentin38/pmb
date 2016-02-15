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
 * @file blog_local.cpp
 */

#include "blog/blog_local.hpp"

#include <iostream>
#include <stdexcept>
#include <sstream>

basics::Blog_local::Blog_local(
    bfs::path blog_instance_folder, 
    bfs::path content_file, 
    bfs::path archive_folder,
    bfs::path resources_folder,
    bfs::path template_file,
    std::vector<basics::Post> posts,
    basics::Configuration_blog config)
    : Interface_blog(), 
      post_index_(),
      configuration_(config),
      blog_instance_folder_(blog_instance_folder), 
      content_file_(content_file), 
      archive_folder_(archive_folder),
      resources_folder_(resources_folder),
      template_file_(template_file)
{    
    std::vector<basics::Post>::iterator it(posts.begin()), end(posts.end());
    for (; it != end; ++it) {
        post_index_[ it->get_timestamp_str() ] = *it;
    }
}

basics::Blog_local::~Blog_local()
{
}

std::vector<basics::Post> basics::Blog_local::get_posts()
{
    return map_values(post_index_);
}

std::vector<std::string> basics::Blog_local::get_post_ids()
{
    return map_keys(post_index_);
}

std::string basics::Blog_local::get_post_content(std::string timestamp) 
{
    return get_post(timestamp).get_life();
}

basics::Post basics::Blog_local::get_post(std::string& timestamp) 
{
    std::map<std::string, basics::Post>::iterator exists = post_index_.find(timestamp);
    if (exists != post_index_.end()) return exists->second;

    std::stringstream err;
    err << "Pas de post avec un id = " << timestamp;
    throw std::runtime_error(err.str());
}

void basics::Blog_local::add_post(std::string title, std::string author, std::string life) 
{
    basics::Post another_post(title, author, life);
    post_index_[ another_post.get_timestamp_str() ] = another_post;    
}

void basics::Blog_local::edit_post(std::string& post_id,
                                   std::string& title,
                                   std::string& author,
                                   std::string& life)
{
    basics::Post update = get_post(post_id);
    update.set_title(title);
    update.set_author(author);
    update.set_life(life);
    update.add_edition();
    
    post_index_[post_id] = update;
}

void basics::Blog_local::remove_post(std::string& post_id)
{
    post_index_.erase(post_id);
}

template<class U, class T> 
std::vector<T> basics::Blog_local::map_values( const std::map<U, T> &input_map )
{
    std::vector<T> values;

    typename std::map<U, T>::const_iterator it(input_map.begin()), end(input_map.end());
    for (; it != end; ++it) {
        values.push_back(it->second);
    }

    return values;
}

template<class U, class T> 
std::vector<U> basics::Blog_local::map_keys( const std::map<U, T> &input_map )
{
    std::vector<U> keys;

    typename std::map<U, T>::const_iterator it(input_map.begin()), end(input_map.end());
    for (; it != end; ++it) {
        keys.push_back(it->first);
    }

    return keys;
}

