#include "../src/KeyValueReader.h"
#include "TestHelpers.h"

using namespace std;

bool test3()
{
    KeyValueReader kvr;
    string errors = "";
    
    // Print test 1
    printf("--- Test 3 (find key/value) ---\n");
    
    // Read in file
    trySuccess(kvr, "test3a.kv", '0', errors);
    
    // a
    tryKeyValueSuccessString(kvr, "key1", "string", 'a', errors);
    
    // b
    tryKeyValueFailureString(kvr, "key_dne", 'b', errors, 
                             KeyValueReader::ExceptionKeyNotFound);
    
    
    // c
    tryKeyValueSuccessInt(kvr, "key2", 10, 'c', errors);
    
    // d
    tryKeyValueFailureInt(kvr, "key1", 'd', errors, 
                          KeyValueReader::ExceptionStringConversionError);
    
    // e
    tryKeyValueFailureInt(kvr, "key_dne", 'd', errors, 
                          KeyValueReader::ExceptionKeyNotFound);
    
    
    // f
    tryKeyValueSuccessDouble(kvr, "key3", 10.0, 'f', errors);
    
    // g
    tryKeyValueFailureDouble(kvr, "key1", 'g', errors, 
                             KeyValueReader::ExceptionStringConversionError);
    
    // h
    tryKeyValueFailureDouble(kvr, "key_dne", 'h', errors, 
                             KeyValueReader::ExceptionKeyNotFound);
    
    
    // i
    tryKeyValueSuccessFloat(kvr, "key3", 10.0f, 'i', errors);
    
    // j
    tryKeyValueFailureFloat(kvr, "key1", 'j', errors, 
                            KeyValueReader::ExceptionStringConversionError);
    
    // k
    tryKeyValueFailureFloat(kvr, "key_dne", 'k', errors, 
                            KeyValueReader::ExceptionKeyNotFound);
    
    
    // l
    tryKeyValueSuccessBool(kvr, "key4", 10.0f, 'l', errors);
    
    // m
    tryKeyValueFailureBool(kvr, "key1", 'm', errors, 
                           KeyValueReader::ExceptionStringConversionError);
    
    // n
    tryKeyValueFailureBool(kvr, "key_dne", 'n', errors, 
                           KeyValueReader::ExceptionKeyNotFound);
    
    
    // Return
    if (errors == "")
        return true;
    return false;
}
