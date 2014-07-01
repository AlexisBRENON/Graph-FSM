.PHONY: check mrproper clean

all: check
	g++ src/main.cpp src/automate_det.cpp src/automate_non_det.cpp -o bin/automate
	
check:
	@if [ ! -e bin ]; then mkdir bin; fi
	
clean:
	
	
mrproper:
	rm bin/automate
