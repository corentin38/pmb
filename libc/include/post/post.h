/** -*- c-basic-offset: 3 -*- 
 *
 * ENSICAEN
 * 6 Boulevard Maréchal Juin 
 * F-14050 Caen Cedex
 * 
 * Ce fichier est l'oeuvre d'élèves de l'ENSI de Caen. Il ne peut être 
 * reproduit, utilisé ou modifié sans l'avis express de ses auteurs.
 * 
 */ 

/** 
 * @author Corentin MARCIAU	<corentin.marciau@ecole.ensicaen.fr>
 *
 * @version 1.0.0 / 25-03-2015
 * @todo 
 * @bug 
 */

/** 
 * @file post.h
 * @brief 
 *
 * 
 */

#ifndef POST_H
#define POST_H

#ifdef __cplusplus
extern "C" {
#endif 

#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <libxml/tree.h>
#include <libxslt/transform.h>
#include <libxslt/xsltutils.h>
   
extern const char * XSL_TIMESTAMP_FORMAT;
   
typedef xmlDocPtr BlogContent;
typedef xmlNodePtr BlogRoot;
typedef xsltStylesheetPtr BlogXsl;
typedef xmlNodePtr BlogPost;
typedef xmlDocPtr BlogHtmlPage;

typedef struct docList DocList;
struct docList {
   xmlDocPtr* docs;
   int docNr;
};

typedef struct nodeList NodeList;
struct nodeList {
   xmlNodePtr* nodes;
   int nodeNr;
};

/** 
 * Create such node :
 *
 * <post date="2015-03-16T00:00:00" author="@param author">
 *   <title>@param title</title>
 *   <mylife>@param life</mylife>
 * </post>
 *
 * @param author the author
 * @param title the post title
 * @param life the post content
 * @return xmlNodePtr
 */
xmlNodePtr createPostNode(const char* author, const char* title, const char* life);

/** 
 * Get a date time string parsable by xsl fucking t 
 *
 * @return time string with format %Y-%m-%dT%H:%M:%S
 */
const char * getXslFormatTime();

/** 
 * Returns a NodeList of post elements with most recent first
 */
NodeList* getPostsOrderByDate(xmlDocPtr doc);

/** 
 * Sorts the given NodeList by date, most recent first
 *
 * @param NodeList the posts
 */
NodeList* sortPostsByDate(NodeList *posts);

/** 
 * Returns the time difference in second betweend the "date" attributes of two posts.
 * If the dates are equals, returns 1.
 * 
 * @param xmlNodePtr the first post
 * @param xmlNodePtr the second post
 */
int compare(xmlNodePtr post1, xmlNodePtr post2);

/** 
 * Returns a table of blog pages with the correct amount of posts in each page.
 *
 * @param xmlDocPtr the initial content document
 */
DocList *splitPostsByPage(NodeList *postNodes, int postsPerPage);

/** 
 * Returns a NodeList with all the nodes found in the @param doc for the given @param xpath.
 * If @param unlink == 1 then, the nodes of the NodeList have been xmlUnlinkNode-ed.
 */
NodeList *getXpathNodes(xmlDocPtr doc, char* xpath);

/** 
 * Free the NodeList structure
 */
void freeNodeList(NodeList *nodeList);

/** 
 * Free the DocList structure
 */
void freeDocList(DocList *docList);

/** 
 * Set prev and next page links
 */
void setPagerAttributes(DocList *pages, const char* pageName);

/** 
 * Wrappers pour les trucs libxml2 utilisé dans Blog_local
 */
BlogContent loadBlogContent(const char *contentPath);
void freeBlogContent(BlogContent blogContent);
BlogRoot loadBlogRoot(BlogContent blogContent);
void freeBlogRoot(BlogRoot blogRoot);
BlogXsl loadBlogXsl(const char *xslPath);
BlogPost createPost(const char *author, const char *title, const char *life);
BlogPost addPostToRoot(BlogRoot blogRoot, BlogPost blogPost);
BlogHtmlPage runXslOnPage(BlogXsl blogXsl, DocList *pages, int pageNr);
void saveBlogHtmlPage(const char *currentPagePath, BlogHtmlPage blogPage, BlogXsl blogXsl);
int saveBlogContent(const char *contentPath, BlogContent blogContent);

#ifdef __cplusplus
}
#endif 

#endif
