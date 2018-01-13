%Nombre d'échantillons
nb_samples=[50,100,200,500,1000,2000];

%Nombre d'expériences
nb_exp = 150;

%Script de simulation
simu_file = 'simulation.m';

%Fichier d'inialisation des filtres
params={'PK1.m','PK2.m','simu.m'};

%Nom des filtres
titles={'FKCL','FKCE','K optimal'};

%Sauvegarde des courbes 
s_curve = 100;

s_likelihood = 1000;
%Log scale
y_log_scale = 0;
