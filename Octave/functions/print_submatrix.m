function str = print_submatrix(mat, row_s, col_s, nb_rows, nb_cols, format, sep)
%%function str = print_submatrix(mat, row_s, col_s, nb_rows, nb_cols, format, sep)
%
%%Entrées
% mat : matrices
% row_s : ligne de départ
% col_s : ligne de fin
% nb_rows : nombre de lignes
% nb_cols : nombre de colonnes
% format: format
% sep : sep

if ( nargin < 7 )
	sep = '^';
end

if ( nargin < 6 )
	format = set_format;
end

str = print_matrix ( mat( row_s:(row_s + nb_rows-1), col_s:(col_s + nb_cols - 1)), format, sep );
	



end
