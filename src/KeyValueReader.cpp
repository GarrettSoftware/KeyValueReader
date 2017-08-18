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
#include "utils.h"
#include <vector>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;


/*
    KeyValueReader data
*/
namespace {
struct KVR_Data
{
    vector<string> c_keyVector;
    vector<string> c_valueVector;
    bool c_isFileRead;
    string c_filename;
};}


/*
    getStringPrivate
    
    Gets string value from key.
    If an error occurs, value is set to "".
*/
static
KVR_Status getStringPrivate(
    const KVR_Data *kvr, 
    const char *key, 
    std::string &value)
{
    int keyIndex = 0;
	
    // Default value
    value = "";
	
    // Check for file read
    if (!kvr->c_isFileRead) {
    	KVR_UTILS::printMessage(kvr->c_filename, "File not read.");
        return KVR_FileNotRead;
    }
    
    // Find value from key
    keyIndex = KVR_UTILS::findKey(kvr->c_keyVector, key);
    if (keyIndex == KVR_UTILS::KEY_NOT_FOUND) {
    	KVR_UTILS::printMessage(kvr->c_filename, "Key not found");
        return KVR_KeyNotFound;
    }
    
    value = kvr->c_valueVector[keyIndex];
    return KVR_Success;
}


// Public C interface
extern "C" {

/*
    KVR_readFile
*/
enum KVR_Status KVR_readFile(
    void *kvrVoid, 
    const char *filename)
{
    KVR_Data *kvr = static_cast<KVR_Data*>(kvrVoid);
    ifstream file;
    string line = "";
    int lineNum = 1;
    bool totalParseOk = true;
    
    
    // Check if already read a file
    if (kvr->c_isFileRead) {
        KVR_UTILS::printMessage(filename, "Cannot read a second file");
        return KVR_CannotReadSecondFile;
    }
    
    
    // Open file
    file.open(filename);
    if (!file.is_open()) {
        KVR_UTILS::printMessage(filename, "Could not open file");
        return KVR_OpenFileError;
    }
    kvr->c_filename = filename;
    
    
    // Parse each line
    while (std::getline(file, line)) {
        string key = "";
        string value = "";
        bool parseOk = KVR_UTILS::parseLine(line, key, value);
        
        // Check parse is ok
        if (!parseOk) {
            totalParseOk = false;
            string errorString = "Parse error on line ";
            errorString += to_string(lineNum);
            KVR_UTILS::printMessage(kvr->c_filename, errorString);
        }
        
        // Check if duplicate key
        else if (KVR_UTILS::findKey(kvr->c_keyVector, key) != 
                 KVR_UTILS::KEY_NOT_FOUND)
        {
            totalParseOk = false;
            string errorString = "Duplicate key on line ";
            errorString += to_string(lineNum);
            KVR_UTILS::printMessage(kvr->c_filename, errorString);
        }
        
        // Add key/value if line had one
        else if (key != "") {
            kvr->c_keyVector.push_back(key);
            kvr->c_valueVector.push_back(value);
        }
        lineNum++;
    }
    
    
    // Close file and return
    file.close();
    kvr->c_isFileRead = true;
    
    if (!totalParseOk)
        return KVR_ParseFileError;

    return KVR_Success;
}


/*
    KVR_create
*/
enum KVR_Status KVR_create(
    void **kvrVoid)
{
    // Allocate kvr data
    KVR_Data *kvr;
    try {
        kvr = new KVR_Data();
    } catch(...) {
        kvrVoid = NULL;
        return KVR_AllocationError;
    }
    
    // Set the kvr data
    kvr->c_isFileRead = false;
    kvr->c_filename = "";
    kvr->c_keyVector.clear();
    kvr->c_valueVector.clear();
    
    // Return
    *kvrVoid = kvr;
    return KVR_Success;
}


/*
    KVR_delete
*/
enum KVR_Status KVR_delete(
    void **kvrVoid)
{
    KVR_Data *kvr = static_cast<KVR_Data*>(*kvrVoid);
    delete kvr;
    kvrVoid = NULL;
    return KVR_Success;
}


/*
    getString
    
    If an error occurs, value is set to "".
*/
enum KVR_Status KVR_getString(
    const void *kvrVoid, 
    const char *key, 
    char *value)
{
    const KVR_Data *kvr = static_cast<const KVR_Data*>(kvrVoid);
    string valueString;
    
    // Default value
    value[0] = 0;
    
    // Get value as string
    KVR_Status error = getStringPrivate(kvr, key, valueString);
    if (error != KVR_Success)
        return error;
    
    // Copy string into char array
    strcpy(value, valueString.c_str());

    return KVR_Success;
}


/*
    getInt
    
    If an error occurs, value is set to zero.
*/
enum KVR_Status KVR_getInt(
    const void *kvrVoid, 
    const char *key, 
    int *value)
{
    const KVR_Data *kvr = static_cast<const KVR_Data*>(kvrVoid);
    string valueString;
    
    // Default value
    *value = 0;
    
    // Get value as string
    KVR_Status error = getStringPrivate(kvr, key, valueString);
    if (error != KVR_Success)
        return error;
    
    // Convert to int
    try {
        *value = stoi(valueString);
    }
    catch (...) {
        KVR_UTILS::printMessage(
            kvr->c_filename, "Error converting value to int");
        return KVR_ConversionError;
    }

    return KVR_Success;
}


/*
    getDouble
    
    If an error occurs, value is set to zero.
*/
enum KVR_Status KVR_getDouble(
    const void *kvrVoid, 
    const char *key, 
    double *value)
{
    const KVR_Data *kvr = static_cast<const KVR_Data*>(kvrVoid);
    string valueString;
    
    // Default value
    *value = 0.0;
    
    // Get value as string
    KVR_Status error = getStringPrivate(kvr, key, valueString);
    if (error != KVR_Success)
        return error;
    
    // Convert to double
    try {
        *value = stod(valueString);
    }
    catch (...) {
        KVR_UTILS::printMessage(
            kvr->c_filename, "Error converting value to double");
        return KVR_ConversionError;
    }

    return KVR_Success;
}


/*
    getFloat
    
    If an error occurs, value is set to zero.
*/
enum KVR_Status KVR_getFloat(
    const void *kvrVoid, 
    const char *key, 
    float *value)
{
    const KVR_Data *kvr = static_cast<const KVR_Data*>(kvrVoid);
    string valueString;
    
    // Default value
    *value = 0.0f;
    
    // Get value as string
    KVR_Status error = getStringPrivate(kvr, key, valueString);
    if (error != KVR_Success)
        return error;
    
    // Convert value to float
    try {
        *value = stof(valueString);
    }
    catch (...) {
        KVR_UTILS::printMessage(
            kvr->c_filename, "Error converting value to float");
        return KVR_ConversionError;
    }

    return KVR_Success;
}


/*
    getBool
    
    If an error occurs, value is set to false.
*/
enum KVR_Status KVR_getBool(
    const void *kvrVoid, 
    const char *key, 
    int *value)
{
    const KVR_Data *kvr = static_cast<const KVR_Data*>(kvrVoid);
    string valueString;
    
    // Default value
    *value = 0;
    
    // Get value from key as string
    KVR_Status error = getStringPrivate(kvr, key, valueString);
    if (error != KVR_Success)
        return error;
    
    // Check for true
    if (KVR_UTILS::areStringsEqual(valueString, "true")) {
        *value = 1;
        return KVR_Success;
    }
    
    // Check for false
    if (KVR_UTILS::areStringsEqual(valueString, "false")) {
        *value = 0;
        return KVR_Success;
    }
    
    // String conversion error if we get here
    KVR_UTILS::printMessage(
        kvr->c_filename, "Error converting value to bool");
    return KVR_ConversionError;
}


/*
    print
*/
enum KVR_Status KVR_print(
    const void *kvrVoid)
{
    const KVR_Data *kvr = static_cast<const KVR_Data*>(kvrVoid);
    
    // Check for file read
    if (!kvr->c_isFileRead) {
    	KVR_UTILS::printMessage(kvr->c_filename, "File not read.");
        return KVR_FileNotRead;
    }
    
    // Print KeyValueReader data
    printf("\n--- KeyValueReader Data (%s) ---\n", kvr->c_filename.c_str());
    for (size_t i = 0; i < kvr->c_keyVector.size(); i++) {
        printf("    %s %s\n", kvr->c_keyVector[i].c_str(), 
                              kvr->c_valueVector[i].c_str());
    }
    printf("\n");
    
    return KVR_Success;
}


/*
    KVR_getMaxValueLength
*/
enum KVR_Status KVR_getMaxValueLength(
    const void *kvrVoid,
    int *length)
{
    const KVR_Data *kvr = static_cast<const KVR_Data*>(kvrVoid);
    *length = 0;
    
    // Check for file read
    if (!kvr->c_isFileRead) {
    	KVR_UTILS::printMessage(kvr->c_filename, "File not read.");
        return KVR_FileNotRead;
    }
    
    // Print KeyValueReader data
    for (size_t i = 0; i < kvr->c_keyVector.size(); i++) {
        if (*length < (int)kvr->c_valueVector[i].size())
            *length = kvr->c_valueVector[i].size();
    }
    
    // Add 1 to length for null terminator of C strings
    *length = *length + 1;

    return KVR_Success;
}

} // End extern "C"


