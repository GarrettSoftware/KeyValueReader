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

#ifndef __KEY_VALUE_READER_H
#define __KEY_VALUE_READER_H


enum KVR_Status {
    KVR_Success,
    KVR_AlreadyReadAFile,
    KVR_FileNotRead,
    KVR_OpenFileError,
    KVR_ParseFileError,
    KVR_KeyNotFound,
    KVR_ConversionError,
};


void *KVR_create();
void KVR_delete(
    void *kvr);

KVR_Status KVR_readFile(
    void *kvr, 
    const char *filename);
KVR_Status KVR_getString(
    const void *kvr, 
    const char *key, 
    char *value);
KVR_Status KVR_getInt(
    const void *kvr, 
    const char *key, 
    int &value);
KVR_Status KVR_getDouble(
    const void *kvr, 
    const char *key, 
    double &value);
KVR_Status KVR_getFloat(
    const void *kvr, 
    const char *key, 
    float &value);
KVR_Status KVR_getBool(
    const void *kvr, 
    const char *key, 
    bool &value);
KVR_Status KVR_print(
    const void *kvr); 


#endif
