# Change this line for different compiler options
# The library requires compiling with the C++11 standard
CC = g++ --std=c++11


.PHONY: libKeyValueReader.a
libKeyValueReader.a:
	for FILE in src/*.cpp; do \
		$(CC) -fpic -c $$FILE ; \
	done
	ar rcs libKeyValueReader.a *.o
	rm *.o

