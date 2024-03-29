CXX=g++
CC=gcc
EXE=calibration
LDFLAGS= -lglut -lGLU -lGLEW -L.
LDFLAGS+= -lOpenKN-math -lOpenKN-image
CFLAGS= -g -O2 -Wall -I.

$(EXE) : main.o
	$(CXX) $^  $(LDFLAGS) -o $(EXE)

main.o : main.cpp
	$(CXX) -c  $(CFLAGS) $<

%.o : %.cpp %.hpp
	$(CXX) -c  $(CFLAGS) $<

.PHONY : clean ultraclean

clean:
	rm -f *.o *~

ultraclean : clean
	rm -f $(EXE)
