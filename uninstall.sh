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

INSTALL_REP=${HOME}/.local

./clean.sh

if [ -d $INSTALL_REP/pmb ]
then
    rm -rf $INSTALL_REP/pmb
fi

if [ -d $INSTALL_REP/share/pmb ]
then
    rm -rf $INSTALL_REP/share/pmb
fi

if [ -f pmb-launch ]
then
    rm -rf pmb-launch
fi

