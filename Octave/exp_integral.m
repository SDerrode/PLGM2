clear all;

% Detection automatique du nombre de threads du processeur.
ch = sprintf('sysctl hw.ncpu | awk ''{print $2}'' > ../Temp/nb_processeurs.txt');
system(ch);
f = fopen('../Temp/nb_processeurs.txt','r');
nb_threads = fscanf(f,'%f');
fclose(f);
system('rm ../Temp/nb_processeurs.txt');
clear f;
% Je n'en prend qu'une partie
nb_threads = floor(nb_threads*0.5);
% ou bien on le fixe:
%nb_threads = 1;

nb_threads, pause

exp_name = 'Exp-Integral';
p_dir = '../Parametres';
s_dir = '../Resultats';
e_dir = '../Executables';
c_dir = '/tmp';
graph_mode = 1;

do_experiment( exp_name, p_dir, s_dir, e_dir, nb_threads, c_dir, graph_mode );
