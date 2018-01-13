t = (0:(nb_samples(n)))/ nb_samples(n);
x = -Ax * exp( - Dx * t );
nu = Ax / (1 + Dy * Dx );
y = nu * x(1:end-1) + (1 - nu) * exp( - Dy^(-1) * t(1:end-1) ) + sqrt(Qyy) * randn(size(x(1:end-1)));
tocard = fopen(s_file, 'w');
save_data( x', 'x', tocard  );
save_data( y', 'y', tocard  );
fclose(tocard);
if ( j == 1 )
	system( ['cp ' p_dir '/PK1.m ' p_dir '/PK1f.m' ] );
	alpha = (1 + Dy * nb_samples(n))^-1 * Dy * nb_samples(n);
	f = fopen([p_dir '/PK1f.m'], 'a+');
		fprintf(f, 'filter::F=[1\t0\n%f\t%f];\n',1-alpha, alpha);
		fprintf(f, 'EM::F_0=[1\t0\n%f\t%f];\n',1-alpha, alpha);
	fclose(f);
	system( ['cp ' p_dir '/PK3.m ' p_dir '/PK3f.m' ] );
	
	beta = (1 + nb_samples(n) / Dx)^(-1) * nb_samples(n) / Dx;
	
	f = fopen([p_dir '/PK3f.m'], 'a+');
		fprintf(f, 'filter::F=[%f\t0\n%f\t%f];\n',beta,1-alpha, alpha);
		fprintf(f, 'EM::F_0=[%f\t0\n%f\t%f];\n',beta,1-alpha, alpha);
	fclose(f);
end
