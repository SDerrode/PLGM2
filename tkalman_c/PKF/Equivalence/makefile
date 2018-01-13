#======================================================================#
#                                 Makefile                             #
#======================================================================#
#    Autheur : Valérian Némesin                                        #
#======================================================================#
#    Modifiez le fichier options.mk pour l'utiliser                    #
#======================================================================#

#Options
	-include options.mk
	-include $(M_OPTIONS)

#Rep courant	
	CUR=$(shell echo `pwd`)

#Fichier de gestion des dépendances
	INCLUDEFILE=$(OBJ_DIR)/$(DEP_FILE)

#Listing de tous les fichiers sources
	#Chemins relatifs de tous les fichiers sources
	SRC_LIST_REL=$(wildcard $(SRC_DIR)/*.$(SRC_EXT))
	#Chemins relations par rapport aux rép. objet
	SRC_LIST_REL_OBJ=$(addprefix ../,$(SRC_LIST_REL))
	#Noms de fichiers
	SRC_FILENAMES=$(notdir $(SRC_LIST_REL) )
	
#Construction de la liste des fichiers headers
	#Chemins absolus de tous les fichiers headers
	H_LIST_ABS="$(shell echo `pwd`)/$(HEAD_DIR)/"
	#Chemin relatifs de tous les fichiers headers
	H_LIST_REL=$(wildcard $(HEAD_DIR)/*.$(HD_EXT))
	
#Construction des noms de fichier pour le résultats de la compilation
	#Fichier header
	H_NAME=$(basename $(NAME)).$(HD_EXT)
	#Fichier .tar
	T_NAME=$(basename $(NAME)).tar 
	#Fichier .tar.gz
	Z_NAME=$(basename $(NAME)).tar.gz
	#Fichier .a
	L_NAME = $(basename $(NAME)).a
	

	
#Construction du fichier header pour la bibliothèque
	#Ajout de "\n à la fin
	TMP_H_LIST_1=$(addsuffix "\"\n",$(H_LIST_REL) )
	#Ajout de #include " au début
	TMP_H_LIST_2=$(addprefix "\#include \"./",$(TMP_H_LIST_1) )
	#Macro
	TMP_MACRO=$(addprefix __, $(addsuffix __,$(shell echo "$(subst .,_,$(H_NAME) )" | tr '[:lower:]' '[:upper:]' ) ) )
	#En-tête
	TMP_HEAD ="/**@file "$(H_NAME)"\n * @author "$(AUTHOR)"\n * @date"$(DATE)"\n * @brief "$(DESC)"\n**/\n"
	#Fichier 
	H_FILE_TXT=$(TMP_HEAD)"\#ifndef $(TMP_MACRO)\n\#define $(TMP_MACRO)\n"$(TMP_H_LIST_2)"\#endif\n"
	
#Listing de tous les fichiers objets 
OBJ_LIST=$(addsuffix .o, $(basename $(addprefix $(OBJ_DIR)/, $(notdir $(SRC_LIST_REL)) )))

#Dépendances 
	#entre .cpp et .o
	DEP=$(addprefix "\n", $(join $(addsuffix :,$(OBJ_LIST)), $(SRC_LIST_REL) ) )
	#entre .o et les options
	DEP_OPT_1=$(addprefix "\n",$(addsuffix :options.mk,$(OBJ_LIST)))
	DEP_OPT_2=$(addprefix "\n",$(addsuffix :$(M_OPTIONS),$(OBJ_LIST)))
	DEP_MAKE=$(addprefix "\n",$(addsuffix :makefile,$(OBJ_LIST)))
#Construction des options de compilations
	CPFLAGS=$(addprefix `pkg-config --cflags --libs ,$(addsuffix `,$(D_LIBS))) $(CP_OPT) $(addprefix -I,$(S_LIBS)) $(addprefix -I,$(addsuffix /include,$(S_LIBS))) -I/$(H_LIST_ABS)

$(LOG_FILE) ::  $(SRC_LIST_REL) options.mk $(M_OPTIONS) makefile $(L_NAME) $(H_NAME) 
	@echo "### Compilation - OK"
	@echo "### Compilation - OK">>$(LOG_FILE)


#Compilation du .a	
$(L_NAME) :: $(OBJ_LIST) $(H_NAME)
	@rm -f *.a
	@echo "### creating $(L_NAME)"
	@echo "### creating $(L_NAME)">>$(LOG_FILE)
	@ar -rc $(L_NAME) $(OBJ_LIST)

#Création du fichier header
$(H_NAME) :: $(H_LIST_REL) $(INCLUDEFILE)
	@rm -f *.hpp
	@echo "### creating $(H_NAME)"
	@echo "### creating $(H_NAME)">>$(LOG_FILE)
	@echo $(H_FILE_TXT)>$(H_NAME)

#Import du fichier de gestion des dépendances
-include $(INCLUDEFILE) 
%.o :
	@echo "### creating $(notdir $@)"
	@mkdir -p $(OBJ_DIR)
	@echo "### creating $(notdir $@)">>$(LOG_FILE)
	@$(CC) $(CPFLAGS) -c $(SRC_DIR)/$(notdir $(basename $@ )).$(SRC_EXT) -o $@ 2>>$(LOG_FILE)


	
#Création du fichier de gestion des dépendances
$(INCLUDEFILE) :: $(SRC_LIST_REL) options.mk $(M_OPTIONS) makefile
	@rm -f $(LOG_FILE)
	@echo "### Make $(NAME)"
	@echo "">>$(LOG_FILE)
	@echo "### Make $(NAME)">>$(LOG_FILE)
	@echo "">>$(LOG_FILE)
	@echo "### creating $(notdir ${INCLUDEFILE})"
	@echo "### creating $(notdir ${INCLUDEFILE})">>$(LOG_FILE)
	
#Création du rép. objet
	@mkdir -p $(OBJ_DIR)
	@echo "#option dependencies" > $(INCLUDEFILE)
	@echo $(DEP_OPT_1)>>$(INCLUDEFILE)
	@echo $(DEP_OPT_2)>>$(INCLUDEFILE)
	@echo $(DEP_MAKE)>>$(INCLUDEFILE)
	
	@echo "#source dependencies" >> $(INCLUDEFILE)
	@echo $(DEP)>>$(INCLUDEFILE)
	
	@(cd $(SRC_DIR) ;makedepend $(addprefix -I,$(S_LIBS)) $(addprefix -I,$(addsuffix /include/,$(S_LIBS))) -I/$(H_LIST_ABS) -f../$(INCLUDEFILE) -p$(OBJ_DIR)/ $(SRC_FILENAMES) 2>>/dev/null ) 1>>$(LOG_FILE)
	@sed -i -e "s/ ..\/..\// ..\//g" $(INCLUDEFILE) 

#Compilation forcée
forced : 
	@echo "### Make forced $(NAME)"
	@make clean
	@make
	

#Suppression des .o
clean :
	@echo "### Make clean $(NAME)"
	@rm -f ${INCLUDEFILE}
	@rm -f $(LOG_FILE)
	@rm -rf $(OBJ_DIR)
	@rm -f *~

#M. Propre
MrProper :
	@echo "### Make MrProper $(NAME)"
	@make clean
	@rm -f *.a
	@rm -f *.hpp
