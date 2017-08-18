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

#include "utils.h"

using namespace std;

/*
    deleteComments
    
    Deletes # and everything after that in the string.
*/
static void deleteComments(
    std::string &line)
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
static size_t deleteWhitespace(
    std::string &line)
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
    popToken
    
    A token is made up of a-z, A-Z, 0-9, and {+,-,_,.}.
    Takes the token out of 'line' and puts it in 'token'.
*/
static void popToken(
    std::string &line, 
    std::string &token)
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


namespace KVR_UTILS {

/*
    printMessage
    
    Prints message and key/value file name in a standard way.
*/
void printMessage(
    const std::string &filename, 
    const std::string &message)
{
    printf("KeyValueReader error in file %s\n", filename.c_str());
    printf("   %s\n", message.c_str());
}


/*
    areStringsEqual
    
    Returns true if the two strings are equal.
    Neglects upper/lower case.
*/
bool areStringsEqual(
    const std::string &s1, 
    const std::string &s2)
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
bool parseLine(
    const std::string &line, 
    std::string &outKey, 
    std::string &outValue)
{
    string parsedLine = line;
    size_t numWhitespace = 0;
    string key = "";
    string value = "";
    
    // Set outKey, outValue to default ""
    outKey = "";
    outValue = "";
    
    // Get rid of comments in line
    deleteComments(parsedLine);
    
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
int findKey(
    const std::vector<std::string> &keyVector, 
    const std::string &key)
{
    for (size_t i = 0; i < keyVector.size(); i++) {
        if (areStringsEqual(key, keyVector[i])) {
            return i;
        }
    }
    
    return KEY_NOT_FOUND;
}

} // End KVR_UTILS namespace
