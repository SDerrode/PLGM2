#======================================================================#
#                                 Options                              #
#======================================================================#

#Nom de la bibliothèque
NAME=lib_tkalman_simulation

#Description
DESC="Simulations for Pairwise Kalman filter"

#Auteur
AUTHOR="Valérian Némesin"

#Dépendances
#Lib. statiques
S_LIBS=../PKF
#Lib. dynamiques
D_LIBS=gsl

#Options principales
M_OPTIONS=../../compilation.mk
