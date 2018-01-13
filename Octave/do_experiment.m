function ok = do_experiment( exp_name, p_dir, s_dir, e_dir, nb_processors, c_dir, graph_mode )
%%function ok = do_experiment( exp_name, p_dir, s_dir, e_dir, nb_processors, c_dir, graph_mode )
% exp_name : nom de l'expérience
% p_dir : rep. des paramètres
% s_dir : rep. de sauvegarde des résultats
% e_dir : rep. des executables
% nb_processors : nb. de processeurs
% c_dir : rep. du cache
% graph_mode : 1 tracé des graphiques, 0 sinon


if (nargin < 1 )
	ok = 0;
	return;
end
addpath('functions');
if ( nargin < 2 )
	p_dir = '../Parametres';
end

if ( nargin < 3)
	s_dir = '../Resultats';
end

if ( nargin < 4 )
	e_dir = '../Executables';
end

if ( nargin < 5 )
	nb_processors = 0;
end
	
if ( nargin < 6 )
	c_dir = '/tmp';
end

if ( nargin < 7 )
	graph_mode = 1;
end

[titles, nb_samples, y_log_scale, S_y, S_x, S_X_s, S_observation_MSEs, S_prediction_MSEs, S_filtering_MSEs, S_smoothing_MSEs,S_mean_observation_MSEs, S_mean_prediction_MSEs, S_mean_filtering_MSEs, S_mean_smoothing_MSEs, S_likelihood,mean_t0_EM, mean_Q0_EM, mean_F_EM, mean_Q_EM] = experience(exp_name, e_dir, p_dir, s_dir, c_dir, nb_processors);


save_estimation([s_dir '/' exp_name], titles, nb_samples, y_log_scale, S_y, S_x, S_X_s, S_observation_MSEs, S_prediction_MSEs, S_filtering_MSEs, S_smoothing_MSEs,S_mean_observation_MSEs, S_mean_prediction_MSEs, S_mean_filtering_MSEs, S_mean_smoothing_MSEs, S_likelihood,mean_t0_EM, mean_Q0_EM, mean_F_EM, mean_Q_EM);

if ( graph_mode )
	generate_curve([s_dir '/' exp_name], titles, nb_samples, y_log_scale, S_y, S_x, S_X_s, S_observation_MSEs, S_prediction_MSEs, S_filtering_MSEs, S_smoothing_MSEs, S_mean_observation_MSEs, S_mean_prediction_MSEs, S_mean_filtering_MSEs, S_mean_smoothing_MSEs, S_likelihood);

end
ok = 1;
rmpath('functions');
end
