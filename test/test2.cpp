#include "../src/KeyValueReader.h"
#include "TestHelpers.h"

using namespace std;

bool test2()
{
    KeyValueReader kvr;
    string errors = "";
    
    // Print test 2
    printf("--- Test 2 (parsing) ---\n");
    
    // a
    trySuccess(kvr, "test2a.kv", 'a', errors);
    
    // b
    kvr.reset();
    tryFailure(kvr, "test2b.kv", 'b', errors, 
	           KeyValueReader::ExceptionParseFileError);
	
	// c
	kvr.reset();
	tryFailure(kvr, "test2c.kv", 'c', errors, 
	           KeyValueReader::ExceptionParseFileError);
	
	// d
	kvr.reset();
	tryFailure(kvr, "test2d.kv", 'd', errors, 
	           KeyValueReader::ExceptionParseFileError);
    
    // Return
    if (errors == "")
        return true;
    return false;
}
