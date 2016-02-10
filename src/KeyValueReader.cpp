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

static const int KEY_NOT_FOUND = -1;


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//                              Helper Functions
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


/*
    getRidOfComments
    
    Deletes # and everything after that in the string.
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
    
    Deletes all the initial whitespace in the string.
    Returns number of whitespace characters.
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
    
    Returns true if the two strings are equal.
    Neglects upper/lower case.
*/
static
bool areStringsEqual(const string &s1, const string &s2)
{
    if (s1.size() != s2.size())
        return false;
    
    for (size_t i = 0; i < s1.size(); i++) {
        if (toupper(s1[i]) != toupper(s2[i]))
            return false;
    }
    
    return true;
}


/*
    popToken
    
    A token is made up of a-z, A-z, 0-9, and {+,-,_,.}.
    Takes the token out of 'line' and puts it in 'token'.
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
    
    From a line of input, sets outKey and outValue.
    If the line parses correctly, function returns true.
    Otherwise function returns false.
    
    In the case of true return and the line contains a key/value pair, outKey and
    outValue contain that data.
    In the case of true return and the line contains only whitespace or comments,
    outKey and outValue are set to "".
    In the case of false return, outKey and outValue are set to "".
*/
static
bool parseLine(const string &line, string &outKey, string &outValue)
{
    string parsedLine = line;
    size_t numWhitespace = 0;
    string key = "";
    string value = "";
    
    // Set outKey, outValue to default ""
    outKey = "";
    outValue = "";
    
    // Get rid of comments in line
    getRidOfComments(parsedLine);
    
    // Delete whitespace
    deleteWhitespace(parsedLine);
    
    // Check for empty line
    if (parsedLine.size() == 0) {
        return true;
    }
    
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
    
    Returns the index of the key in the keyVector.
    If key is not found, returns KEY_NOT_FOUND.
*/
static
int findKey(const vector<string> &keyVector, const string &key)
{
    for (size_t i = 0; i < keyVector.size(); i++) {
        if (areStringsEqual(key, keyVector[i])) {
            return i;
        }
    }
    
    return KEY_NOT_FOUND;
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
    
    Causes an abort of the program due to an error.
*/
void KeyValueReader::Private::abortMessage(const string &message)
{
    if (!c_willAbort) {
    	if (message != "")
    		printf("   %s\n", message.c_str());
        return;
    }
    
    printf("KeyValueReader error causing abort in file %s.\n",
           c_filename.c_str());
    if (message != "")
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
    reset();
}
KeyValueReader::~KeyValueReader()
{
    delete c_data;
}


/*
    readFile
    
    Reads in a key-value file.
    Returns status of success or failure.
*/
KeyValueReader::Status
KeyValueReader::readFile(const string &filename)
{
    ifstream file;
    std::string line = "";
    int lineNum = 1;
    Status status = StatusSuccess;
    
    
    // Check if already read a file
    if (c_data->c_isFileRead) {
        c_data->abortMessage("Already read a file");
        return StatusAlreadyReadAFile;
    }
    
    
    // Open file
    c_data->c_filename = filename;
    file.open(filename);
    if (!file.is_open()) {
        c_data->abortMessage("Could not open file");
        return StatusOpenFileError;
    }
    
    
    // Parse each line
    while (std::getline(file, line)) {
        string key = "";
        string value = "";
        bool parseOk = parseLine(line, key, value);
        
        if (!parseOk) {
            status = StatusParseFileError;
            printf("   Parse error in file %s on line %d\n", filename.c_str(), lineNum);
        }
        else if (findKey(c_data->c_keyVector, key) != KEY_NOT_FOUND) {
        	status = StatusParseFileError;
            printf("   Duplicate key in file %s on line %d\n", filename.c_str(), lineNum);
        }
        else if (key != "") {
            c_data->c_keyVector.push_back(key);
            c_data->c_valueVector.push_back(value);
        }
        lineNum++;
    }
    
    
    // Close file and return
    file.close();
    if (status != StatusSuccess)
        c_data->abortMessage("");
    c_data->c_isFileRead = true;
    return status;
}


/*
    getString
    
    Gets string value from key.
    Returns status of success or failure.
    If an error occurs, value is set to "".
*/
KeyValueReader::Status
KeyValueReader::getString(const std::string &key, std::string &value)
{
	int keyIndex;
	
	// Default value
    value = "";
	
	// Check for file read
    if (!c_data->c_isFileRead) {
    	c_data->abortMessage("File not read.");
    	return StatusFileNotRead;
    }
    
    // Find value from key
    keyIndex = findKey(c_data->c_keyVector, key);
    if (keyIndex == KEY_NOT_FOUND) {
    	c_data->abortMessage("Key not found");
    	return StatusKeyNotFound;
    }
    
    value = c_data->c_valueVector[keyIndex];
    return StatusSuccess;
}


/*
    getInt
    
    Gets integer value from key.
    Returns status of success or failure.
    If an error occurs, value is set to zero.
*/
KeyValueReader::Status
KeyValueReader::getInt(const std::string &key, int &value)
{
    string valueString;
    Status status;
    
    // Default value
    value = 0;
    
    // Check for file read
    if (!c_data->c_isFileRead) {
    	c_data->abortMessage("File not read.");
    	return StatusFileNotRead;
    }
    
    // Get value as string
    status = getString(key, valueString);
    if (status != StatusSuccess) {
        return status;
    }
    
    // Convert to int
    try {
        value = stoi(valueString);
    }
    catch (...) {
        c_data->abortMessage("Error converting value to int");
        return StatusStringConversionError;
    }
    
    return StatusSuccess;
}


/*
    getDouble
    
    Gets double value from key.
    Returns status of success or failure.
    If an error occurs, value is set to zero.
*/
KeyValueReader::Status
KeyValueReader::getDouble(const std::string &key, double &value)
{
    string valueString;
    Status status;
    
    // Default value
    value = 0.0;
    
    // Check for file read
    if (!c_data->c_isFileRead) {
    	c_data->abortMessage("File not read.");
    	return StatusFileNotRead;
    }
    
    // Get value as string
    status = getString(key, valueString);
    if (status != StatusSuccess) {
        return status;
    }
    
    // Convert to double
    try {
        value = stod(valueString);
    }
    catch (...) {
        c_data->abortMessage("Error converting value to double");
        return StatusStringConversionError;
    }
    
    return StatusSuccess;
}


/*
    getFloat
    
    Gets float value from key.
    Returns status of success or failure.
    If an error occurs, value is set to zero.
*/
KeyValueReader::Status
KeyValueReader::getFloat(const std::string &key, float &value)
{
    string valueString;
    Status status;
    
    // Default value
    value = 0.0f;
    
    // Check for file read
    if (!c_data->c_isFileRead) {
    	c_data->abortMessage("File not read.");
    	return StatusFileNotRead;
    }
    
    // Get value as string
    status = getString(key, valueString);
    if (status != StatusSuccess) {
        return status;
    }
    
    // Convert value to float
    try {
        value = stof(valueString);
    }
    catch (...) {
        c_data->abortMessage("Error converting value to float");
        return StatusStringConversionError;
    }
    
    return StatusSuccess;
}


/*
    getBool
    
    Gets boolean value from key.
    Returns status of success or failure.
    If an error occurs, value is set to false.
*/
KeyValueReader::Status
KeyValueReader::getBool(const std::string &key, bool &value)
{
    string valueString;
    Status status;
    
    // Default value
    value = false;
    
    // Check for file read
    if (!c_data->c_isFileRead) {
    	c_data->abortMessage("File not read.");
    	return StatusFileNotRead;
    }
    
    // Get value from key as string
    status = getString(key, valueString);
    if (status != StatusSuccess) {
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
    c_data->abortMessage("Error converting value to bool");
    return StatusStringConversionError;
}


/*
    print
    
    Prints entire set of key/value pairs.
*/
void KeyValueReader::print()
{
    printf("\n--- KeyValueReader Data (%s) ---\n", c_data->c_filename.c_str());
    
    // Check for file read
    if (!c_data->c_isFileRead) {
    	printf("No file has been read.\n\n");
    	return;
    }
    
    // Print KeyValueReader data
    for (size_t i = 0; i < c_data->c_keyVector.size(); i++) {
        printf("    %s %s\n", c_data->c_keyVector[i].c_str(), 
                              c_data->c_valueVector[i].c_str());
    }
    printf("\n");
}


/*
    setAbortOnError
    
    Sets whether the KeyValueReader will abort the program if an error is detected.
*/
void KeyValueReader::setAbortOnError(bool willAbort)
{
    c_data->c_willAbort = willAbort;
}


/*
    reset
    
    Resets the KeyValueReader to an uninitialized state.
*/
void KeyValueReader::reset()
{
	c_data->c_isFileRead = false;
    c_data->c_willAbort = true;
    c_data->c_filename = "";
    c_data->c_keyVector.clear();
    c_data->c_valueVector.clear();
}



