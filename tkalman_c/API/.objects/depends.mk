#option dependencies

.objects/tkalman_api_em_parameters.o:options.mk 
.objects/tkalman_api_parameters.o:options.mk 
.objects/tkalman_api_signal.o:options.mk

.objects/tkalman_api_em_parameters.o:../../compilation.mk 
.objects/tkalman_api_parameters.o:../../compilation.mk 
.objects/tkalman_api_signal.o:../../compilation.mk

.objects/tkalman_api_em_parameters.o:makefile 
.objects/tkalman_api_parameters.o:makefile 
.objects/tkalman_api_signal.o:makefile
#source dependencies

.objects/tkalman_api_em_parameters.o:source/tkalman_api_em_parameters.cpp 
.objects/tkalman_api_parameters.o:source/tkalman_api_parameters.cpp 
.objects/tkalman_api_signal.o:source/tkalman_api_signal.cpp
# DO NOT DELETE

.objects/tkalman_api_em_parameters.o: ../API/include/tkalman_api_em_parameters.hpp
.objects/tkalman_api_em_parameters.o: ../API/include/tkalman_api_parameters.hpp
.objects/tkalman_api_parameters.o: ../API/include/tkalman_api_parameters.hpp
.objects/tkalman_api_signal.o: ../API/include/tkalman_api_signal.hpp