x = cell2mat(S_x(n));
y = cell2mat(S_y(n));
X_s = cell2mat(S_X_s(n));

tabcolor = ['g', 'b', 'm', 'c'];

for j = 1 : size_x
        figure(curve_id);
curve_id = curve_id + 1;
hold off;
plot(0: (nb_samples(n)), x(:, j), '1;Etats cachés (x);');
axis([0, (nb_samples(n))]);
hold on;
for i = 1 : nb_filters
        plot( 0 : nb_samples(n), X_s( :, j, i), sprintf('%c;%s;', tabcolor(mod(i - 1, length(tabcolor)) + 1), cell2mat(titles(i))));
end
title( sprintf('Chanel %d', j) );
print('dpng', [ save_folder '/' sprintf('Estimation-N=%d_Chanel=%d.png', nb_samples(n), j) ] );
% print('dfig', [ save_folder '/' sprintf('Estimation-N=%d_Chanel=%d.fig', nb_samples(n), j) ] );
end

