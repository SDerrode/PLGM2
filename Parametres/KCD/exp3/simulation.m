x = sin( 2 * pi * freq ./ nb_samples(n) .* (0:(nb_samples(n))) + phi );
y = x(1:end-1) + sqrt(Qyy) * randn(size(x(1:end-1)));
tocard = fopen(s_file, 'w');
save_data( x', 'x', tocard  );
save_data( y', 'y', tocard  );
fclose(tocard);
