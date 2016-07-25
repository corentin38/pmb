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
# date	  :     22-07-2016
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
    exit -1
fi

BLOG_HOST=$1
BLOG_PATH_ON_HOST=$2
BLOG_PATH_LOCAL=$3

echo "Host: $BLOG_HOST"
echo "Path on server: $BLOG_PATH_ON_HOST"
echo "Blog path: $BLOG_PATH_LOCAL"

echo "--------------------------"

echo "Calculating md5sum of local html files"
for page in $(ls $BLOG_PATH_LOCAL/*.html)
do
    CHECK_LOCAL=$CHECK_LOCAL$(md5sum $page | cut -d' ' -f1)
done

echo "Local blog checksum: "$CHECK_LOCAL

echo "--------------------------"

echo "Calculating md5sum of remote html files"
HTML_FILES=$(ssh $BLOG_HOST ls $BLOG_PATH_ON_HOST/*.html)
for page2 in $HTML_FILES
do
    CHECK_HOST=$CHECK_HOST$(ssh $BLOG_HOST md5sum $page2 | cut -d' ' -f1)
done

echo "Remote blog checksum: "$CHECK_HOST

echo "--------------------------"

if [ "$CHECK_HOST" != "$CHECK_LOCAL" ]
then
    echo "Local and remote hosts are NOT synchronized"
    exit 1
fi

echo "Local and remote hosts are synchronized"
exit 0
