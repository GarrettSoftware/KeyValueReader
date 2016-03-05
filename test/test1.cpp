#include "../src/KeyValueReader.h"
#include "TestHelpers.h"

using namespace std;

bool test1()
{
    CKG_Utils::KeyValueReader kvr;
    string errors = "";
    
    // Print test 1
    printf("--- Test 1 (reading a file) ---\n");
    
    // a
    tryFailure(kvr, "test_does_not_exist.kv", 'a', errors, 
               CKG_Utils::KeyValueReader::ExceptionOpenFileError);
    
    // b
    kvr.reset();
    trySuccess(kvr, "test1a.kv", 'b', errors);
	
	// c
	tryFailure(kvr, "test1b.kv", 'c', errors, 
	           CKG_Utils::KeyValueReader::ExceptionAlreadyReadAFile);
    
    // Return
    if (errors == "")
        return true;
    return false;
}
