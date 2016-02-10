#include "../src/KeyValueReader.h"

int main()
{
    printf("--- Test 1 (reading a file) ---\n");
    KeyValueReader kvr;
    KeyValueReader::Status status;
    
    
    // a
    kvr.setAbortOnError(false);
    status = kvr.readFile("test_does_not_exist.kv");
    if (status == KeyValueReader::StatusOpenFileError)
    	printf("   a: Passed\n");
    else
    	printf("   a: Failed\n");
    
    
    // b
    kvr.reset();
    kvr.setAbortOnError(false);
    status = kvr.readFile("test1a.kv");
    if (status == KeyValueReader::StatusSuccess)
    	printf("   b: Passed\n");
	else 
		printf("   b: Failed\n");
	
	
	// c
    status = kvr.readFile("test1b.kv");
    if (status == KeyValueReader::StatusAlreadyReadAFile)
    	printf("   c: Passed\n");
    else
    	printf("   c: Failed\n");
    
    
    return 0;
}
