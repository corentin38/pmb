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
 * @file generator.cpp
 */

#include <iostream>
#include <fstream>
#include <blog/generator.hpp>
#include <string>
#include <sstream>
#include <cpp-markdown/markdown.h>

basics::Generator::Generator() : buff_(), f_ptr_(NULL)
{
}

void basics::Generator::templatize_the_fucker(bfs::path template_path,
                                              bfs::path destination_path,
                                              basics::Persistable_blog blog)
{


    basics::Configuration_blog config = blog.config();
    std::vector<basics::Post> posts = blog.posts();

    std::sort(posts.begin(), posts.end());

    int post_per_page = config.post_per_page_;
    int posts_number = posts.size();

    bool has_next = true;
    int page_count = 0;

    while (has_next) {

        // Make the post subset
        std::vector<basics::Post>::iterator beg = posts.begin() + page_count * post_per_page;
        std::vector<basics::Post>::iterator end;

        if (page_count * post_per_page + post_per_page >= posts_number) {
            end = posts.end();
            has_next = false;
        } else {
            end = beg + post_per_page;
        }

        // Make the page names
        std::stringstream page_name, prev, next;
        if (page_count == 0) {
            page_name << "index.html";

            prev << "#";
            if (has_next) {
                next << "page" << 2 << ".html";
            } else {
                next << "#";
            }
        } else {
            page_name << "page" << (page_count + 1) << ".html";

            if (page_count == 1) {
                prev << "index.html";
            } else {
                prev << "page" << page_count << ".html";
            }
            if (has_next) {
                next << "page" << page_count + 2 << ".html";
            } else {
                next << "#";
            }
        }

        std::vector<basics::Post> page(beg, end);
        templatize_page(template_path, destination_path, page_name.str(), config, page, next.str(), prev.str());

        page_count++;
    }

}

void basics::Generator::templatize_page(bfs::path tpl, bfs::path destination_path, std::string pagename, basics::Configuration_blog &config, std::vector<basics::Post> &posts, std::string prev_page_link, std::string next_page_link)
{
    init(tpl);

    // Config
    set_variable("meta-desc", config.meta_desc_);
    set_variable("meta-author", config.meta_author_);
    set_variable("meta-title", config.meta_title_);
    set_variable("meta-conf-bootstrap", config.bootstrap_);
    set_variable("meta-conf-css", config.css_);

    std::map<std::string, std::string> menu = config.menu_;
    for (std::map<std::string, std::string>::iterator it = menu.begin(); it != menu.end(); ++it) {
        set_variable("nav-href", it->first);
        set_variable("nav-item", it->second);
        feed_table("nav-items");
    }

    // Find home link and set icon
    for (std::map<std::string, std::string>::iterator it = menu.begin(); it != menu.end(); ++it) {
        if (it->second.compare(config.home_link_) == 0) {
            set_variable("nav-select", " active");
        }
    }

    set_variable("title", config.title_);
    set_variable("subtitle", config.subtitle_);

    // Posts
    for (std::vector<basics::Post>::iterator it = posts.begin(); it != posts.end(); ++it) {
        set_variable("post-title", it->get_title());
        set_variable("post-date", it->get_timestamp_str());
        set_variable("post-author-link", "#");
        set_variable("post-author", it->get_author());

        markdown::Document doc;
        doc.read(it->get_life());

        std::stringstream output;
        doc.write(output);


        set_variable("post-life", output.str());
        feed_table("posts");
    }

    set_variable("prev-page-link", prev_page_link);
    set_variable("next-page-link", next_page_link);

    set_variable("about", config.about_);
    set_variable("about-line", config.about_headline_);
    set_variable("links-line", config.links_headline_);


    std::map<std::string, std::string> links = config.links_;
    for (std::map<std::string, std::string>::iterator it = links.begin(); it != links.end(); ++it) {
        set_variable("link-href", it->first);
        set_variable("link-item", it->second);
        feed_table("links");
    }

    set_variable("philosophy", config.philosophy_);
    set_variable("backtotop", config.back_to_top_);

    exec(destination_path, pagename);
    clear();
    destroy();
}


void basics::Generator::init(bfs::path template_path)
{
    f_ptr_ = NULL;
    flateSetFile(&f_ptr_, fu(template_path.string()));
}

void basics::Generator::set_variable(std::string name, std::string value)
{
    flateSetVar(f_ptr_, fu(name), fu(value));
}

void basics::Generator::feed_table(std::string name)
{
    flateDumpTableLine(f_ptr_, fu(name));
}

void basics::Generator::exec(bfs::path folder, std::string name)
{
    bfs::path res = folder / bfs::path(name);
    std::string content(flatePage(f_ptr_));
    std::ofstream page(res.string());
    page << content;
    page.close();
}



char* basics::Generator::fu(std::string in)
{
    char* another = new char [in.size() + 1];
    strcpy(another, in.c_str());
    buff_.push_back(another);
    return another;
}

void basics::Generator::clear()
{
    for (std::vector<char*>::iterator it = buff_.begin(); it != buff_.end(); ++it) {
        delete[] *it;
    }
    buff_.clear();
}

void basics::Generator::destroy()
{
    flateFreeMem(f_ptr_);
}
