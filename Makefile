CPPFLAGS = -O3
LDFLAGS  = -lpthread 

all: Main 

clean :
	rm -f *.o

Main: Main.o my_scanner.o
	g++ -o $@ $^ $(LDFLAGS)
