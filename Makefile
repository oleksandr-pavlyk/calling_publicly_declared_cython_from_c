all:
	cython --cplus rect.pyx
	c++ -g -O2 -c rect.cpp -o rect.o -I`python3-config --includes`
	c++ -g -O2 -c Rectangle.cpp -o Rectangle.o -I`python3-config --includes`
	c++ -g -O2 -c main.cpp -o main.o -I`python3-config --includes`
	c++ -g -O2 -o rect Rectangle.o rect.o main.o `python3-config --libs` -L$(CONDA_PREFIX)/lib -Wl,-rpath,$(CONDA_PREFIX)/lib

clean:
	rm -f rect rect.cpp rect.h *.o
