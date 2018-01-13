function save_estimation(save_folder, titles, nb_samples, y_log_scale, S_y, S_x, S_X_s, S_observation_MSEs, S_prediction_MSEs, S_filtering_MSEs, S_smoothing_MSEs,S_mean_observation_MSEs, S_mean_prediction_MSEs, S_mean_filtering_MSEs, S_mean_smoothing_MSEs, S_likelihood,mean_t0_EM, mean_Q0_EM, mean_F_EM, mean_Q_EM)
	nb_filters = length(titles);
	save([save_folder '/data.txt']);
	for n = 1:length(nb_samples)
		%Sauvegarde des données 
		if ( n == 1 )
			opt = 'w';
		else
			opt = 'a+';
		end
		mean_t0 = cell2mat( mean_t0_EM(n) );
		mean_Q0 = cell2mat( mean_Q0_EM(n) );
		mean_F = cell2mat( mean_F_EM(n) );
		mean_Q = cell2mat( mean_Q_EM(n) );
		
		%t0
		f = fopen( [ save_folder '/mean_t0.txt'], opt);
		fprintf(f, 'Nb_samples=%d\n', nb_samples(n));
		for i = 1:nb_filters
			fprintf(f, '%s:\n', cell2mat(titles(i)) );
			fdisp(f, cell2mat(mean_t0(i)) );
			fprintf(f, '\n' );
		end
		fclose(f); 
		
		%Q
		f = fopen( [ save_folder '/mean_Q0.txt'], opt);
		fprintf(f, 'Nb_samples=%d\n', nb_samples(n));
		for i = 1:nb_filters
			fprintf(f, '%s:\n', cell2mat(titles(i)) );
			fdisp(f, cell2mat(mean_Q0(i)) );
			fprintf(f, '\n' );
		end
		fclose(f); 
		
		%F
		f = fopen( [ save_folder '/mean_F.txt'], opt);
		fprintf(f, 'Nb_samples=%d\n', nb_samples(n));
		for i = 1:nb_filters
			fprintf(f, '%s:\n', cell2mat(titles(i)) );
			fdisp(f, cell2mat(mean_F(i)) );
			fprintf(f, '\n' );
		end
		fclose(f); 

		%Q
		f = fopen( [ save_folder '/mean_Q.txt'], opt);
		fprintf(f, 'Nb_samples=%d\n', nb_samples(n));
		for i = 1:nb_filters
			fprintf(f, '%s:\n', cell2mat(titles(i)) );
			fdisp(f, cell2mat(mean_Q(i)) );
			fprintf(f, '\n' );
		end
		fclose(f); 

	end
end
