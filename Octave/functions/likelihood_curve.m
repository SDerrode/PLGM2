figure(curve_id);
curve_id = curve_id + 1;
L = cell2mat( S_likelihood(n) );
% Génération de la courbe de vraisemblance
max_s = 1;
for j = 1 : nb_filters
        l = cell2mat(L(j));
s = length(l);
max_s = max(s, max_s);
end
% Vraisemblance
hold off;
for j = 1 : nb_filters
        l = cell2mat(L(j));
s = length(l);
plot( 0: (s - 1), l, sprintf('%d;%s;', mod(j + 2, 7), cell2mat(titles(j))));
hold on;
if ( s < max_s )
	plot( (s - 1): (max_s - 1), l(s) * ones(max_s - s + 1, 1), sprintf('%d', mod(j + 2, 7) ) );
end
end
title('likelihood');
axis([0, (max_s - 1)]);
print('dpng', [ save_folder sprintf('/likelihood_N=%d.png', nb_samples(n))] );
%print('dfig', [ save_folder sprintf('/likelihood_N=%d.fig',nb_samples(n))] );

