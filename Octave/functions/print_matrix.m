function str = print_matrix(mat, format, sep)
%%function str = print_matrix(mat, format, sep)
%
%% Entrées
% mat : matrice
% format : format
% sep : sep ^
	
if ( nargin < 3 )
	sep = '^';
end
if ( nargin < 2 )
	format = set_format;
end
obj = strsplit(format, sep );
if ( length(obj) > 1 )
	left_sep = cell2mat(obj(1));
	right_sep = cell2mat(obj(2));
else
	left_sep = "\\begin{bmatrix}";
	right_sep = "\\end{bmatrix}";
end
if ( length(obj) > 3 )
	col_sep = cell2mat(obj(3));
	row_sep = cell2mat(obj(4));
else
	col_sep = "&";
	row_sep = "\\\\";
end
if ( length(obj) > 4 )
	number_format = cell2mat(obj(5));
else
	number_format = "%.3f";
end

str = left_sep;
if ( nargin >= 1 )
	nb_rows = size(mat)(1);
	nb_cols = size(mat)(2);
	
	for row = 1:(nb_rows-1)
		for col = 1:(nb_cols-1)
			str = [str sprintf(number_format, mat(row, col)) col_sep];
		end
		str = [str sprintf(number_format, mat(row, nb_cols)) row_sep]; 
	end
	for col = 1:(nb_cols-1)
		str = [str sprintf(number_format, mat(nb_rows, col)) col_sep];
	end
	str = [str sprintf(number_format, mat(nb_rows, nb_cols))]; 
end
str = [str right_sep];	
end
