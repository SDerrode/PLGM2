function [string] = print_time( t )
	days_1 = floor(t / 86400);
	hour_1 = mod(floor(t / 3600), 24);
	min_1 = mod(floor(t / 60), 60);
	sec_1 = mod(floor(t), 60);

	string = '';
	if ( days_1 > 0 )
		string = [ string sprintf('%d j ', days_1 )]; 
	end
	if ( hour_1 > 0  )
		string = [ string sprintf('%d h ', hour_1 )]; 
	end
	if ( min_1 > 0 )
		string = [ string sprintf('%d min ', min_1 )]; 
	end
	if ( sec_1 > 0 )
		string = [ string sprintf('%d sec ', sec_1 )]; 
	end
	
	if ( t == 0 )
		string = ['0 sec :)'];
	end
	
end

