close all;
clear all;
addpath('functions');

rep = "../Resultats/tracking/filter_data";

str1 = "\\begin{table}[tb]\n";
str1 = [str1 "\\centering\n"];
str1 = [str1 "\\caption{Title1}\n"];
str1 = [str1 "\\label{C5S3-Tab-1}\n"];
str1 = [str1 "\\begin{tabular}[c|c||c|c|c||c|]\n"];
str1 = [str1 "\\hline\n"];
str1 = [str1 "Vidéo & \\Q[z,z] & \\Q[r,r] & \\Qyy & EQM \\\\ \\hline\n"];
str1 = [str1 "\\hline\n"];


str2 = "\\begin{table}[tb]\n";
str2 = [str2 "\\centering\n"];
str2 = [str2 "\\caption{Title1}\n"];
str2 = [str2 "\\label{C5S3-Tab-2}\n"];
str2 = [str2 "\\begin{tabular}[c|c||c|c||c|c|c||c|]\n"];
str2 = [str2 "\\hline\n"];
str2 = [str2 "Vidéo & \\F[r,z] & \\F[r,r] & \\Q[z,z] & \\Q[r,r] & \\Qyy & EQM \\\\ \\hline\n"];
str2 = [str2 "\\hline\n"];

str3 = "\\begin{table}[tb]\n";
str3 = [str3 "\\centering\n"];
str3 = [str3 "\\caption{Title1}\n"];
str3 = [str3 "\\label{C5S3-Tab-2}\n"];
str3 = [str3 "\\begin{tabular}[c|c||c||c|c|c||c|]\n"];
str3 = [str3 "\\hline\n"];
str3 = [str3 "Vidéo & \\F[r,r] & \\Q[z,z] & \\Q[r,r] & \\Qyy & EQM \\\\ \\hline\n"];
str3 = [str3 "\\hline\n"];

list = dir(rep);
format = set_format( "%.2f" );

i = 0;
for n_class = 1:3
	for n_video = 1:5
		for n_filter = 1:3
			i = i + 1;
			class_name = list(i + 2).name(1:5);
			video_name = list(i + 2).name(1:end-6);
			file = [rep "/" list(i + 2).name(1:end)];
			f = fopen( file, "r" );
			fseek( f, 0, SEEK_END);
			s = ftell( f );
			fseek( f, 0, SEEK_SET);
			str = fscanf( f, "%c", s );
			eval( str );
			fclose(f);
			if ( n_filter == 1 )
				str1 = [str1 video_name "&\n"];
				str1 = [str1 "$" print_submatrix(Q_EM,1,1,2,2,format) "$&\n"];
				str1 = [str1 "$" print_submatrix(Q_EM,3,3,2,2,format) "$&\n"];
				str1 = [str1 "$" print_submatrix(Q_EM,5,5,2,2,format) "$&\n"];
				str1 = [str1 "$" sprintf("%.2f", EQMp) "$\\\\ \\hline \n"];
				
			elseif( n_filter == 2 )
				str2 = [str2 video_name "&\n"];
				str2 = [str2 "$" print_submatrix(F_EM,3,1,2,2,format) "$&\n"];
				str2 = [str2 "$" print_submatrix(F_EM,3,3,2,2,format) "$&\n"];
				str2 = [str2 "$" print_submatrix(Q_EM,1,1,2,2,format) "$&\n"];
				str2 = [str2 "$" print_submatrix(Q_EM,3,3,2,2,format) "$&\n"];
				str2 = [str2 "$" print_submatrix(Q_EM,5,5,2,2,format) "$&\n"];
				str2 = [str2 "$" sprintf("%.2f", EQMp) "$\\\\ \\hline \n"];
			
			else
				str3 = [str3 video_name "&\n"];
				str3 = [str3 "$" print_submatrix(F_EM,3,3,2,2,format) "$&\n"];
				str3 = [str3 "$" print_submatrix(Q_EM,1,1,2,2,format) "$&\n"];
				str3 = [str3 "$" print_submatrix(Q_EM,3,3,2,2,format) "$&\n"];
				str3 = [str3 "$" print_submatrix(Q_EM,5,5,2,2,format) "$&\n"];
				str3 = [str3 "$" sprintf("%.2f", EQMp) "$\\\\ \\hline \n"];
			end
		end
	end
	str1 = [str1 "\\hline\n"];
	str2 = [str2 "\\hline\n"];
	str3 = [str3 "\\hline\n"];

	
end
str1 = [str1 "\\end{tabular}\n\\end{table}"];
str2 = [str2 "\\end{tabular}\n\\end{table}"];
str3 = [str3 "\\end{tabular}\n\\end{table}"];

rmpath('functions');

f = fopen( [rep "/../PK0.tex"], "w");
fprintf(f, "%s", str1);
fclose(f);

f = fopen( [rep "/../PK1.tex"], "w");
fprintf(f, "%s", str2);
fclose(f);

f = fopen( [rep "/../PK2.tex"], "w");
fprintf(f, "%s", str3);
fclose(f);



