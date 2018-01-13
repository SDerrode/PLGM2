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

#Options de compilation
	CPFLAGS=$(addprefix `pkg-config --cflags --libs ,$(addsuffix `,$(D_LIBS))) $(CP_OPT) $(addprefix -I,$(S_LIBS)) $(addprefix -I,$(addsuffix /include/,$(S_LIBS)))



#Listing de tous les fichiers sources
	#Chemins relatifs de tous les fichiers sources
	SRC_LIST_REL=$(wildcard $(SRC_DIR)/*.$(SRC_EXT))
	#Chemins relations par rapport aux rép. objet
	SRC_LIST_REL_OBJ=$(addprefix ../,$(SRC_LIST_REL))
	#Noms de fichiers
	SRC_FILENAMES=$(notdir $(SRC_LIST_REL) )



#Décompilation des .a et compilation des .o
	S_LIBS= $(subst include/,, $(subst $(OBJ_DIR)/,, $(wildcard */ ) ))
	LIBS_A=$(wildcard $(addsuffix *.a, $(S_LIBS)))
	L_CMD = $(addprefix ar -x ,$(addsuffix ;,$(realpath $(LIBS_A) ) ) )
	
#LOG_files
	LOG_FILES=$(addsuffix $(LOG_FILE),$(S_LIBS) )
	
#Création du fichier header
	LIST_HPP=$(wildcard $(addsuffix *.$(HD_EXT), $(S_LIBS)))
	#Ajout de "\n à la fin
	TMP_H_LIST_1=$(addsuffix "\"\n",$(LIST_HPP) )
	#Ajout de #include " au début
	TMP_H_LIST_2=$(addprefix "\#include \"./",$(TMP_H_LIST_1) )
	#Macro
	TMP_MACRO=$(addprefix __, $(addsuffix __,$(shell echo "$(subst .,_,$(NAME) )" | tr '[:lower:]' '[:upper:]' ) ) )
	#En-tête
	TMP_HEAD ="/**@file "$(H_NAME)"\n * @author "$(AUTHOR)"\n * @date"$(DATE)"\n * @brief "$(DESC)"\n**/\n"
	#Fichier 
	H_FILE_TXT=$(TMP_HEAD)"\#ifndef $(TMP_MACRO)\n\#define $(TMP_MACRO)\n"$(TMP_H_LIST_2)"\#endif\n"
	
#Commande MAKE
	MAKE_ROOT = $(addprefix cd ,$(addsuffix ;make;, $(S_LIBS)) )
	MAKE_ALL= $(subst ;make;,;make;cd ..;,$(MAKE_ROOT))
	MAKE_CLEAN= $(subst ;make;,;make clean;cd ..;,$(MAKE_ROOT))
	MAKE_MR_PROPER= $(subst ;make;,;make MrProper;cd ..;,$(MAKE_ROOT))
	N=$(words $(S_LIBS))
	
all :
	@rm -f $(LOG_FILE)
	@for i in `seq 0 $(N)`; do\
		$(MAKE_ALL)\
	done
	make $(NAME).a 

#Compilation forcée
forced : 
	@echo "### Make forced $(NAME)"
	@make clean
	@make
	

#Suppression des .o
clean :
	$(MAKE_CLEAN)
	@echo "### Make clean $(NAME)"
	@rm -f ${INCLUDEFILE}
	@rm -f $(LOG_FILE)
	@rm -rf $(OBJ_DIR)
	@rm -f *~

#M. Propre
MrProper :
	@echo "### Make MrProper $(NAME)"
	$(MAKE_MR_PROPER)
	@make clean
	@rm -f *.a
	@rm -f *.hpp
	@rm -f $(RUN_LIST)
	
#Compilation des exécutables
#Compilation des objets
#Compilation de dinosaure.a
$(NAME).a : $(NAME).$(HD_EXT) $(LIBS_A)
	@rm -f *.a
	@echo "#creating $(NAME).a">>$(LOG_FILE) 
	@echo "#creating $(NAME).a"
	@mkdir -p $(TMP_DIR)
	@(cd $(TMP_DIR);$(L_CMD) )
	@(cd $(TMP_DIR);ar -r ../$(NAME).a  *.o) 2>>$(LOG_FILE) 
	@rm -r -f $(TMP_DIR)

$(NAME).$(HD_EXT) :: $(H_NAME)
	@rm -f *.hpp
	@echo "### creating $(NAME).$(HD_EXT) "
	@echo "### creating $(NAME).$(HD_EXT) ">>$(LOG_FILE)
	@echo $(LIST_HPP)
	@echo $(H_FILE_TXT)>$(NAME).$(HD_EXT)
