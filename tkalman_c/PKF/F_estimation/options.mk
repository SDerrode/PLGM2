#======================================================================#
#                                 Options                              #
#======================================================================#

#Nom de la bibliothèque
NAME=lib_PKF_F

#Description
DESC="Pairwise Kalman filter algorithmes"

#Auteur
AUTHOR="Valérian Némesin"

#Dépendances
#Lib. statiques
S_LIBS=../gsl ../Filter
#Lib. dynamiques
D_LIBS=gsl

#Options principales
M_OPTIONS=../../../compilation.mk
