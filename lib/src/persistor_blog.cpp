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

basics::Persistor_blog::Persistor_blog()
{
}

std::string nv(rapidxml::xml_node<> *parent, std::string name) 
{
    return parent->first_node(name.c_str())->value();
}

std::string av(rapidxml::xml_node<> *parent, std::string name) 
{
    return parent->first_attribute(name.c_str())->value();
}

std::map<std::string, std::string> nvs(rapidxml::xml_node<> *parent, std::string name) 
{
    std::map<std::string, std::string> key_val;
    rapidxml::xml_node<> *item;
    for (item = parent->first_node(name.c_str())->first_node();
         item;
         item = item->next_sibling()) {
        key_val[ item->first_attribute()->value() ] = item->value();
    }
    return key_val;
}

basics::Persistable_blog basics::Persistor_blog::read_blog(bfs::path content_storage_file)
{
    // Parsing content from file
    rapidxml::xml_document<> content;
    rapidxml::file<> content_file(content_storage_file.string().c_str());

    // Retreiving root node
    content.parse<0>(content_file.data());
    rapidxml::xml_node<> *blog_root = content.first_node("blog");

    // Retreiving config
    rapidxml::xml_node<> *conf = blog_root->first_node("config");
    basics::Configuration_blog config(nv(conf, "meta-desc"),
                                      nv(conf, "meta-author"),
                                      nv(conf, "meta-title"),
                                      nv(conf, "meta-conf-bootstrap"),
                                      nv(conf, "meta-conf-css"),
                                      nvs(conf, "nav-items"),
                                      nv(conf, "title"),
                                      nv(conf, "subtitle"),
                                      nv(conf, "about"),
                                      av(conf, "about_headline"),
                                      nvs(conf, "links"),
                                      av(conf, "links"),
                                      nv(conf, "philosophy"),
                                      nv(conf, "back-to-top"),
                                      std::stoi(nv(conf, "post-per-page")));
    

    // Iterating over "post" nodes
    rapidxml::xml_node<> *post_node = blog_root->first_node("posts");
    std::vector<basics::Post> posts;    
    rapidxml::xml_node<> *post;
    for (post = post_node->first_node("post"); post; post = post->next_sibling("post")) {
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

    basics::Persistable_blog blog_ptr(
        posts,
        config);    
    
    return blog_ptr;
    
//    std::unique_ptr<basics::Persistable_blog> blog_ptr(
//        new basics::Persistable_blog(
//            posts,
//            config)
//        );    
//    
//    return std::move(blog_ptr);
}

void basics::Persistor_blog::wn(rapidxml::xml_node<> *parent,
                                std::string name,
                                std::string value,
                                std::string attr_name,
                                std::string attr_value)
{
    rapidxml::xml_node<> *new_node = parent->document()->allocate_node(rapidxml::node_element, name, value);

    if (attr_name != "") {
        rapidxml::xml_attribute<> *new_attr = parent->document()->allocate_attribute(attr_name, attr_value);
        new_node->append_attribute(new_attr);
    }
    
    
    parent->append_node(new_node);
}

void basics::Persistor_blog::wns(rapidxml::xml_node<> *parent,
                                 std::string map_name,
                                 std::string key_name,
                                 std::string val_name,
                                 std::map<std::string, std::string> key_val) 
{
    rapidxml::xml_node<> *new_map = parent->document()->allocate_node(rapidxml::node_element, map_name);
    parent->append_node(new_map);
    
    for (std::map<std::string, std::string>::iterator it = key_val.begin(); it != key_val.end(); ++it) {
        rapidxml::xml_node<> *val = parent->document()->allocate_node(rapidxml::node_element, val_name, it->second());
        rapidxml::xml_attribute<> *key = parent->document()->allocate_attribute(key_name, it->first());
        val->append_attribute(key);
        new_map->append_node(val);
    }
}        

void basics::Persistor_blog::write_blog(bfs::path content_storage_file, basics::Persistable_blog blog) 
{
    // Getting containers
    std::vector<basics::Post> posts = blog.posts();
    basics::Configuration_blog config = blog.config();

    // Declaration
    rapidxml::xml_document<> content;
    rapidxml::xml_node<> *decl = content.allocate_node(rapidxml::node_declaration);
    decl->append_attribute(content.allocate_attribute("version", "1.0"));
    decl->append_attribute(content.allocate_attribute("encoding", "utf-8"));
    content.append_node(decl);
 
    // Blog root <blog>
    rapidxml::xml_node<> *blog_root = content.allocate_node(rapidxml::node_element, "blog");
    content.append_node(blog_root);

    // Configuration <config>
    rapidxml::xml_node<> *conf = content.allocate_node(rapidxml::node_element, "config");
    content.append_node(conf);
    wn(conf, "meta-desc", config.meta_desc_);
    wn(conf, "meta-author", config.meta_author_);
    wn(conf, "meta-title", config.meta_title_);
    wn(conf, "meta-conf-bootstrap", config.bootstrap_);
    wn(conf, "meta-conf-css", config.css_);
    wns(conf, "nav-items", "href", "item", config.menu_)
    wn(conf, "title", config.title_);
    wn(conf, "subtitle", config.subtitle_);
    wn(conf, "about", config.about_, "line", config.about_deadline_);
    wns(conf, "links", "href", "item", config.links_, "line", config.links_headline_);
    wn(conf, "philosophy", config.philosophy_);
    wn(conf, "backtotop", config.back_to_top_);
    wn(conf, "post-per-page", std::to_string(config.post_per_page_));
    
    // Post root <post prev="#" next="#">
    rapidxml::xml_node<> *post_node = content.allocate_node(rapidxml::node_element, "posts");
    rapidxml::xml_attribute<> *prev_attr = content.allocate_attribute("prev", "#");
    post_node->append_attribute(prev_attr);
    rapidxml::xml_attribute<> *next_attr = content.allocate_attribute("next", "#");
    post_node->append_attribute(next_attr);
    blog_root->append_node(post_node);

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
        post_node->append_node(another_post);
    }
    
    std::string content_string;
    rapidxml::print(std::back_inserter(content_string), content);
    
    std::ofstream content_output_stream(content_storage_file.string());
    content_output_stream << content_string;
    content_output_stream.close();
}

