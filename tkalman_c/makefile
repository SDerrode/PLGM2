
all:
	@(cd PKF; make)
	@(cd Simulation;make)
	@(cd API; make)
	@(cd Applications;make)
clean:
	@(cd PKF; make clean)
	@(cd Simulation;make clean)
	@(cd API; make clean)
	@(cd Applications;make clean)
	
MrProper:
	@(cd PKF; make MrProper)
	@(cd Simulation;make MrProper)
	@(cd API; make MrProper)
	@(cd Applications;make MrProper)

forced:
	make clean
	make all
