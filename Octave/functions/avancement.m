function [str,t2] = avancement( exp_name, nb_processed, nb_total, t_begin, p_str, t2)
	if ( nargin == 5 )
		t2 = clock;
	end

	% Nom de l'experience
	str = ['Experience : ' exp_name '\n'];
	
	%Avancement au temps t2
	x = nb_processed / nb_total;

	%dt
	dt = etime(t2, t_begin);
	
	if ( dt > 0)
		%Vitesse
		vx = x / dt;
	else
		vx = 0;
	end
	%Update de x
	x = x + etime(clock,t2) * vx;
	if ( x > 1 )
		x = 1;
	end
	%Avancement
	str = [str 'Avancement : ' sprintf('%.2f%c', 100 * x, '%') '\n'];
	
	%Barre
	d = 1.0/80;
	for i=1:80
		if (x > d * i)
			str = [str '='];
		else
			str = [str '-'];
		end
	end
	str = [str '\n'];
	
	title = [exp_name ' ' sprintf('(%.2f%c)', 100 * x, '%')];
	
	%Temps ecoule
	str = [str 'Temps ecoule : ' print_time( floor(etime(clock,t_begin)) ) '\n'];
	
	%Temps restant
	if ( vx > 0 )
	
		t = (1 - x) / vx;
		str = [str 'Temps restant : ' print_time( t ) '\n'];
		title = [title ' Restant: ' print_time( t )];
	end
	
	%Affichage
	if ( strcmp(str, p_str ) == 0 )
		ch = sprintf('clear; echo "%s"', str);
		system(ch);
		ch = sprintf('echo "%s"', title);
		system(ch);
	end
	t2 = clock();
end
