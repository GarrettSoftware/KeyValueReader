#include "../src/KeyValueReader.h"
#include "TestHelpers.h"

using namespace std;

bool test3()
{
    CKG_Utils::KeyValueReader kvr;
    string errors = "";
    
    // Print test 1
    printf("--- Test 3 (find key/value) ---\n");
    
    // Read in file
    trySuccess(kvr, "test3a.kv", '0', errors);
    
    // a
    tryKeyValueSuccessString(kvr, "key1", "string", 'a', errors);
    
    // b
    tryKeyValueFailureString(kvr, "key_dne", 'b', errors, 
                             CKG_Utils::KeyValueReader::ExceptionKeyNotFound);
    
    
    // c
    tryKeyValueSuccessInt(kvr, "key2", 10, 'c', errors);
    
    // d
    tryKeyValueFailureInt(kvr, "key1", 'd', errors, 
                          CKG_Utils::KeyValueReader::ExceptionStringConversionError);
    
    // e
    tryKeyValueFailureInt(kvr, "key_dne", 'd', errors, 
                          CKG_Utils::KeyValueReader::ExceptionKeyNotFound);
    
    
    // f
    tryKeyValueSuccessDouble(kvr, "key3", 10.0, 'f', errors);
    
    // g
    tryKeyValueFailureDouble(kvr, "key1", 'g', errors, 
                             CKG_Utils::KeyValueReader::ExceptionStringConversionError);
    
    // h
    tryKeyValueFailureDouble(kvr, "key_dne", 'h', errors, 
                             CKG_Utils::KeyValueReader::ExceptionKeyNotFound);
    
    
    // i
    tryKeyValueSuccessFloat(kvr, "key3", 10.0f, 'i', errors);
    
    // j
    tryKeyValueFailureFloat(kvr, "key1", 'j', errors, 
                            CKG_Utils::KeyValueReader::ExceptionStringConversionError);
    
    // k
    tryKeyValueFailureFloat(kvr, "key_dne", 'k', errors, 
                            CKG_Utils::KeyValueReader::ExceptionKeyNotFound);
    
    
    // l
    tryKeyValueSuccessBool(kvr, "key4", 10.0f, 'l', errors);
    
    // m
    tryKeyValueFailureBool(kvr, "key1", 'm', errors, 
                           CKG_Utils::KeyValueReader::ExceptionStringConversionError);
    
    // n
    tryKeyValueFailureBool(kvr, "key_dne", 'n', errors, 
                           CKG_Utils::KeyValueReader::ExceptionKeyNotFound);
    
    
    // Return
    if (errors == "")
        return true;
    return false;
}
