SOURCES="main.cpp \
         TestHelpers.cpp \
         ../src/KeyValueReader.cpp \
         test1.cpp \
         test2.cpp \
         test3.cpp \
         test4.cpp"

g++ --std=c++11 -Wall $SOURCES -o test.x 
