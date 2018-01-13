clear all;

nb_threads = 3;

e_dir = '../Executables';
c_dir = '../Cache';
graph_mode = 1;
% s_dir = '../Resultats/KCE'; p_dir = '../Parametres/KCE'; exp_name = 'exp1';
% s_dir = '../Resultats/KCC'; p_dir = '../Parametres/KCC'; exp_name = 'exp1';
% s_dir = '../Resultats/KCD'; p_dir = '../Parametres/KCD'; exp_name = 'exp3';
s_dir = '../Resultats/TAIMA15'; p_dir = '../Parametres/TAIMA15'; exp_name = 'exp1';
do_experiment( exp_name, p_dir, s_dir, e_dir, nb_threads, c_dir, graph_mode );
