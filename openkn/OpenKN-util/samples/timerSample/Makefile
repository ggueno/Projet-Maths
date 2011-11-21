all: timerSample

timerSample:  main.o
	g++ -o  timerSample main.o

main.o : main.cpp
	g++ -c  main.cpp -o main.o  -I../../../libIMAC-util/src -I.

clean :
	rm -f *_o *.o *~ timerSample report.txt
