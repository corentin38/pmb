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
# date	  :     12-02-2016
#
# Script shell 

LIB_REP=build-pmb-common/
GUI_REP=build-pmb-gui/

if [ -d $LIB_REP ]
then
    rm -rf $LIB_REP
fi

if [ -d $GUI_REP ]
then
    rm -rf $GUI_REP
fi
