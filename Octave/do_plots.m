function ok = do_plots( exp_name, s_dir )
%%function ok = do_plots( exp_name, s_dir )
% exp_name : nom de l'expérience
% s_dir : rep. de sauvegarde des résultats
	addpath('functions');
	
	load( [s_dir '/' exp_name '/data.txt'] );
	generate_curve([s_dir '/' exp_name], titles, nb_samples, y_log_scale, S_y, S_x, S_X_s, S_observation_MSEs, S_prediction_MSEs, S_filtering_MSEs, S_smoothing_MSEs, S_mean_observation_MSEs, S_mean_prediction_MSEs, S_mean_filtering_MSEs, S_mean_smoothing_MSEs, S_likelihood);

	rmpath('functions');
end
