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

#include "KeyValueReader.h"
#include <vector>
#include <fstream>
#include <stdio.h>

using namespace std;


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//                              Helper Functions
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


/*
    getRidOfComments
*/
static
void getRidOfComments(string &line)
{
    size_t commentStart = line.find('#');
    if (commentStart != string::npos)
        line = line.substr(0, commentStart);
}


/*
    deleteWhitespace
*/
static
size_t deleteWhitespace(string &line)
{
    static const string whitespace = " \t";
    size_t pos = 0;
    
    for (pos = 0; pos < line.size(); pos++) {
        if (whitespace.find(line[pos]) == string::npos) 
            break;
    }
    line = line.substr(pos);
    return pos;
}


/*
    areStringsEqual
*/
static
bool areStringsEqual(const string &s1, const string &s2)
{
    if (s1.size() != s2.size())
        return false;
    
    for (size_t i = 0; i < s1.size(); i++) {
        if(toupper(s1[i]) != toupper(s2[i]))
            return false;
    }
    
    return true;
}


/*
    popToken
*/
static
void popToken(string &line, string &token)
{
    static const string allowableChar = "abcdefghijklmnopqrstuvwxyz"
                                        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                        "0123456789"
                                        "+-_.";
    size_t pos = 0;
    token = "";
    
    for (pos = 0; pos < line.size(); pos++) {
        if (allowableChar.find(line[pos]) == string::npos) 
            break;
    }
    token = line.substr(0, pos);
    line = line.substr(pos);
}


/*
    parseLine
*/
static
bool parseLine(const string &line, string &outKey, string &outValue)
{
    string parsedLine = line;
    size_t numWhitespace = 0;
    string key = "";
    string value = "";
    
    // Get rid of comments in line
    getRidOfComments(parsedLine);
    
    // Delete whitespace
    deleteWhitespace(parsedLine);
    
    // Check for empty line
    if (parsedLine.size() == 0)
        return true;
    
    // Get key
    popToken(parsedLine, key);
    if (key == "") {
        return false;
    }
    
    // Delete whitespace
    numWhitespace = deleteWhitespace(parsedLine);
    if (numWhitespace == 0) {
        return false;
    }
    
    // Get value
    popToken(parsedLine, value);
    if (value == "") {
        return false;
    }
    
    // Delete whitespace
    deleteWhitespace(parsedLine);
    
    // Check for non-empty line
    if (parsedLine.size() != 0) {
        return false;
    }
    
    // If here, the line parsed correctly
    outKey = key;
    outValue = value;
    return true;
}


/*
    findKey
*/
static
int findKey(const vector<string> &keyVector, const string &key)
{
    for (size_t i = 0; i < keyVector.size(); i++) {
        if (areStringsEqual(key, keyVector[i])) {
            return i;
        }
    }
    
    return -1;
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//                              Private Class Data
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


/*
    PrivateData class
*/
struct KeyValueReader::Private
{
    void abortMessage(const string &message);
    
    vector<string> c_keyVector;
    vector<string> c_valueVector;
    bool c_isFileRead;
    bool c_willAbort;
    string c_filename;
};


/*
    abortMessage
*/
void KeyValueReader::Private::abortMessage(const string &message)
{
    if (!c_willAbort)
        return;
    
    printf("KeyValueReader error causing abort in file %s.\n",
           c_filename.c_str());
    printf("   %s\n", message.c_str());
    abort();
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//                              Class Implementation
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


/*
    Constructor/Destructor
*/
KeyValueReader::KeyValueReader()
{
    c_data = new Private();
    c_data->c_isFileRead = false;
    c_data->c_willAbort = true;
    c_data->c_filename = "";
}
KeyValueReader::~KeyValueReader()
{
    delete c_data;
}


/*
    readFile
*/
KeyValueReader::STATUS
KeyValueReader::readFile(const string &filename)
{
    ifstream file;
    std::string line = "";
    int lineNum = 1;
    STATUS status = StatusSuccess;
    
    
    // Check if already read a file
    if (c_data->c_isFileRead) {
        if (c_data->c_willAbort)
            c_data->abortMessage("Already read a file");
        return StatusAlreadyReadAFile;
    }
    
    
    // Open file
    c_data->c_filename = filename;
    file.open(filename);
    if (!file.is_open()) {
        if (c_data->c_willAbort)
            c_data->abortMessage("Could not open file");
        return StatusOpenFileError;
    }
    
    
    // Parse each line
    while (std::getline(file, line)) {
        string key = "";
        string value = "";
        bool parseOk = parseLine(line, key, value);
        
        if (!parseOk || findKey(c_data->c_keyVector, key) >= 0) {
            status = StatusParseFileError;
            printf("Parse error in file %s on line %d\n", filename.c_str(), lineNum);
        }
        else if (key != "") {
            c_data->c_keyVector.push_back(key);
            c_data->c_valueVector.push_back(value);
        }
        lineNum++;
    }
    
    // Close file and return
    file.close();
    if (c_data->c_willAbort && status != StatusSuccess)
        c_data->abortMessage("Parse line error");
    return status;
}


/*
    getString
*/
KeyValueReader::STATUS
KeyValueReader::getString(const std::string &key, std::string &value)
{
    for (size_t i = 0; i < c_data->c_keyVector.size(); i++) {
        if (areStringsEqual(key, c_data->c_keyVector[i])) {
            value = c_data->c_keyVector[i];
            return StatusSuccess;
        }
    }
    
    if (c_data->c_willAbort)
        c_data->abortMessage("Key not found");
    return StatusKeyNotFound;
}


/*
    getInt
*/
KeyValueReader::STATUS
KeyValueReader::getInt(const std::string &key, int &value)
{
    string valueString;
    STATUS status;
    
    status = getString(key, valueString);
    if (status != StatusSuccess) {
        value = 0;
        if (c_data->c_willAbort)
            c_data->abortMessage("Key not found");
        return status;
    }
    
    try {
        value = stoi(valueString);
    }
    catch (...) {
        value = 0;
        if (c_data->c_willAbort)
            c_data->abortMessage("Error converting value to int");
        return StatusStringConversionError;
    }
    
    return StatusSuccess;
}


/*
    getDouble
*/
KeyValueReader::STATUS
KeyValueReader::getDouble(const std::string &key, double &value)
{
    string valueString;
    STATUS status;
    
    status = getString(key, valueString);
    if (status != StatusSuccess) {
        value = 0;
        if (c_data->c_willAbort)
            c_data->abortMessage("Key not found");
        return status;
    }
    
    try {
        value = stod(valueString);
    }
    catch (...) {
        value = 0.0;
        if (c_data->c_willAbort)
            c_data->abortMessage("Error converting value to double");
        return StatusStringConversionError;
    }
    
    return StatusSuccess;
}


/*
    getFloat
*/
KeyValueReader::STATUS
KeyValueReader::getFloat(const std::string &key, float &value)
{
    string valueString;
    STATUS status;
    
    status = getString(key, valueString);
    if (status != StatusSuccess) {
        value = 0;
        if (c_data->c_willAbort)
            c_data->abortMessage("Key not found");
        return status;
    }
    
    try {
        value = stof(valueString);
    }
    catch (...) {
        value = 0.0f;
        if (c_data->c_willAbort)
            c_data->abortMessage("Error converting value to float");
        return StatusStringConversionError;
    }
    
    return StatusSuccess;
}


/*
    getBool
*/
KeyValueReader::STATUS
KeyValueReader::getBool(const std::string &key, bool &value)
{
    string valueString;
    STATUS status;
    
    // Get value from key as string
    status = getString(key, valueString);
    if (status != StatusSuccess) {
        value = 0;
        if (c_data->c_willAbort)
            c_data->abortMessage("Key not found");
        return status;
    }
    
    // Check for true
    if (areStringsEqual(valueString, "true")) {
        value = true;
        return StatusSuccess;
    }
    
    // Check for false
    if (areStringsEqual(valueString, "false")) {
        value = false;
        return StatusSuccess;
    }
    
    // String conversion error if we get here
    if (c_data->c_willAbort)
        c_data->abortMessage("Error converting value to bool");
    return StatusStringConversionError;
}


/*
    print
*/
void KeyValueReader::print()
{
    printf("\n--- KeyValueReader Data (%s) ---\n", c_data->c_filename.c_str());
    for (size_t i = 0; i < c_data->c_keyVector.size(); i++) {
        printf("    %s %s\n", c_data->c_keyVector[i].c_str(), 
                              c_data->c_valueVector[i].c_str());
    }
    printf("\n");
}


/*
    setAbortOnError
*/
void KeyValueReader::setAbortOnError(bool willAbort)
{
    c_data->c_willAbort = willAbort;
}



