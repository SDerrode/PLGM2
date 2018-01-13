%Nombre d'échantillons
%nb_samples=[50,100,200,500,1000,2000,5000,10000];
nb_samples=[50,100,200,500,1000,2000,5000,10000];

%Nombre d'expériences
nb_exp = 1000;

%Script de simulation
simu_file = 'simulation.m';

%Fichier d'inialisation des filtres
params={'PK1.m','PK2.m','PK3.m','simu.m'};

%Nom des filtres
titles={'FKCL','FKCE','FKC contraint','FKCO'};

%Sauvegarde des courbes 
s_curve = 100;

s_likelihood = 1000;
%Log scale
y_log_scale = 0;

complexity = [100,100,100,1];
