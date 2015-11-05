/** -*- c-basic-offset: 3 -*- 
 *
 * ENSICAEN
 * 6 Boulevard Maréchal Juin 
 * F-14050 Caen Cedex
 * 
 * Ce fichier est l'oeuvre d'élèves de l'ENSI de Caen. Il ne peut être 
 * reproduit, utilisé ou modifié sans l'avis express de ses auteurs.
 */ 

/** 
 * @author Corentin MARCIAU	<corentin@marciau.fr>
 *
 * @version 1.0.0 / 25-03-2015
 * @todo 
 * @bug 
 */

/** 
 * @file post.c
 * @brief 
 *
 * 
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <libxml/tree.h>

#include "post/post.h"

const char * XSL_TIMESTAMP_FORMAT = "%Y-%m-%dT%H:%M:%S";

xmlNodePtr createPostNode(const char* author, const char* title, const char* life) {
   xmlNodePtr newPost;

   // On récupère la date courante
   const char *date = getXslFormatTime();
   if (date == NULL) {
      return NULL;
   }
   
   // Création d'un nouveau post :
   if ((newPost = xmlNewNode(NULL, BAD_CAST "post")) == NULL) {
      free((char*) date);
      return NULL;
   }

   // Caler l'attribut date
   if (xmlSetProp(newPost, BAD_CAST "date", BAD_CAST date) == NULL) {
      xmlFreeNode(newPost);
      free((char*) date);
      return NULL;
   }

   // Caler l'attribut auteur
   if (xmlSetProp(newPost, BAD_CAST "author", BAD_CAST author) == NULL) {
      xmlFreeNode(newPost);
      free((char*) date);
      return NULL;
   }

   // Rajouter un fils pour le titre
   if (xmlNewTextChild(newPost, NULL, BAD_CAST "title", BAD_CAST title) == NULL) {
      xmlFreeNode(newPost);
      free((char*) date);
      return NULL;
   }

   // Rajouter un fils pour le contenu
   if (xmlNewTextChild(newPost, NULL, BAD_CAST "mylife", BAD_CAST life) == NULL) {
      xmlFreeNode(newPost);
      free((char*) date);
      return NULL;
   }

   // On retourne le xmlNodePtr qu'il ne faudra pas oublier de xmlFreeNoder ...
   free((char*) date);
   return newPost;
}

const char * getXslFormatTime() {
   time_t now_time;
   struct tm *now_time_struct;

   // XSL time format
   const char * format = XSL_TIMESTAMP_FORMAT;

   // return a fancy time string
   char *fancy_time = malloc(256 * sizeof(char));

   now_time = time(NULL);
   if (now_time == ((time_t) -1)) {
      fprintf(stderr, "Unable to get time\n");
      return NULL;
   }

   now_time_struct = localtime(&now_time);
   if (now_time_struct == NULL) {
      fprintf(stderr, "Unable convert time to struct tm\n");
      return NULL;
   }
   
   strftime(fancy_time, 256, format, now_time_struct);
   if (fancy_time == NULL) {
      fprintf(stderr, "Unable to print time\n");
      return NULL;
   }

   return fancy_time;
}

NodeList* getPostsOrderByDate(xmlDocPtr doc) {
   char *xpathPosts = "/posts/post";
   NodeList *postNodes = getXpathNodes(doc, xpathPosts, 1);
   
   if(postNodes->nodes == NULL) {
      printf("[ERROR] Impossible to get posts from xpath: %s", xpathPosts);
      return postNodes;
   }

   return sortPostsByDate(postNodes);
}

NodeList* sortPostsByDate(NodeList *posts) {
   if(posts->nodes == NULL) return posts;
   
   // Buble sort
   int swap = 1, index = posts->nodeNr - 1;
   while (index > 0 && swap == 1) {
      swap = 0;
      int j = 0;
      for (j=0; j<index; j++) {
	 if (compare(posts->nodes[j], posts->nodes[j+1]) < 0) {
	    xmlNodePtr tmp = posts->nodes[j];
	    posts->nodes[j] = posts->nodes[j+1];
	    posts->nodes[j+1] = tmp;
	    swap = 1;
	 }
      }
      index--;
   }

   return posts;
}

int compare(xmlNodePtr post1, xmlNodePtr post2) {
   // XSL time format
   const char * format = XSL_TIMESTAMP_FORMAT;

   // Fetching time string of both nodes
   xmlChar *time1str, *time2str;
   
   time1str = xmlGetProp(post1, BAD_CAST "date");
   time2str = xmlGetProp(post2, BAD_CAST "date");

   struct tm time1_struct;
   struct tm time2_struct;
   
   if (strptime(time1str, format, &time1_struct) == NULL) {
      printf("[ERROR] Impossible to parse time string from: < %s >\n", time1str);
      xmlFree(time1str);
      xmlFree(time2str);
      return 1;
   }

   if (strptime(time2str, format, &time2_struct) == NULL) {
      printf("[ERROR] Impossible to parse time string from: < %s >\n", time2str);
      xmlFree(time1str);
      xmlFree(time2str);
      return 1;
   }
   
   //   printf("Différence entre les deux dates : %d\n", ((int) difftime(mktime(&res), mktime(tmp))) / (60 * 60 *24));
   xmlFree(time1str);
   xmlFree(time2str);
   return difftime(mktime(&time1_struct), mktime(&time2_struct));
}   

DocList* splitPostsByPage(NodeList *postNodes, int postsPerPage) {
   DocList *blogPages;
   
   // Le nombre de doc, c'est la division entière du nb total de posts par
   // le nombre de posts par page souhaité + 1 pour mettre ceux qui restent.
   int docNr = postNodes->nodeNr / postsPerPage + 1;

   // Si la division tombe pile, pas besoin de prévoir une page pour les restants ...
   if (postNodes->nodeNr % postsPerPage == 0) {
      docNr--;
   }
   
   // Init docList with docNr
   blogPages = malloc(sizeof(DocList));
   blogPages->docs = malloc(docNr * sizeof(xmlDocPtr));
   blogPages->docNr = docNr;
   
   int i=0, indexInCurrentPage=0, currentPage=0;
   xmlNodePtr currentRoot;
   
   for (i=0; i<postNodes->nodeNr; i++) {
      // If starting a new page
      if (indexInCurrentPage == 0) {
         xmlDocPtr newPage = xmlNewDoc(BAD_CAST "1.0");
         currentRoot = xmlNewNode(NULL, BAD_CAST "posts");
         xmlDocSetRootElement(newPage, currentRoot);
         
         blogPages->docs[currentPage] = newPage;
      }

      xmlAddChild(currentRoot, postNodes->nodes[i]);
      indexInCurrentPage++;
      
      // If reaching the end of a page
      if (indexInCurrentPage == postsPerPage) {
         indexInCurrentPage = 0;
         currentPage++;
      }
   }

   return blogPages;
}

NodeList* getXpathNodes(xmlDocPtr doc, char* xpath, int unlink) {
   xmlXPathContextPtr ctxt;
   xmlXPathObjectPtr xpathRes;
   NodeList *nodeList;
   nodeList = malloc(sizeof(NodeList));

   // Retrieve post nodes with xpath
   xmlXPathInit();
   
   if (NULL == (ctxt = xmlXPathNewContext(doc))) {
      printf("[ERROR] Impossible to initialize XPath context\n");
      nodeList->nodes = NULL;
      return nodeList;
   }

   xpathRes = xmlXPathEvalExpression(BAD_CAST xpath, ctxt);

   if (!xpathRes || XPATH_NODESET != xpathRes->type) {
      printf("[ERROR] Bad XPath or no result : %s\n", xpath);
      nodeList->nodes = NULL;
      return nodeList;
   }

   nodeList->nodeNr = xpathRes->nodesetval->nodeNr;
   nodeList->nodes = malloc(nodeList->nodeNr * sizeof(xmlNodePtr));
   
   int i = 0;
   for (i=0; i<nodeList->nodeNr; i++) {
      xmlNodePtr current = xpathRes->nodesetval->nodeTab[i];
      nodeList->nodes[i] = current;
      if (unlink == 1) {
	 xmlUnlinkNode(current);
      }
   }

   xmlXPathFreeObject(xpathRes);
   xmlXPathFreeContext(ctxt);
   
   return nodeList;
}

void freeNodeList(NodeList *nodeList) {
   int i = 0;
   if (nodeList && nodeList->nodes) {
      for (i=0; i<nodeList->nodeNr; i++) {
         xmlFreeNode(nodeList->nodes[i]);
      }
   }
   free(nodeList->nodes);
}

void freeDocList(DocList *docList) {
   int i = 0;
   if (docList && docList->docs) {
      for (i=0; i<docList->docNr; i++) {
         xmlFreeDoc(docList->docs[i]);
      }
   }
   free(docList->docs);
}

void setPagerAttributes(DocList *pages, const char* pageName) {
   char* extension = ".html";
   char currentPageName[256];
   
   int i=0;
   for(i=0; i<pages->docNr; i++) {
      xmlNodePtr currentRoot = xmlDocGetRootElement(pages->docs[i]);

      // First page's previous link points to #
      if (i == 0) {
	 if (xmlSetProp(currentRoot, BAD_CAST "prev", BAD_CAST "#") == NULL) return;
      }

      // Last page's next link points to #
      if (i == pages->docNr - 1) {
         if (xmlSetProp(currentRoot, BAD_CAST "next", BAD_CAST "#") == NULL) return;
      }
      
      // Building prev link
      if (i != 0) {
      	 // reset current page name
         currentPageName[0] = '\0';
         
         if (i == 1) {// First page is index.html, not index0.html
            snprintf(currentPageName, sizeof currentPageName, "%s%s", pageName, extension);
         } else {
            snprintf(currentPageName, sizeof currentPageName, "%s%d%s", pageName, i - 1, extension);
         }
         
         if (xmlSetProp(currentRoot, BAD_CAST "prev", BAD_CAST currentPageName) == NULL) return;
      }
      
      // Building next link
      if (i != pages->docNr - 1) {
      	 // reset current page name
         currentPageName[0] = '\0';
         
         snprintf(currentPageName, sizeof currentPageName, "%s%d%s", pageName, i + 1, extension);
         
         if (xmlSetProp(currentRoot, BAD_CAST "next", BAD_CAST currentPageName) == NULL) return;
      }
   }

   return;
}
