%Nombre d'échantillons
nb_samples=[50,100,200,500,1000,2000,5000,10000];
%nb_samples=[50, 75, 100, 200, 500, 1000, 2000, 5000];
%nb_samples=[50, 75, 100];
%nb_samples=[1000, 2000, 5000];
%Nombre d'expériences
nb_exp = 1;
%Script de simulation
simu_file = 'simulation.m';

%Fichier d'initialisation des filtres
params={'PK2.m'};
%params={'PK3.m', 'PK1.m', 'PK2.m', 'simu.m'};

%Nom des filtres
%titles={'Noise unconstrained', 'Noise block-unconstrained', 'Noise block-constrained', 'FKO'};
%titles={'Bruit non-contraint', 'Bruit bloc-non-contraint', 'Bruit bloc-contraint', 'FKO'};
%titles={'Filtre f1', 'Filtre f2', 'Filtre f3', 'Filtre f4'};
titles={'Filtre f3'};

%Sauvegarde des courbes 
s_curve = 100;

s_likelihood = 1000;
%Log scale
y_log_scale = 0;

%Optionnel pour le temps
complexity=1;
