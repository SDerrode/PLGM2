function [titles,nb_samples, y_log_scale, S_y, S_x, S_X_s, S_observation_MSEs, S_prediction_MSEs, S_filtering_MSEs, S_smoothing_MSEs, S_mean_observation_MSEs, S_mean_prediction_MSEs, S_mean_filtering_MSEs, S_mean_smoothing_MSEs, S_likelihood,mean_t0_EM, mean_Q0_EM, mean_F_EM, mean_Q_EM] = experience( exp_name, a_folder, p_folder, s_folder, c_folder, nb_threads )
%%function [ok] = experience( exp_name, a_folder, p_folder, s_folder, c_folder, nb_thread )
%
%%Entrees:
% exp_name: nom de l'expérience
% a_folder: dosier des exécutables
% p_folder: dossier des paramètres
% s_folder: dossier de sauvegarde
% c_folder: dossier pour les données temporaires
% nb_thread : nombre de threads
%%Sortie:
% ok : 1 si l'expérience s'est bien déroulée
%      0 sinon
%
%%Howto:
%
%Dans le dossier de configuration, créer un fichier parametres.m
%
%
complexity = 1;
t1 = clock;%Temps 0
t2 = clock;
close all;
y_log_scale = 0; %Desactivation de l'échelle log
ok = 0;
curve_id = 1;
d_integral = 0;

%Test du nombre d'arguments
if ( nargin < 1 )
	return;
end
if ( nargin < 2 )
	a_folder = '../Executables';
end
if ( nargin < 3 )
	p_folder = '../Parametres';
end
if ( nargin < 4 ) 
	s_folder = '../Resultats';
end
if ( nargin < 5 )
	c_folder = '../Tmp';
end
if ( nargin < 6 )
	nb_threads = 1;
end


%Dossier de cache
cache_folder = [c_folder '/' exp_name]; %Nom
system(['rm -rf ' cache_folder]); %Suppression
mkdir(cache_folder); %Construction

%Dossier de sauvegarde
save_folder = [s_folder '/' exp_name]; %Nom 
system(['rm -rf ' save_folder]); %Suppression
mkdir(save_folder); %Construction


%Dossier de paramètres
exp_folder =[p_folder '/' exp_name];

%Recopie des paramètres et des éxécutables
system(['cp -av ' exp_folder ' ' save_folder '/parameters $2>/dev/null']);
system(['cp -av ' exp_folder ' ' cache_folder '/parameters $2>/dev/null']);
system(['cp -av ' a_folder ' ' cache_folder '/applications $2>/dev/null']);
system(['cp -av ' 'functions' ' ' cache_folder '/functions $2>/dev/null']);
system(['cp -av ' '../Scripts' ' ' cache_folder '/scripts $2>/dev/null']);
%Chemin courant pour les applications
app_dir = [cache_folder '/applications']
p_dir = [cache_folder '/parameters']
f_dir = [cache_folder '/functions']
script_dir = [cache_folder '/scripts']
%Chemin des applications
addpath(p_dir);
addpath(f_dir);
addpath(cache_folder);

%Lecture du fichier de paramètres
parametres;

%Nb exp.
if ( length(nb_exp) < length(nb_samples) )
	nb_exp = nb_exp(1) * ones(length(nb_samples),1);
end

if ( length(complexity) < length(params) )
	complexity = ones(length(params),1);
end

%Nombre de filtres
nb_filters = length( params );

%Nombre d'échantillons total
nb_total = sum(nb_samples(:) .* nb_exp(:));
%Nombre d'échantillons traités
nb_processed = 0;

str = '';

S_y = {};
S_x = {};
S_X_s = {};
S_observation_MSEs = {};
S_prediction_MSEs = {};
S_filtering_MSEs = {};
S_smoothing_MSEs = {};
mean_t0_EM = {};
mean_Q0_EM = {}; 
mean_F_EM = {};
mean_Q_EM = {};

%Expériences
for n = 1:length(nb_samples)
	nb = floor(nb_exp(n) / nb_threads);
	reste = nb_exp(n) - nb * nb_threads;
	for i = 1:(nb+1)
		if ( i > nb) 
			q = reste;
		else
			q = nb_threads;
		end
		t2 = clock();
		%Message
		[str] = avancement( exp_name, nb_processed, nb_total, t1, str, t2);
		
		%Génération du signal
		for j = 1:q,
			s_file = [cache_folder sprintf('/simu_%d.m', j)];
			simulation;
        end
		
		%Restauration du signal (parallélisation)
		system('rm -f log.txt');
		for j = 1:nb_filters
			for k = 1:q
				s_file = [cache_folder sprintf('/simu_%d.m', k)];  %Fichier de simu
				r_file = [cache_folder sprintf('/%d_%s', k, cell2mat(params(j)))]; %Fichier de restauration
				rbis_file = [cache_folder sprintf('/bis_%d_%s', k, cell2mat(params(j)))];
				p_file = [p_dir '/' cell2mat(params(j))];
				cmd = ['(' app_dir '/restore_PKF_data.run ' p_file ' ' s_file ' ' rbis_file ' $2>>log.txt; mv ' rbis_file ' ' r_file ')&'];
				ch=sprintf('echo "%s >> log.txt"', cmd);
				system(ch);
				system(cmd);
			end

			%Test de l'existence de tous les fichiers
			f_ok = 0;
			while ( f_ok < q )
				
				[str] = avancement( exp_name, nb_processed, nb_total, t1, str, t2);
				
				for k = 1:q
					r_file = [cache_folder sprintf('/%d_%s', k, cell2mat(params(j)))];
					f = fopen( r_file, 'r+' );
					if ( f >= 0 )
						f_ok = f_ok + 1;
					
						fclose(f);
						%Récupération des données		
						r_file = [cache_folder sprintf('/%d_%s', k, cell2mat(params(j)))];
						s_file = [cache_folder sprintf('/simu_%d.m', k)];
						
						%Lecture des données
						f = fopen( s_file, 'r' );
						fseek( f, 0, SEEK_END);
						s = ftell( f );
						fseek( f, 0, SEEK_SET);
						str = fscanf( f, '%c', s );
						eval( str );

						fclose(f);
						
						f = fopen( r_file, 'r' );
						fseek( f, 0, SEEK_END);
						s = ftell( f );
						fseek( f, 0, SEEK_SET);
						str = fscanf( f, '%c', s );
						eval( str );
						fclose(f);
						
						if ( d_integral )
							x = x / nb_samples(n);
							x_p = x_p / nb_samples(n);
							x_f = x_f / nb_samples(n);
							x_s = x_s / nb_samples(n);
						end
						
						%Suppression des données du filtre
						system(['rm -f ' r_file]);
						
						%Dimensions
						%size_x = size(x)(2);
						%size_y = size(y)(2);
                        size_x = size(x,2);
						size_y = size(y,2);
						size_t = size_x + size_y;
						
						%Initialization des moments
						if ( i * j * f_ok == 1 )
							if ( d_integral )
								nb_filters_2 = nb_filters + 1;
							else
								nb_filters_2 = nb_filters;
								
							end
							
							smoothing_MSEs = zeros (nb_samples(n) + 1, size_x, nb_filters_2);
							filtering_MSEs = zeros (nb_samples(n), size_x, nb_filters_2);
							prediction_MSEs = zeros (nb_samples(n) + 1, size_x, nb_filters_2);

							X_s = zeros ( nb_samples(n) + 1, size_x, nb_filters_2 );
							X_p = zeros ( nb_samples(n) + 1, size_x, nb_filters_2 );
							X_f = zeros ( nb_samples(n), size_x, nb_filters_2 );
							
							if ( n == 1 )
								mean_smoothing_MSEs = zeros( length(nb_samples), size_x, nb_filters_2 );
								mean_filtering_MSEs = zeros( length(nb_samples), size_x, nb_filters_2 );
								mean_prediction_MSEs = zeros( length(nb_samples), size_x, nb_filters_2 );

							end
							
							
							if ( n == 1 )
								mean_observation_MSEs = zeros( length(nb_samples), size_x);							
							end
							observation_MSEs = zeros(nb_samples(n), size_x );							
							
							L = {};
							mean_F = {};
							mean_Q = {};
							mean_t0 = {};
							mean_Q0 = {};
						end

						%Comptabilité
						if ( k * i == 1 )
							X_s(:, :, j) = x_s(:, 1:size_x);
							X_p(:, :, j) = x_p(:, 1:size_x);
							X_f(:, :, j) = x_f(:, 1:size_x);
						end
						
						if ( i * f_ok == 1 )
							L(j) = likelihood  / nb_exp(n);
							mean_F(j) = F_EM / nb_exp(n); 
							mean_Q(j) = Q_EM / nb_exp(n); 
							mean_t0(j) = t_0_EM / nb_exp(n); 
							mean_Q0(j) = Q_0_EM / nb_exp(n); 
						else
							L(j) = cell2mat(L(j)) + likelihood  / nb_exp(n);
							mean_F(j) = cell2mat(mean_F(j)) + F_EM / nb_exp(n); 
							mean_Q(j) = cell2mat(mean_Q(j)) + Q_EM / nb_exp(n); 
							mean_t0(j) = cell2mat(mean_t0(j)) + t_0_EM / nb_exp(n); 
							mean_Q0(j) = cell2mat(mean_Q0(j)) + Q_0_EM / nb_exp(n);
						end
						%Erreurs
						[err, m_err] = compute_errors( x_p, x );
						mean_prediction_MSEs(n,:,j) = m_err / nb_exp(n);
						prediction_MSEs(:,:,j) = prediction_MSEs(:,:,j) + err / nb_exp(n);
						
						[err, m_err] = compute_errors( x_s, x );
						mean_smoothing_MSEs(n,:,j) = mean_smoothing_MSEs(n,:,j) + m_err / nb_exp(n);
						smoothing_MSEs(:,:,j) = smoothing_MSEs(:,:,j) + err / nb_exp(n);
						
						[err, m_err] = compute_errors( x_f, x );
						mean_filtering_MSEs(n,:,j) = mean_filtering_MSEs(n,:,j)  + m_err / nb_exp(n);
						filtering_MSEs(:,:,j) = filtering_MSEs(:,:,j) + err / nb_exp(n);
						
						
						nb_processed = nb_processed + nb_samples(n) * complexity(j) / sum(complexity);
						t2 = clock();
					end
					%usleep (1);
				end
			end
		end
		

		%Suppression des fichiers de simulation
		for j = 1:q
			s_file = [cache_folder sprintf('/simu_%d.m', j)];
	
			%Lecture du fichier de simulation
			f = fopen( s_file, 'r' );
			fseek( f, 0, SEEK_END);
			s = ftell( f );
			fseek( f, 0, SEEK_SET);
			str = fscanf( f, '%c', s );
			eval( str );
			fclose(f);
			if (d_integral)
				x = x / nb_samples(n);
			end
			%Erreur sur les observations
			[err, m_err] = compute_errors( y, x );
			mean_observation_MSEs(n,:) = m_err / nb_exp(n);
			observation_MSEs = observation_MSEs + err / nb_exp(n);
			
			if ( i * j == 1 )
				Y = y;
				X = x;
			end
			
			%Lecture des données
			if ( d_integral )
				nb_filter_2 = nb_filters + 1;

				
				%Génération de l'intégral du signal
				i_y = zeros ( nb_samples(n) + 1, size_y );
				for kk = 1:nb_samples(n)
					i_y(kk + 1,:) = i_y(kk,:) + y(kk,:); 
				end
				i_y = i_y / nb_samples(n);
				if ( i * k )
					X_s(:, :, nb_filter_2) = i_y(:, 1:size_x);
					X_p(:, :, nb_filter_2) = i_y(:, 1:size_x);
					X_f(:, :, nb_filter_2) = i_y(1:end-1, 1:size_x);
				end
				if ( i * f_ok == 1 )
					L(nb_filter_2) = 0;
					mean_F(nb_filter_2) = 0;
					mean_Q(nb_filter_2) = 0;
					mean_t0(nb_filter_2) = 0; 
					mean_Q0(nb_filter_2) = 0;
				end
				
				[err, m_err] = compute_errors( i_y, x );
				mean_prediction_MSEs(n,:,nb_filter_2) = mean_prediction_MSEs(n,:,nb_filter_2) + m_err / nb_exp(n);
				prediction_MSEs(:,:,nb_filter_2) = prediction_MSEs(:,:,nb_filter_2) + err / nb_exp(n);
				
				mean_smoothing_MSEs(n,:,nb_filter_2) = mean_smoothing_MSEs(n,:,nb_filter_2) + m_err / nb_exp(n);
				smoothing_MSEs(:,:,nb_filter_2) = smoothing_MSEs(:,:,nb_filter_2) + err / nb_exp(n);
				
				mean_filtering_MSEs(n,:,nb_filter_2) = mean_filtering_MSEs(n,:,nb_filter_2) + m_err / nb_exp(n);
				filtering_MSEs(:,:,nb_filter_2) = filtering_MSEs(:,:,nb_filter_2) + err(1:end-1,:) / nb_exp(n);
				
			else
				
			end
			
			system(['rm -f ' s_file]);
		end
	end
	mean_t0_EM(n) = {mean_t0};
	mean_Q0_EM(n) = {mean_Q0}; 
	mean_F_EM(n)  = {mean_F};
	mean_Q_EM(n) = {mean_Q};
	S_likelihood(n) = {L};
	S_y(n) = {Y};
	S_x(n) = {X};
	S_X_s(n) = {X_s};
	S_observation_MSEs(n) = {observation_MSEs};
	S_prediction_MSEs(n) = {prediction_MSEs};
	S_filtering_MSEs(n) = {filtering_MSEs};
	S_smoothing_MSEs(n) = {smoothing_MSEs};
	
end

t2 = clock();
[str,t2] = avancement( exp_name, nb_processed, nb_total, t1, str, t2);
%Graphiques
S_mean_prediction_MSEs = mean_prediction_MSEs;
S_mean_observation_MSEs = mean_observation_MSEs;
S_mean_filtering_MSEs = mean_filtering_MSEs;
S_mean_smoothing_MSEs = mean_smoothing_MSEs;

if (d_integral)
	titles(nb_filter_2) = 'Integral';
end


ok = 1;
rmpath(p_dir);
rmpath(f_dir);
rmpath(cache_folder);
system(['rm -rf ' cache_folder]);
end



