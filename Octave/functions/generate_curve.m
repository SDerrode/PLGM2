function generate_curve(save_folder, titles, nb_samples, y_log_scale, S_y, S_x, S_X_s, S_observation_MSEs, S_prediction_MSEs, S_filtering_MSEs, S_smoothing_MSEs, S_mean_observation_MSEs, S_mean_prediction_MSEs, S_mean_filtering_MSEs, S_mean_smoothing_MSEs, S_likelihood)

curve_id = 1;
nb_filters = length(titles);
%Pointeur de fonction pour les plots
if (y_log_scale == 0 )
	plot_error_signal = @plot;
	plot_error = @semilogx;
else
	plot_error_signal = @semilogy;
	plot_error = @loglog;
end

for n = 1:length(nb_samples)
	%Graphiques des restorations
	%observations
	observation_curve
	%Restorations
	restoration_curve
	%Erreurs
	error_curve
	likelihood_curve;
end

merror_curve;

close all;


end
