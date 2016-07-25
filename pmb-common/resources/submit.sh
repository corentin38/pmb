# !/bin/sh
#
# ENSICAEN
# 6 Boulevard Maréchal Juin
# F-14050 Caen Cedex
#
# Ce fichier est l'oeuvre d'élèves de l'ENSI de Caen. Il ne peut être
# reproduit, utilisé ou modifié sans l'avis express de ses auteurs.
#
# author  :	Corentin MARCIAU	<corentin.marciau@ecole.ensicaen.fr>
# date	  :     23-07-2016
#
# Script shell
#
# Pour que ça marche, il faut d'abord enregistrer son biclef
# sur le server à l'aide de :
#
#   $ ssh-copy-id corentin@marciau.fr
#

if [ $# -ne 3 ]
then
    echo "wrong number of argument"
    exit 12
fi

BLOG_HOST=$1
BLOG_PATH_ON_HOST=$2
BLOG_PATH_LOCAL=$3

RESOURCES_FILENAME=resources

echo "Host: $BLOG_HOST"
echo "Path on server: $BLOG_PATH_ON_HOST"
echo "Blog path: $BLOG_PATH_LOCAL"

# Removing previous version
ssh $BLOG_HOST rm -f $BLOG_PATH_ON_HOST/*.html
ssh $BLOG_HOST rm -rf $BLOG_PATH_ON_HOST/$RESOURCES_FILENAME

# Copying pages
for page in $(ls $BLOG_PATH_LOCAL/*.html)
do
    scp $page $BLOG_HOST:$BLOG_PATH_ON_HOST/
done

# Coprying resource folder
RESOURCE_LOCAL=$BLOG_PATH_LOCAL/$RESOURCES_FILENAME
RESOURCE_HOST=$BLOG_PATH_ON_HOST/$RESOURCES_FILENAME
scp -r $RESOURCE_LOCAL $BLOG_HOST:$RESOURCE_HOST
