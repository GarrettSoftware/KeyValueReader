# Change this line for different compiler options
# This library requires compiling with the C++11 standard
CC = g++ --std=c++11 -Wall


.PHONY: libKeyValueReader
libKeyValueReader:
	for FILE in src/*.cpp; do \
		$(CC) -fpic -c $$FILE ; \
	done
	mkdir -p lib
	ar rcs lib/libKeyValueReader.a *.o
	$(CC) -shared -o lib/libKeyValueReader.so *.o
	rm *.o

