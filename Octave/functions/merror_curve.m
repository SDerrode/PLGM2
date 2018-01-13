tabcolor=['g', 'b', 'm', 'c'];

%Prediction
for j=1:size_d
	figure(curve_id);
	curve_id = curve_id + 1;
	hold off;

	for i=1:nb_filters
		plot_error( nb_samples, S_mean_prediction_MSEs(:,j,i), sprintf('%c;%s;', tabcolor(mod(i-1,length(tabcolor))+1), cell2mat(titles(i))));
		hold on;
	end
	title( sprintf('Chanel %d', j) );
	axis([nb_samples(1),nb_samples(end)]);
	grid();
	print('dpng', [ save_folder '/' sprintf('MSE-Prediction-Chanel=%d.png',j) ] );
	%print('dfig', [ save_folder '/' sprintf('MSE-Prediction-Chanel=%d.fig',j) ] );
end
for j=size_d:size_x
	figure(curve_id);
	curve_id = curve_id + 1;
	hold off;
	for i=1:nb_filters
		plot_error( nb_samples, S_mean_prediction_MSEs(:,j,i), sprintf('%c;%s;', tabcolor(mod(i-1,length(tabcolor))+1), cell2mat(titles(i))));
		hold on;
	end
	axis([nb_samples(1),nb_samples(end)]);
	grid();
	title( sprintf('Chanel %d', j) );
	print('dpng', [ save_folder '/' sprintf('MSE-Prediction-Chanel=%d.png',j) ] );
	%print('dfig', [ save_folder '/' sprintf('MSE-Prediction-Chanel=%d.fig',j) ] );
end

%Filtrage
for j=1:size_d
	figure(curve_id);
	curve_id = curve_id + 1;
	hold off;
	plot_error( nb_samples, S_mean_observation_MSEs(:,j), '0;Observations (y);');
	hold on;
	for i=1:nb_filters
		plot_error( nb_samples, S_mean_filtering_MSEs(:,j,i), sprintf('%c;%s;', tabcolor(mod(i-1,length(tabcolor))+1), cell2mat(titles(i))));
	end
	title( sprintf('Chanel %d', j) );
	axis([nb_samples(1),nb_samples(end)]);
	grid();
	print('dpng', [ save_folder '/' sprintf('MSE-Filtering-Chanel=%d.png',j) ] );
	%print('dfig', [ save_folder '/' sprintf('MSE-Filtering-Chanel=%d.fig',j) ] );
end
for j=size_d:size_x
	figure(curve_id);
	curve_id = curve_id + 1;
	hold off;
	for i=1:nb_filters
		plot_error( nb_samples, S_mean_filtering_MSEs(:,j,i), sprintf('%c;%s;', tabcolor(mod(i-1,length(tabcolor))+1), cell2mat(titles(i))));
		hold on;
	end
	title( sprintf('Chanel %d', j) );
	axis([nb_samples(1),nb_samples(end)]);
	grid();
	print('dpng', [ save_folder '/' sprintf('MSE-Filtering-Chanel=%d.png',j) ] );
	%print('dfig', [ save_folder '/' sprintf('MSE-Filtering-Chanel=%d.fig',j) ] );
end

%Lissage
for j=1:size_d
	figure(curve_id);
	curve_id = curve_id + 1;
	hold off;
	plot_error( nb_samples, S_mean_observation_MSEs(:,j), '0;Observations (y);');
	hold on;
	for i=1:nb_filters
		plot_error( nb_samples, S_mean_smoothing_MSEs(:,j,i), sprintf('%c;%s;', tabcolor(mod(i-1,length(tabcolor))+1), cell2mat(titles(i))));
	end
	axis([nb_samples(1),nb_samples(end)]);
	grid();
	title( sprintf('Chanel %d', j) );
	print('dpng', [ save_folder '/' sprintf('MSE-Smoothing-Chanel=%d.png',j) ] );
	%print('dfig', [ save_folder '/' sprintf('MSE-Smoothing-Chanel=%d.fig',j) ] );
end
for j=size_d:size_x
	figure(curve_id);
	curve_id = curve_id + 1;
	hold off;
	for i=1:nb_filters
		plot_error( nb_samples, S_mean_smoothing_MSEs(:,j,i), sprintf('%c;%s;', tabcolor(mod(i-1,length(tabcolor))+1), cell2mat(titles(i))));
		hold on;
	end
	axis([nb_samples(1),nb_samples(end)]);
	grid();
	title( sprintf('Chanel %d', j) );
	print('dpng', [ save_folder '/' sprintf('MSE-Smoothing-Chanel=%d.png',j) ] );
	%print('dfig', [ save_folder '/' sprintf('MSE-Smoothing-Chanel=%d.fig',j) ] );
end

