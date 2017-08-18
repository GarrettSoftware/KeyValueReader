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

#ifndef __KEY_VALUE_READER_H
#define __KEY_VALUE_READER_H

#ifdef __cplusplus
extern "C" {
#endif

enum KVR_Status {
    KVR_Success,
    KVR_CannotReadSecondFile,
    KVR_FileNotRead,
    KVR_OpenFileError,
    KVR_ParseFileError,
    KVR_KeyNotFound,
    KVR_ConversionError,
    KVR_AllocationError
};


/*
    Create/delete KeyValueReader strucuture.
*/
enum KVR_Status KVR_create(
    void **kvr);
enum KVR_Status KVR_delete(
    void **kvr);

/*
    Parse key/value file and store the data.
*/
enum KVR_Status KVR_readFile(
    void *kvr, 
    const char *filename);

/*
    Get the maximum length in characters of all values.
    Useful before using KVR_getString to know how large to 
    make value char array.
*/
enum KVR_Status KVR_getMaxValueLength(
    const void *kvr,
    int *length);

/*
    Get value from key.
*/
enum KVR_Status KVR_getString(
    const void *kvr, 
    const char *key, 
    char *value);
enum KVR_Status KVR_getInt(
    const void *kvr, 
    const char *key, 
    int *value);
enum KVR_Status KVR_getDouble(
    const void *kvr, 
    const char *key, 
    double *value);
enum KVR_Status KVR_getFloat(
    const void *kvr, 
    const char *key, 
    float *value);
enum KVR_Status KVR_getBool(
    const void *kvr, 
    const char *key, 
    int *value);

/*
    Print the contents of all keys/values.
*/
enum KVR_Status KVR_print(
    const void *kvr); 

#ifdef __cplusplus
}
#endif

#endif

