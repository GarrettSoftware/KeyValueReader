/*
The MIT License (MIT)

Copyright (c) 2016 C. Kristopher Garrett

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

#ifndef __KEY_VALUE_READER_C_H
#define __KEY_VALUE_READER_C_H

#ifdef __cplusplus
extern "C" {
#endif

enum KVR_Error {
    KVR_Error_None,
    KVR_Error_AlreadyReadAFile,
    KVR_Error_FileNotRead,
    KVR_Error_OpenFileError,
    KVR_Error_ParseFileError,
    KVR_Error_KeyNotFound,
    KVR_Error_StringConversionError,
};

void* KVR_createKeyValueReader();
void KVR_deleteKeyValueReader(void *kvr);

KVR_Error KVR_readFile(void *kvr, const char *filename);
KVR_Error KVR_getString(void *kvr, const char *key, char *value);
KVR_Error KVR_getInt(void *kvr, const char *key, int *value);
KVR_Error KVR_getDouble(void *kvr, const char *key, double *value);
KVR_Error KVR_getFloat(void *kvr, const char *key, float *value);
KVR_Error KVR_getBool(void *kvr, const char *key, int *value);
KVR_Error KVR_print();
KVR_Error KVR_reset();

#ifdef __cplusplus
}
#endif

#endif

