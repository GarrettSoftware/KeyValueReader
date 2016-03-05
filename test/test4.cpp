#include "../src/KeyValueReader.h"
#include "TestHelpers.h"

using namespace std;


static
void testConstMethods(const CKG_Utils::KeyValueReader &kvr)
{
    string valueString;
    int valueInt;
    double valueDouble;
    float valueFloat;
    bool valueBool;
    
    kvr.getString("key1", valueString);
    kvr.getInt("key2", valueInt);
    kvr.getDouble("key3", valueDouble);
    kvr.getFloat("key3", valueFloat);
    kvr.getBool("key4", valueBool);
    
    kvr.print();
}

bool test4()
{
    CKG_Utils::KeyValueReader kvr;
    
    // Print test 4
    printf("--- Test 4 (ensure compile with const methods) ---\n");
    
    kvr.readFile("test4a.kv");
    testConstMethods(kvr);
    
    return true;
}
