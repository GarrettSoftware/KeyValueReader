SOURCES="main.cpp \
         TestHelpers.cpp \
         ../lib/libKeyValueReader.a"

cd ..
make
cd test

g++ --std=c++11 -Wall $SOURCES -o test.x -lgtest
