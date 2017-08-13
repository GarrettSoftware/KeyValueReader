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

#include <string>
#include <vector>

enum KVR_Error {
    KVR_Error_None,
    KVR_Error_AlreadyReadAFile,
    KVR_Error_FileNotRead,
    KVR_Error_OpenFileError,
    KVR_Error_ParseFileError,
    KVR_Error_KeyNotFound,
    KVR_Error_StringConversionError,
};


class KeyValueReader 
{
public:
    
    // Constructor
    KeyValueReader();
    
        
//private:
    std::vector<std::string> c_keyVector;
    std::vector<std::string> c_valueVector;
    bool c_isFileRead;
    std::string c_filename;

    void printMessage(const std::string &message) const;
    KVR_Error getStringPrivate(const char *key, std::string &value) const;
};

void *createKeyValueReader();
void deleteKeyValueReader(
    void *kvr);

// Interface
KVR_Error readFile(
    void *kvr, 
    const char *filename);
KVR_Error getString(
    const void *kvr, 
    const char *key, 
    char *value);
KVR_Error getInt(
    const void *kvr, 
    const char *key, 
    int &value);
KVR_Error getDouble(
    const void *kvr, 
    const char *key, 
    double &value);
KVR_Error getFloat(
    const void *kvr, 
    const char *key, 
    float &value);
KVR_Error getBool(
    const void *kvr, 
    const char *key, 
    bool &value);
KVR_Error print(
    const void *kvr); 


#endif
