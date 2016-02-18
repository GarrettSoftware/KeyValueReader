#include "../src/KeyValueReader.h"
#include <string>

using namespace std;


static
void trySuccess(KeyValueReader &kvr, const string filename, const char test, string errors)
{
    try {
        kvr.readFile(filename);
    }
    catch (...) {
        errors += test;
    }
}

static
void tryFailure(KeyValueReader &kvr, const string filename, 
                const KeyValueReader::Exception exceptionToMatch, 
                const char test, string errors)
{
    try {
        kvr.readFile(filename);
        errors += test;
    }
    catch (KeyValueReader::Exception e) {
        if (e != exceptionToMatch)
            errors += test;
    }
}

bool test1()
{
    printf("--- Test 1 (reading a file) ---\n");
    KeyValueReader kvr;
    string errors = "";
    
    // a
    tryFailure(kvr, "test_does_not_exist.kv", KeyValueReader::ExceptionOpenFileError, 'a', errors);
    
    // b
    kvr.reset();
    trySuccess(kvr, "test1a.kv", 'b', errors);	
	
	// c
	tryFailure(kvr, "test1b.kv", KeyValueReader::ExceptionAlreadyReadAFile, 'c', errors);
    
    if (errors == "")
        return true;
    return false;
}
