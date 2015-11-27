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
 * @file persistor_blog.cpp
 */

#include <blog/persistor_blog.hpp>
#include <rapidxml/rapidxml_utils.hpp>
#include <rapidxml/rapidxml_print.hpp>

basics::Persistor_blog::Persistor_blog(bfs::path content_storage_file)
    : content_storage_file_(content_storage_file)
{
}

std::vector<basics::Post> basics::Persistor_blog::read_posts()
{
    // Parsing content from file
    rapidxml::xml_document<> content;
    rapidxml::file<> content_file(content_storage_file_.string().c_str());

    // Retreiving root node
    content.parse<0>(content_file.data());
    rapidxml::xml_node<> *post_root = content.first_node("posts");

    // Iterating over "post" nodes
    std::vector<basics::Post> posts;    
    rapidxml::xml_node<> *post;
    for (post = post_root->first_node("post"); post; post = post->next_sibling("post")) {
        // Attributes
        std::string timestamp_str = post->first_attribute("date")->value();
        std::string author = post->first_attribute("author")->value();
        
        // title child node
        rapidxml::xml_node<> *title_node = post->first_node("title");
        std::string title = title_node->value();
        
        // mylife child node
        rapidxml::xml_node<> *life_node = post->first_node("mylife");
        std::string life = life_node->value();

        // Creating a new Post object from all infos
        basics::Post another_post(title, author, life, timestamp_str);
        posts.push_back(another_post);
    }
    
    return posts;
}

void basics::Persistor_blog::write_posts(std::vector<basics::Post> posts)
{
    rapidxml::xml_document<> content;
    std::ofstream content_output_stream(content_storage_file_.string());

    // Declaration
    rapidxml::xml_node<> *decl = content.allocate_node(rapidxml::node_declaration);
    decl->append_attribute(content.allocate_attribute("version", "1.0"));
    decl->append_attribute(content.allocate_attribute("encoding", "utf-8"));
    content.append_node(decl);
 
    // Post root <post prev="#" next="#">
    rapidxml::xml_node<> *post_root = content.allocate_node(rapidxml::node_element, "posts");
    rapidxml::xml_attribute<> *prev_attr = content.allocate_attribute("prev", "#");
    post_root->append_attribute(prev_attr);
    rapidxml::xml_attribute<> *next_attr = content.allocate_attribute("next", "#");
    post_root->append_attribute(next_attr);
    content.append_node(post_root);

    for (std::vector<basics::Post>::iterator it = posts.begin(); it != posts.end(); ++it) {
        char *timestamp_str = content.allocate_string(it->get_timestamp_str().c_str());
        char *author = content.allocate_string(it->get_author().c_str());
        char *title = content.allocate_string(it->get_title().c_str());
        char *life = content.allocate_string(it->get_life().c_str());

        // Building new post node
        rapidxml::xml_node<> *another_post = content.allocate_node(rapidxml::node_element, "post");
        rapidxml::xml_attribute<> *date_attr = content.allocate_attribute("date", timestamp_str);
        another_post->append_attribute(date_attr);
        rapidxml::xml_attribute<> *author_attr = content.allocate_attribute("author", author);
        another_post->append_attribute(author_attr);
        rapidxml::xml_node<> *title_child = content.allocate_node(rapidxml::node_element, "title", title);
        another_post->append_node(title_child);
        rapidxml::xml_node<> *mylife_child = content.allocate_node(rapidxml::node_element, "mylife", life);
        another_post->append_node(mylife_child);
        
        // Adding node to post root
        post_root->append_node(another_post);
    }
    
    std::string content_string;
    rapidxml::print(std::back_inserter(content_string), content);
    
    content_output_stream << content_string;
    content_output_stream.close();
}

