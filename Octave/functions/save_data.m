function save_data( x, var_name, f )
%%function save_data( x, var_name, f )
%
%%Inputs:
% x : data
% var_name : var name
% f file

	fprintf(f, '%s=[', var_name);
	for i = 1: (size(x)(1) - 1)
		for j = 1:(size(x)(2) - 1)
			fprintf(f, '%f\t', x(i, j));
		end
		fprintf(f, '%f\n', x(i, size(x)(2)));
	end

	for j = 1:(size(x)(2) - 1)
		fprintf(f, '%f\t', x(size(x)(1), j));
	end
	fprintf(f, '%f]\n', x(size(x)(1), size(x)(2)));
end

