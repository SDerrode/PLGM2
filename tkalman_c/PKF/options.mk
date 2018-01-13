#======================================================================#
#                                 Options                              #
#======================================================================#

#Nom de la bibliothèque
NAME=lib_PKF

#Description
DESC="Pairwise Kalman filter algorithmes"

#Auteur
AUTHOR="Valérian Némesin"

#Options principales
M_OPTIONS=../../compilation.mk

#Dépendances
#Lib. statiques
#S_LIBS=./gsl ./Filter ./EM ./F_estimation ./Q_estimation
#Lib. dynamiques
D_LIBS=gsl
