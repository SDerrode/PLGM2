
%Nombre d'échantillons
%nb_samples=[50,100,200];
nb_samples=[50,100,150,200,250,300,350,400,450,500,650,750,1000,1250,1500,1750,2000];


%Nombre d'expériences
nb_exp = 100;


%Script de simulation
simu_file = 'simulation.m';

%Fichier d'inialisation des filtres
params={'PK1f.m','PK2.m','PK3f.m'};

%Nom des filtres
titles={'KC contraint 1','Kalman contraint','KC optimal?'};

%Amplitude
Ax = 1;

Dx = 1;

Dy = 0.001;

%Bruit
Qyy= 0.1;
