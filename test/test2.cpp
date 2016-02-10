#include "../src/KeyValueReader.h"

int main()
{
    printf("--- Test 2 (parsing) ---\n");
    KeyValueReader kvr;
    KeyValueReader::Status status;
    
    
    // a
    kvr.setAbortOnError(false);
    status = kvr.readFile("test2a.kv");
    if (status == KeyValueReader::StatusSuccess)
    	printf("a: Passed\n");
    else
    	printf("a: Failed\n");
    
    
    // b
    kvr.reset();
    kvr.setAbortOnError(false);
    status = kvr.readFile("test2b.kv");
    if (status == KeyValueReader::StatusParseFileError)
    	printf("b: Passed\n");
	else 
		printf("b: Failed\n");
	
	
	// c
	kvr.reset();
    kvr.setAbortOnError(false);
    status = kvr.readFile("test2c.kv");
    if (status == KeyValueReader::StatusParseFileError)
    	printf("c: Passed\n");
	else 
		printf("c: Failed\n");
	
	
	// d
	kvr.reset();
    kvr.setAbortOnError(false);
    status = kvr.readFile("test2d.kv");
    if (status == KeyValueReader::StatusParseFileError)
    	printf("d: Passed\n");
	else 
		printf("d: Failed\n");
    
    
    return 0;
}
