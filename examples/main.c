/*
The MIT License (MIT)

Copyright (c) 2016-2017 C. Kristopher Garrett

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "../include/KeyValueReader.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    void *kvr = NULL;
    int maxStringLength = 0;
    char *method;
    int nx;
    double dt;
    int doExtraStuff;

    // Create the Key/Value reader and read in file
    KVR_create(&kvr);
    KVR_readFile(kvr, "input.kv");

    // Get max string length necessary to hold values
    KVR_getMaxValueLength(kvr, &maxStringLength);
    method = malloc(maxStringLength);

    // Get parameters of different types
    KVR_getString(kvr, "method", method);
    KVR_getInt(kvr, "nx", &nx);
    KVR_getDouble(kvr, "dt", &dt);
    KVR_getBool(kvr, "doExtraStuff", &doExtraStuff);

    // Print the values that I got
    printf("\nValues from the Key/Value reader\n");
    printf("Method: %s\n", method);
    printf("nx:     %d\n", nx);
    printf("dt:     %f\n", dt);
    printf("extra:  %s\n", doExtraStuff ? "true" : "false");

    // Print the Key/Value pairs from the file
    KVR_print(kvr);

    // Cleanup
    free(method);
    KVR_delete(&kvr);
    return 0;
}

