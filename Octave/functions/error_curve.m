observation_MSEs = cell2mat(S_observation_MSEs(n));
prediction_MSEs = cell2mat(S_prediction_MSEs(n));
filtering_MSEs = cell2mat(S_filtering_MSEs(n));
smoothing_MSEs = cell2mat(S_smoothing_MSEs(n));

tabcolor = ['g', 'b', 'm', 'c'];

for j = 1 : size_d
        figure(curve_id);
curve_id = curve_id + 1;
hold off;
plot_error_signal(0: (nb_samples(n) - 1), observation_MSEs(:, j), '0;Observations (y);');
hold on;
for i = 1 : nb_filters
        plot_error_signal( 0 : nb_samples(n), prediction_MSEs( :, j, i), sprintf('%c;%s;', tabcolor(mod(i - 1, length(tabcolor)) + 1), cell2mat(titles(i))));
end
axis([0, (nb_samples(n))]);
if ( y_log_scale == 1 )
	grid();
end
title( sprintf('Chanel %d', j) );
print('dpng', [ save_folder '/' sprintf('MSE-Prediction-N=%d_Chanel=%d.png', nb_samples(n), j) ] );
% print('dfig', [ save_folder '/' sprintf('MSE-Prediction-N=%d_Chanel=%d.fig', nb_samples(n), j) ] );
end
for j = size_d + 1 : size_x
        figure(curve_id);
curve_id = curve_id + 1;
hold off;
for i = 1 : nb_filters
        plot_error_signal( 0 : nb_samples(n), prediction_MSEs( :, j, i), sprintf('%c;%s;', tabcolor(mod(i - 1, length(tabcolor)) + 1), cell2mat(titles(i))));
hold on;
end
axis([0, (nb_samples(n))]);
if ( y_log_scale == 1 )
	grid();
end
title( sprintf('Chanel %d', j) );
print('dpng', [ save_folder '/' sprintf('MSE-Prediction-N=%d_Chanel=%d.png', nb_samples(n), j) ] );
% print('dfig', [ save_folder '/' sprintf('MSE-Prediction-N=%d_Chanel=%d.fig', nb_samples(n), j) ] );
end
for j = 1 : size_d
        figure(curve_id);
curve_id = curve_id + 1;
hold off;
plot_error_signal(0: (nb_samples(n) - 1), observation_MSEs(:, j), '0;Observations (y);');
hold on;
for i = 1 : nb_filters
        plot_error_signal( 0 : (nb_samples(n) - 1), filtering_MSEs( :, j, i), sprintf('%c;%s;', tabcolor(mod(i - 1, length(tabcolor)) + 1), cell2mat(titles(i))));
end
axis([0, (nb_samples(n))]);
if ( y_log_scale == 1 )
	grid();
end
title( sprintf('Chanel %d', j) );
print('dpng', [ save_folder '/' sprintf('MSE-Filtering-N=%d_Chanel=%d.png', nb_samples(n), j) ] );
% print('dfig', [ save_folder '/' sprintf('MSE-Filtering-N=%d_Chanel=%d.fig', nb_samples(n), j) ] );
end
for j = size_d + 1 : size_x
        figure(curve_id);
curve_id = curve_id + 1;
hold off;
for i = 1 : nb_filters
        plot_error_signal( 0 : (nb_samples(n) - 1), filtering_MSEs( :, j, i), sprintf('%c;%s;', tabcolor(mod(i - 1, length(tabcolor)) + 1), cell2mat(titles(i))));
hold on;
end
axis([0, (nb_samples(n))]);
if ( y_log_scale == 1 )
	grid();
end
title( sprintf('Chanel %d', j) );
print('dpng', [ save_folder '/' sprintf('MSE-Filtering-N=%d_Chanel=%d.png', nb_samples(n), j) ] );
% print('dfig', [ save_folder '/' sprintf('MSE-Filtering-N=%d_Chanel=%d.fig', nb_samples(n), j) ] );
end
for j = 1 : size_d
        figure(curve_id);
curve_id = curve_id + 1;
hold off;
plot_error_signal(0: (nb_samples(n) - 1), observation_MSEs(:, j), '0;Observations (y);');
hold on;
for i = 1 : nb_filters
        plot_error_signal( 0 : nb_samples(n), smoothing_MSEs( :, j, i), sprintf('%c;%s;', tabcolor(mod(i - 1, length(tabcolor)) + 1), cell2mat(titles(i))));
end
axis([0, (nb_samples(n))]);
if ( y_log_scale == 1 )
	grid();
end
title( sprintf('Chanel %d', j) );
print('dpng', [ save_folder '/' sprintf('MSE-Smoothing-N=%d_Chanel=%d.png', nb_samples(n), i) ] );
% print('dfig', [ save_folder '/' sprintf('MSE-Smoothing-N=%d_Chanel=%d.fig', nb_samples(n), i) ] );
end
for j = size_d + 1 : size_x
        figure(curve_id);
curve_id = curve_id + 1;
hold off;
for i = 1 : nb_filters
        plot_error_signal( 0 : nb_samples(n), smoothing_MSEs( :, j, i), sprintf('%c;%s;', tabcolor(mod(i - 1, length(tabcolor)) + 1), cell2mat(titles(i))));
hold on;
end
axis([0, (nb_samples(n))]);
if ( y_log_scale == 1 )
	grid();
end
title( sprintf('Chanel %d', j) );
print('dpng', [ save_folder '/' sprintf('MSE-Smoothing-N=%d_Chanel=%d.png', nb_samples(n), j) ] );
% print('dfig', [ save_folder '/' sprintf('MSE-Smoothing-N=%d_Chanel=%d.fig', nb_samples(n), j) ] );
end
