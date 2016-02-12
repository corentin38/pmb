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
INSTALL_REP=${HOME}/.local

# Config Directories
echo "=================================================="
echo "Configuring directories ..."
echo "=================================================="

if [ -d $LIB_REP ]
then
    rm -rf $LIB_REP
fi

if [ -d $GUI_REP ]
then
    rm -rf $GUI_REP
fi

mkdir $LIB_REP
mkdir $GUI_REP

# Generating makefile for pmb-common
echo "=================================================="
echo "Generating makefile for pmb-common .."
echo "=================================================="
cd $LIB_REP
cmake -DCMAKE_INSTALL_PREFIX=${HOME}/.local ../pmb-common/
cd ..

# Build lib and install
echo "=================================================="
echo "Building library pmb-common in ${INSTALL_REP} ..."
echo "=================================================="

cd $LIB_REP
make && make install
cd ..

# Generating makefile for pmb-gui
echo "=================================================="
echo "Generating makefile for pmb-gui ..."
echo "=================================================="
cd $GUI_REP
cmake ../pmb-gui
cd ..

# Build gui
echo "=================================================="
echo "Building pmb-gui ..."
echo "=================================================="

cd $GUI_REP
make
cd ..

# Move executable to root dir
mv $GUI_REP/pmb-gui pmb-launch
