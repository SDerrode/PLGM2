x = cell2mat(S_x(n));
y = cell2mat(S_y(n));
size_x = size(x)(2);
size_y = size(x)(2);
size_d = min(size(x)(2), size(y)(2) );

%Signal généré (Etats cachés + observations)
for j=1:size_d
	figure(curve_id);
	curve_id = curve_id + 1;

	hold off;
	plot(0:(nb_samples(n)-1), y(:,j),'0;Observations (y);');
	hold on;
	plot(0:(nb_samples(n)), x(:,j),'1;Etats cachés (x);');
	title( sprintf('Chanel %d', j) );
	axis([0,(nb_samples(n))]);
	print('dpng', [ save_folder '/' sprintf('Obs-HS-N=%d_Chanel=%d.png', nb_samples(n),j) ] );
	%print('dfig', [ save_folder '/' sprintf('Obs-HS-N=%d_Chanel=%d.fig', nb_samples(n),j) ] );
end

%Eventuelles observations supplémentaires
for j=(size_d+1):size_y
	figure(curve_id);
	curve_id = curve_id + 1;

	hold off;
	plot(0:(nb_samples(n)-1), y(:,j),'0;Observations (y);');
	axis([0,(nb_samples(n))]);
	title( sprintf('Chanel %d', j) );
	print('dpng', [ save_folder '/' sprintf('Obs-HS-N=%d_Chanel=%d.png', nb_samples(n),j) ] );
	%print('dfig', [ save_folder '/' sprintf('Obs-HS-N=%d_Chanel=%d.fig', nb_samples(n),j) ] );
end
%Eventuels états cachés supplémentaires
for j=(size_d+1):size_x
	figure(curve_id);
	curve_id = curve_id + 1;
	
	hold off;
	plot(0:(nb_samples(n)), x(:,j),'1;Etats cachés (x);');
	axis([0,(nb_samples(n))]);
	title( sprintf('Chanel %d', j) );
	print('dpng', [ save_folder '/' sprintf('Obs-HS-N=%d_Chanel=%d.png', nb_samples(n),j) ] );
	%print('dfig', [ save_folder '/' sprintf('Obs-HS-N=%d_Chanel=%d.fig', nb_samples(n),j) ] );
end



