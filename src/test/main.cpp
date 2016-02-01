#include "../KeyValueReader.h"

int main()
{
    KeyValueReader kvr;
    kvr.readFile("test.kv");
    kvr.print();
    return 0;
}
