/**@file api_parameters.hpp
 * @brief
 * Ce fichier contient le prototype de la classe gérant les paramètres du programme.
 * 
 * 
 **/
#ifndef _API_PARAMETERS_HPP_
#define _API_PARAMETERS_HPP_
	#define API_NB_VAR_MAX 256

	#include "api_variable.hpp"
	/**@class api_parameters
	 * @brief
	 * Classe de gestion des paramètres du programme.
	 **/
	class api_parameters
	{
		public:
			/**@fn api_parameters :: api_parameters( const char * filename = "",
													 unsigned int nb_var_max = API_NB_VAR_MAX)
			 * @param filename : nom du fichier à ouvrir
			 * @param nb_var_max : nombre de variables maximum
			 * @brief Constructeur
			 */
			api_parameters(unsigned int nb_var_max = API_NB_VAR_MAX);
			
			/**@fn void api_parameters :: setup(	const char * filename = "",
													unsigned int nb_var_max = API_NB_VAR_MAX)
			 * @param filename : nom du fichier à ouvrir
			 * @param nb_var_max : nombre de variables maximum
			 * @brief
			 * Setuo
			 */
			void setup(unsigned int nb_var_max = API_NB_VAR_MAX);
		
			/**@fn void api_parameters :: set_max_nb_variables(unsigned int nb_var_max = API_NB_VAR_MAX);
			 * @param nb_var_max : nombre de variables maxi.
			 * @brief
			 * Modifie le nombre maximal de variables supportées par l'objet.
			 * 
			 */
			void set_max_nb_variables(unsigned int nb_var_max = API_NB_VAR_MAX);
		
			/**@fn int api_parameters :: add_variable(const char * name);
			 * @param name : nom de la variable à ajouter
			 * @return
			 * - 0 si réussite
			 * - 1 sinon
			 * @brief
			 * Ajoute une variable vide à l'objet.
			 */
			 
			int add_variable(const char * name);
			
			/**@fn int api_parameters :: add_variable(const api_variable & variable)
			 * @param variable : variable à ajouter
			 * @return
			 * - 0 si réussite de l'ajout de la variable
			 * - 1 en cas d'échec
			 * @brief
			 * Ajoute une variable à l'objet.
			 */
			int add_variable(const api_variable & variable);
			
			/**@fn api_parameters :: ~api_parameters()
			 * @brief
			 * Destructeur.
			 */
			~api_parameters();
		
			/**@fn inline unsigned int api_parameters :: nb_variables() const
			 * @return 
			 * nombre de variables.
			 * 
			 */
			inline unsigned int nb_variables() const
			{
				return _nb_var;
			}
		
			/**@fn inline unsigned int api_parameters :: max_nb_variables() const
			 * @return
			 * Nombre maximum de variables supportées par l'objet.
			 */
			inline unsigned int max_nb_variables() const
			{
				return _nb_var_max;
			}
			
			/**@fn api_variable *  api_parameters :: operator[](const char * name);
			 * @param name : nom de variable.
			 * @return 
			 * - variable de nom name
			 * - ou NULL si elle n'existe pas.
			 * @brief
			 * Cette fonction renvoie la variable de nom name et NULL si elle n'existe pas.
			 */
			api_variable * operator[](const char * name);
			
			/**@fn api_variable ** api_parameters :: get_variables() const
			 * @return Différentes variables
			 * 
			 **/
			inline api_variable ** get_variables() const
			{
				return variables;
			}
			
			/**@fn int api_parameters :: delete_variable(const char * name);
			 * @param name : nom de la variable à sup.
			 * @brief
			 * Supprime la variable de nom name.
			 */
			int delete_variable(const char * name);
			
			/**@fn int api_parameters :: save(const char * filename);
			 * @param filename : fichier
			 * @return
			 * - 0 en cas de réussite de la sauvegarde
			 * - 1 sinon
			 * @brief
			 * Sauvegarde les différentes variables dans le fichier filename.
			 */
			int save(const char * filename, const char * format = API_DEFAULT_FORMAT);
			
			/**@fn int api_parameters :: load(const char * filename);
			 * @param filename : fichier
			 * @return
			 * - 0 en cas de réussite de  la lecture
			 * - 1 sinon
			 * @brief
			 * Lit le fichier filename pour extraire les différentes variables.
			 */
			int load(const char * filename, const char * format = API_DEFAULT_FORMAT);
			
			/**@fn int api_parameters :: search_variables_with_prefix( 	const char * prefix, 
																		api_variable ** variables,
																		int * nb_variables,
																		int nb_variables_max );
			 * @param prefix : prefixe
			 * @param variables : variables trouvées
			 * @param nb_variables : nombre de variables trouvées
			 * @param nb_variables_max : nombre de variables maximum.
			 * @return
			 * - 1 s'il y 'a trop de variables.
			 * @brief
			 * Cette fonction recherche les variables dont leur nom commence par prefix.
			 * 
			 **/
			int search_variables_with_prefix( 	const char * prefix, 
												api_variable ** variables,
												unsigned int * nb_variables,
												unsigned int nb_variables_max );
			
			/**@fn int api_parameters :: detect_namespaces(	char *** namespaces,
														int * nb_namespaces );
			 * @param namespaces : espace de noms
			 * @param nb_namespaces : nombre d'espace de noms
			 * @brief
			 * Détecte tous les espaces de nom inclu dans les variables
			 **/
			int detect_namespaces( char *** namespaces,
								   unsigned int * nb_namespaces );
		protected:
			/**@fn void api_parameters :: free();
			 * @brief
			 * Libération mémoire
			 **/
			void free();
			
			/**@fn void api_parameters :: initialize();
			 * @brief
			 * Met à 0 tous les attributs de l'objet.
			 */
			void initialize();
			unsigned int _nb_var;
			unsigned int _nb_var_max;
			api_variable ** variables; //Liste des variables ordonnées
	};

#endif
