function format = set_format( number_format, format_id )
	
	if (nargin < 2)
		format_id = 1;
	end
	
	if ( format_id == 1 )
		format = ["\\begin{bmatrix}^\\end{bmatrix}^&^\\\\^"];
	elseif (format_id == 2 )
		format = ["[^]^\t^\n^"];
	end
	
	if (nargin < 1)
		number_format = "%.3f";
	end
	format = [format number_format];

end
