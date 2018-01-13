all:
	@(cd API; make)
	@(cd tkalman_c;make)
clean:
	@(cd API; make clean)
	@(cd tkalman_c;make clean)
MrProper:
	@(cd API; make MrProper)
	@(cd tkalman_c;make MrProper)
forced:
	make clean
	make all
