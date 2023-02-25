zlibcompress: main.o compressionlib.o
	g++ main.o compressionlib.o -o zlibcompress -lz

main.o : main.cpp
	g++ -c main.cpp

compressionlib.o : compressionlib.cpp compressionlib.h
	g++ -c compressionlib.cpp

clean:
	rm *.o zlibcompress