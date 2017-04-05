SOURCES="main.cpp \
         TestHelpers.cpp \
         ../src/KeyValueReader.cpp"

g++ --std=c++11 -Wall $SOURCES -o test.x -lgtest
