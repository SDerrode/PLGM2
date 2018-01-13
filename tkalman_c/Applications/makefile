#======================================================================#
#                                 Makefile                             #
#======================================================================#
#    Autheur : Valérian Némesin                                        #
#======================================================================#
#    Modifiez le fichier options.mk pour l'utiliser                    #
#    1 fichier source (.cpp) => 1 exécutable (.run)                    #
#======================================================================#

#Options
	-include options.mk
	-include $(M_OPTIONS)

#Rep courant	
	CUR=$(shell echo `pwd`)

#Options de compilation
	CPFLAGS=$(addprefix `pkg-config --cflags --libs ,$(addsuffix `,$(D_LIBS))) $(CP_OPT) $(addprefix -I,$(S_LIBS)) $(addprefix -I,$(addsuffix /include/,$(S_LIBS)))
	CCFLAGS=$(addprefix `pkg-config --cflags --libs ,$(addsuffix `,$(D_LIBS))) $(CP_OPT)

#Fichier de gestion des dépendances
	INCLUDEFILE=$(OBJ_DIR)/$(DEP_FILE)

#Listing de tous les fichiers sources
	#Chemins relatifs de tous les fichiers sources
	SRC_LIST_REL=$(wildcard $(SRC_DIR)/*.$(SRC_EXT))
	#Chemins relations par rapport aux rép. objet
	SRC_LIST_REL_OBJ=$(addprefix ../,$(SRC_LIST_REL))
	#Noms de fichiers
	SRC_FILENAMES=$(notdir $(SRC_LIST_REL) )

#Listing de tous les fichiers objets 
	OBJ_LIST=$(addsuffix .o, $(basename $(addprefix $(OBJ_DIR)/, $(notdir $(SRC_LIST_REL)) )))

#Listing de tous les éxécutables
	RUN_LIST=$(addsuffix .$(E_EXT),$(basename $(addprefix $(APP_DIR), $(notdir $(SRC_LIST_REL)))))

#Décompilation des .a et compilation des .o
	LIBS_A=$(wildcard $(addsuffix /*.a, $(S_LIBS)))
	L_CMD=$(addprefix ar -x ,$(addsuffix ;,$(realpath $(LIBS_A) ) ) )

#Dépendances
	#entre .cpp et .o
	DEP_1=$(addprefix "\n", $(join $(addsuffix :,$(OBJ_LIST)), $(SRC_LIST_REL) ) )
	#entre .cpp et options
	DEP_OPT_1=$(addprefix "\n",$(addsuffix :options.mk,$(OBJ_LIST)))
	DEP_OPT_2=$(addprefix "\n",$(addsuffix :$(M_OPTIONS),$(OBJ_LIST)))
	DEP_MAKE=$(addprefix "\n",$(addsuffix :makefile,$(OBJ_LIST)))
	
	#entre .run et .o
	DEP_2=$(addprefix "\n", $(join $(addsuffix :,$(RUN_LIST)),$(OBJ_LIST) ) )
	#entre .run et options
	DEP_2_OPT_1=$(addprefix "\n",$(addsuffix :options.mk,$(RUN_LIST)))
	DEP_2_OPT_2=$(addprefix "\n",$(addsuffix :$(M_OPTIONS),$(RUN_LIST)))
	DEP_2_MAKE=$(addprefix "\n",$(addsuffix :makefile,$(RUN_LIST)))
	#entre .run et NAME
	DEP_DINO=$(addprefix "\n",$(addsuffix :$(NAME).a,$(RUN_LIST)))

#Commande MAKE
	MAKE_ROOT = $(addprefix cd ,$(addsuffix ;make;, $(REP)) )
	MAKE_ALL= $(subst ;make;,;make;cd ..;,$(MAKE_ROOT))

$(LOG_FILE) :: $(RUN_LIST) $(LIBS_A) options.mk $(M_OPTIONS) makefile
	@echo "#Compilation - OK"
	@echo "#Compilation - OK">>$(LOG_FILE)
#Import du fichier de gestion des dépendances
-include $(INCLUDEFILE)

#Compilation des exécutables
%.$(E_EXT) :
	@echo "#creating $(notdir $@)">>$(LOG_FILE)
	@echo "#creating $(notdir $@)"
	@mkdir -p $(APP_DIR)
	@$(CC) $(OBJ_DIR)/$(basename $(notdir $@)).o $(NAME).a $(CCFLAGS) -o $@ 2>>$(LOG_FILE)

#Compilation des objets

%.o :
	@echo "#creating $(notdir $@)">>$(LOG_FILE)
	@echo "#creating $(notdir $@)"
	@$(CC) $(CPFLAGS) -c $(SRC_DIR)/$(notdir $(basename $@ )).$(SRC_EXT) -o $@  2>>$(LOG_FILE)

#Compilation de dinosaure.a
$(NAME).a :: $(LIBS_A) options.mk $(M_OPTIONS) makefile
	@rm -f *.a
	@echo "#creating $(NAME).a">>$(LOG_FILE) 
	@echo "#creating $(NAME).a"
	@mkdir -p $(TMP_DIR)
	@(cd $(TMP_DIR);$(L_CMD) )
	@(cd $(TMP_DIR);ar -r ../$(NAME).a  *.o) 2>>$(LOG_FILE) 
	@rm -r -f $(TMP_DIR)

#Création des dépendances
$(INCLUDEFILE):: $(SRC_LIST_REL) options.mk $(M_OPTIONS) makefile
	@rm -f $(LOG_FILE)
	@echo "### Make $(NAME)"
	@echo "">>$(LOG_FILE)
	@echo "### Make $(NAME)">>$(LOG_FILE)
	@echo "">>$(LOG_FILE)
	@echo "### creating $(notdir ${INCLUDEFILE})">>$(LOG_FILE)
	@echo "### creating $(notdir ${INCLUDEFILE})"
	@mkdir -p $(OBJ_DIR)
	@echo $(DEP_2)>$(INCLUDEFILE)
	@echo $(DEP_2_OPT_1)>>$(INCLUDEFILE)
	@echo $(DEP_2_OPT_2)>>$(INCLUDEFILE)
	@echo $(DEP_2_MAKE)>>$(INCLUDEFILE)
	@echo $(DEP_DINO)>>$(INCLUDEFILE)
	@echo $(DEP_OPT_1)>>$(INCLUDEFILE)
	@echo $(DEP_OPT_2)>>$(INCLUDEFILE)
	@echo $(DEP_MAKE)>>$(INCLUDEFILE)
	@echo $(DEP_1)>>$(INCLUDEFILE)
	@(cd $(SRC_DIR) ;makedepend -f../$(INCLUDEFILE) -p$(OBJ_DIR)/ $(SRC_FILENAMES) 2>>/dev/null ) 1>>$(LOG_FILE)
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
	@rm -f $(RUN_LIST)
	
