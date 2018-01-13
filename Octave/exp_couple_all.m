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
nb_threads = 1;

e_dir = '../Executables';
c_dir = '../Cache';
graph_mode = 1;
s_dir = '../Resultats/KCE';
p_dir = '../Parametres/KCE';
exp_name = 'exp1';
do_experiment( exp_name, p_dir, s_dir, e_dir, nb_threads, c_dir, graph_mode );
exp_name = 'exp2';
do_experiment( exp_name, p_dir, s_dir, e_dir, nb_threads, c_dir, graph_mode );
exp_name = 'exp3';
do_experiment( exp_name, p_dir, s_dir, e_dir, nb_threads, c_dir, graph_mode );

% s_dir = '../Resultats/KCC';
% p_dir = '../Parametres/KCC';
% exp_name = 'exp1';
% do_experiment( exp_name, p_dir, s_dir, e_dir, nb_threads, c_dir, graph_mode );
% exp_name = 'exp1bis';
% do_experiment( exp_name, p_dir, s_dir, e_dir, nb_threads, c_dir, graph_mode );
% exp_name = 'exp2';
% do_experiment( exp_name, p_dir, s_dir, e_dir, nb_threads, c_dir, graph_mode );
% exp_name = 'exp3';
% do_experiment( exp_name, p_dir, s_dir, e_dir, nb_threads, c_dir, graph_mode );
% exp_name = 'exp4';
% do_experiment( exp_name, p_dir, s_dir, e_dir, nb_threads, c_dir, graph_mode );

% s_dir = '../Resultats/KCD';
% p_dir = '../Parametres/KCD';
% exp_name = 'exp1';
% do_experiment( exp_name, p_dir, s_dir, e_dir, nb_threads, c_dir, graph_mode );
% exp_name = 'exp2';
% do_experiment( exp_name, p_dir, s_dir, e_dir, nb_threads, c_dir, graph_mode );
% exp_name = 'exp3';
% do_experiment( exp_name, p_dir, s_dir, e_dir, nb_threads, c_dir, graph_mode );
% exp_name = 'exp4';
% do_experiment( exp_name, p_dir, s_dir, e_dir, nb_threads, c_dir, graph_mode );
