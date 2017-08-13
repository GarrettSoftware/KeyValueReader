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

#include "../include/KeyValueReader.h"
#include "utils.h"
#include <vector>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;



/*
    printMessage
    
    Causes an abort of the program due to an error.
*/
void KeyValueReader::printMessage(
    const std::string &message) const
{
    printf("KeyValueReader error in file %s\n", c_filename.c_str());
    printf("   %s\n", message.c_str());
}


/*
    Constructor
*/
KeyValueReader::KeyValueReader()
{
    c_isFileRead = false;
    c_filename = "";
    c_keyVector.clear();
    c_valueVector.clear();
}


/*
    getStringPrivate
    
    Gets string value from key.
    Throws an error if appropriate.
    If an error occurs, value is set to "".
*/
KVR_Error KeyValueReader::getStringPrivate(
    const char *key, 
    std::string &value) const
{
    int keyIndex = 0;
	
    // Default value
    value = "";
	
    // Check for file read
    if (!c_isFileRead) {
    	printMessage("File not read.");
        return KVR_Error_FileNotRead;
    }
    
    // Find value from key
    keyIndex = findKey(c_keyVector, key);
    if (keyIndex == KEY_NOT_FOUND) {
    	printMessage("Key not found");
        return KVR_Error_KeyNotFound;
    }
    
    value = c_valueVector[keyIndex];
    return KVR_Error_None;
}


/*
    readFile
    
    Reads in a key-value file.
    Throws an error if appropriate.
*/
KVR_Error readFile(
    void *kvrVoid, 
    const char *filename)
{
    KeyValueReader *kvr = static_cast<KeyValueReader*>(kvrVoid);
    ifstream file;
    string line = "";
    int lineNum = 1;
    bool totalParseOk = true;
    string oldFilename = kvr->c_filename;
    
    
    // Set filename (used in printMessage)
    kvr->c_filename = filename;
    
    
    // Check if already read a file
    if (kvr->c_isFileRead) {
        kvr->printMessage("Already read a file");
        kvr->c_filename = oldFilename;
        return KVR_Error_AlreadyReadAFile;
    }
    
    
    // Open file
    file.open(filename);
    if (!file.is_open()) {
        kvr->printMessage("Could not open file");
        kvr->c_filename = oldFilename;
        return KVR_Error_OpenFileError;
    }
    
    
    // Parse each line
    while (std::getline(file, line)) {
        string key = "";
        string value = "";
        bool parseOk = parseLine(line, key, value);
        
        // Check parse is ok
        if (!parseOk) {
            totalParseOk = false;
            string errorString = "Parse error on line ";
            errorString += to_string(lineNum);
            kvr->printMessage(errorString);
        }
        
        // Check if duplicate key
        else if (findKey(kvr->c_keyVector, key) != KEY_NOT_FOUND) {
            totalParseOk = false;
            string errorString = "Duplicate key on line ";
            errorString += to_string(lineNum);
            kvr->printMessage(errorString);
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
        return KVR_Error_ParseFileError;

    return KVR_Error_None;
}


void *createKeyValueReader()
{
    return new KeyValueReader();
}


void deleteKeyValueReader(
    void *kvrVoid)
{
    KeyValueReader *kvr = static_cast<KeyValueReader*>(kvrVoid);
    delete kvr;
}


/*
    getString
    
    Gets string value from key.
    Throws an error if appropriate.
    If an error occurs, value is set to "".
*/
KVR_Error getString(
    const void *kvrVoid, 
    const char *key, 
    char *value)
{
    const KeyValueReader *kvr = static_cast<const KeyValueReader*>(kvrVoid);
    string valueString;
    
    // Default value
    value[0] = 0;
    
    // Get value as string
    KVR_Error error = kvr->getStringPrivate(key, valueString);
    if (error != KVR_Error_None)
        return error;
    
    // Copy string into char array
    strcpy(value, valueString.c_str());

    return KVR_Error_None;
}


/*
    getInt
    
    Gets integer value from key.
    Throws an error if appropriate.
    If an error occurs, value is set to zero.
*/
KVR_Error getInt(
    const void *kvrVoid, 
    const char *key, 
    int &value)
{
    const KeyValueReader *kvr = static_cast<const KeyValueReader*>(kvrVoid);
    string valueString;
    
    // Default value
    value = 0;
    
    // Get value as string
    KVR_Error error = kvr->getStringPrivate(key, valueString);
    if (error != KVR_Error_None)
        return error;
    
    // Convert to int
    try {
        value = stoi(valueString);
    }
    catch (...) {
        kvr->printMessage("Error converting value to int");
        //throw ExceptionStringConversionError;
        return KVR_Error_StringConversionError;
    }

    return KVR_Error_None;
}


/*
    getDouble
    
    Gets double value from key.
    Throws an error if appropriate.
    If an error occurs, value is set to zero.
*/
KVR_Error getDouble(
    const void *kvrVoid, 
    const char *key, 
    double &value)
{
    const KeyValueReader *kvr = static_cast<const KeyValueReader*>(kvrVoid);
    string valueString;
    
    // Default value
    value = 0.0;
    
    // Get value as string
    KVR_Error error = kvr->getStringPrivate(key, valueString);
    if (error != KVR_Error_None)
        return error;
    
    // Convert to double
    try {
        value = stod(valueString);
    }
    catch (...) {
        kvr->printMessage("Error converting value to double");
        //throw ExceptionStringConversionError;
        return KVR_Error_StringConversionError;
    }

    return KVR_Error_None;
}


/*
    getFloat
    
    Gets float value from key.
    Throws an error if appropriate.
    If an error occurs, value is set to zero.
*/
KVR_Error getFloat(
    const void *kvrVoid, 
    const char *key, 
    float &value)
{
    const KeyValueReader *kvr = static_cast<const KeyValueReader*>(kvrVoid);
    string valueString;
    
    // Default value
    value = 0.0f;
    
    // Get value as string
    KVR_Error error = kvr->getStringPrivate(key, valueString);
    if (error != KVR_Error_None)
        return error;
    
    // Convert value to float
    try {
        value = stof(valueString);
    }
    catch (...) {
        kvr->printMessage("Error converting value to float");
        //throw ExceptionStringConversionError;
        return KVR_Error_StringConversionError;
    }

    return KVR_Error_None;
}


/*
    getBool
    
    Gets boolean value from key.
    Throws an error if appropriate.
    If an error occurs, value is set to false.
*/
KVR_Error getBool(
    const void *kvrVoid, 
    const char *key, 
    bool &value)
{
    const KeyValueReader *kvr = static_cast<const KeyValueReader*>(kvrVoid);
    string valueString;
    
    // Default value
    value = false;
    
    // Get value from key as string
    KVR_Error error = kvr->getStringPrivate(key, valueString);
    if (error != KVR_Error_None)
        return error;
    
    // Check for true
    if (areStringsEqual(valueString, "true")) {
        value = true;
        //return;
        return KVR_Error_None;
    }
    
    // Check for false
    if (areStringsEqual(valueString, "false")) {
        value = false;
        //return;
        return KVR_Error_None;
    }
    
    // String conversion error if we get here
    kvr->printMessage("Error converting value to bool");
    return KVR_Error_StringConversionError;
}


/*
    print
    
    Prints entire set of key/value pairs.
    Throws an error if appropriate.
*/
KVR_Error print(
    const void *kvrVoid)
{
    const KeyValueReader *kvr = static_cast<const KeyValueReader*>(kvrVoid);
    printf("\n--- KeyValueReader Data (%s) ---\n", kvr->c_filename.c_str());
    
    // Check for file read
    if (!kvr->c_isFileRead) {
    	kvr->printMessage("File not read.");
        return KVR_Error_FileNotRead;
    }
    
    // Print KeyValueReader data
    for (size_t i = 0; i < kvr->c_keyVector.size(); i++) {
        printf("    %s %s\n", kvr->c_keyVector[i].c_str(), 
                              kvr->c_valueVector[i].c_str());
    }
    printf("\n");
    
    return KVR_Error_None;
}



