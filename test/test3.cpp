#include "../src/KeyValueReader.h"
#include <string>

using namespace std;

int main()
{
    printf("--- Test 3 (find key/value) ---\n");
    KeyValueReader kvr;
    KeyValueReader::Status status;
    string key = "";
    string valueString = "";
    int valueInt = 0;
    double valueDouble = 0.0;
    float valueFloat = 0.0;
    bool valueBool = false;
    
    
    // Read in file
    kvr.setAbortOnError(false);
    status = kvr.readFile("test3a.kv");
    if (status != KeyValueReader::StatusSuccess) {
    	printf("Test failed read.\n");
    	return 0;
    }
    
    
    // a
    status = kvr.getString("key1", valueString);
    if (status == KeyValueReader::StatusSuccess && valueString == "string")
    	printf("a: Passed\n");
    else
    	printf("a: Failed\n");
    // b
    status = kvr.getString("key_dne", valueString);
    if (status == KeyValueReader::StatusKeyNotFound) 
    	printf("b: Passed\n");
    else
    	printf("b: Failed\n");
    
    
    // c
    status = kvr.getInt("key2", valueInt);
    if (status == KeyValueReader::StatusSuccess && valueInt == 10)
    	printf("c: Passed\n");
    else
    	printf("c: Failed\n");
    // d
    status = kvr.getInt("key1", valueInt);
    if (status == KeyValueReader::StatusStringConversionError)
    	printf("d: Passed\n");
    else
    	printf("d: Failed\n");
    // e
    status = kvr.getInt("key_dne", valueInt);
    if (status == KeyValueReader::StatusKeyNotFound) 
    	printf("e: Passed\n");
    else
    	printf("e: Failed\n");
    
    
    // f
    status = kvr.getDouble("key3", valueDouble);
    if (status == KeyValueReader::StatusSuccess && valueDouble == 10.0)
    	printf("f: Passed\n");
    else
    	printf("f: Failed\n");
    // g
    status = kvr.getDouble("key1", valueDouble);
    if (status == KeyValueReader::StatusStringConversionError)
    	printf("g: Passed\n");
    else
    	printf("g: Failed\n");
    // h
    status = kvr.getDouble("key_dne", valueDouble);
    if (status == KeyValueReader::StatusKeyNotFound) 
    	printf("h: Passed\n");
    else
    	printf("h: Failed\n");
    
    
    // i
    status = kvr.getFloat("key3", valueFloat);
    if (status == KeyValueReader::StatusSuccess && valueFloat == 10.0f)
    	printf("i: Passed\n");
    else
    	printf("i: Failed\n");
    // j
    status = kvr.getFloat("key1", valueFloat);
    if (status == KeyValueReader::StatusStringConversionError)
    	printf("j: Passed\n");
    else
    	printf("j: Failed\n");
    // k
    status = kvr.getFloat("key_dne", valueFloat);
    if (status == KeyValueReader::StatusKeyNotFound) 
    	printf("k: Passed\n");
    else
    	printf("k: Failed\n");
    
    
    // l
    status = kvr.getBool("key4", valueBool);
    if (status == KeyValueReader::StatusSuccess && valueBool == true)
    	printf("l: Passed\n");
    else
    	printf("l: Failed\n");
    // m
    status = kvr.getBool("key1", valueBool);
    if (status == KeyValueReader::StatusStringConversionError)
    	printf("m: Passed\n");
    else
    	printf("m: Failed\n");
    // n
    status = kvr.getBool("key_dne", valueBool);
    if (status == KeyValueReader::StatusKeyNotFound) 
    	printf("n: Passed\n");
    else
    	printf("n: Failed\n");
    
    
    return 0;
}
