
%Nombre d'échantillons
%nb_samples=[50,60,70,80,90,100,150,200,225,250,275,300,350,400,500,550,600,650,700,800,1000,2000,5000,10000];
nb_samples=[50,100,500];

%Nombre d'expériences
nb_exp = 10;

%Script de simulation
simu_file = 'simulation.m';

%Fichier d'inialisation des filtres
params={'K1.m','K1bis.m','K2.m','K3.m','PK1.m','PK2.m','PK3.m'};

%Nom des filtres
titles={'KE','K contraint', 'KAE', 'KA contraint', 'KCE','KCAE','KCA contraint'};

%Amplitude
A = 1;

%Phasis
phi = 0;

%frequency
freq = 10;

%Bruit
Qyy= 0.1;
