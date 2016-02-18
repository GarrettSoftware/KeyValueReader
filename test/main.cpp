#include <stdio.h>

bool test1();

int main()
{
    bool result1 = test1();
    
    
    printf("\n\n*** TEST RESULTS ***\n");
    if(result1 == false)
        printf("   Test 1: failed\n");
    else
        printf("   Test 1: passed\n");
    
    return 0;
}