#include "../KeyValueReader.h"

int main()
{
    KeyValueReader kvr;
    kvr.setAbortOnError(false);
    kvr.readFile("test.kv");
    kvr.print();
    
    KeyValueReader kvr2;
    kvr2.setAbortOnError(false);
    kvr2.readFile("test2.kv");
    kvr2.print();
    
    KeyValueReader kvr3;
    kvr3.setAbortOnError(false);
    kvr3.readFile("test3.kv");
    kvr3.print();
    
    KeyValueReader kvr4;
    kvr4.setAbortOnError(true);
    kvr4.readFile("test4.kv");
    kvr4.print();
    
    return 0;
}
