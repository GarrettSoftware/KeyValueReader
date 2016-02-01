#include "KeyValueReader.h"
#include <vector>
#include <fstream>
#include <stdio.h>

using namespace std;


/*
    PrivateData class
*/
class KeyValueReader::Private
{
public:
    bool parseLine(const int lineNum, const string &filename, const string &line);
    
    vector<string> keyVector;
    vector<string> valueVector;
    bool isFileRead;
};


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
    convertToUpperCase
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
bool KeyValueReader::Private::parseLine(const int lineNum, 
                                        const string &filename,
                                        const string &line)
{
    string parsedLine = line;
    string key = "";
    string value = "";
    size_t numWhitespace;
    
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
        printf("Parse error in file %s on line %d\n", filename.c_str(), lineNum);
        return false;
    }
    
    // Delete whitespace
    numWhitespace = deleteWhitespace(parsedLine);
    if (numWhitespace == 0) {
        printf("Parse error in file %s on line %d\n", filename.c_str(), lineNum);
        return false;
    }
    
    // Get value
    popToken(parsedLine, value);
    if (value == "") {
        printf("Parse error in file %s on line %d\n", filename.c_str(), lineNum);
        return false;
    }
    
    // Delete whitespace
    deleteWhitespace(parsedLine);
    
    // Check for non-empty line
    if (parsedLine.size() != 0) {
        printf("Parse error in file %s on line %d\n", filename.c_str(), lineNum);
        return false;
    }
    
    // If here, the line parsed correctly
    keyVector.push_back(key);
    valueVector.push_back(value);
    return true;
}


/*
    Constructor/Destructor
*/
KeyValueReader::KeyValueReader()
{
    c_data = new Private();
    c_data->isFileRead = false;
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
    
    // Open file
    file.open(filename);
    if (!file.is_open()) {
        return StatusOpenFileError;
    }
    
    // Parse each line
    while (std::getline(file, line)) {
        bool parseOk = c_data->parseLine(lineNum, filename, line);
        if (!parseOk)
            status = StatusParseFileError;
        lineNum++;
    }
    
    // Close file and return
    file.close();
    return status;
}


/*
    getString
*/
KeyValueReader::STATUS
KeyValueReader::getString(const std::string &key, std::string &value)
{
    for (size_t i = 0; i < c_data->keyVector.size(); i++) {
        if (areStringsEqual(key, c_data->keyVector[i])) {
            value = c_data->keyVector[i];
            return StatusSuccess;
        }
    }
    
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
        return status;
    }
    
    try {
        value = stoi(valueString);
    }
    catch (...) {
        value = 0;
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
        return status;
    }
    
    try {
        value = stod(valueString);
    }
    catch (...) {
        value = 0.0;
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
        return status;
    }
    
    try {
        value = stof(valueString);
    }
    catch (...) {
        value = 0.0f;
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
        return status;
    }
    
    // Check for true
    if (valueString.size() == 4 &&
        tolower(valueString[0]) == 't' &&
        tolower(valueString[1]) == 'r' &&
        tolower(valueString[2]) == 'u' &&
        tolower(valueString[3]) == 'e')
    {
        value = true;
        return StatusSuccess;
    }
    
    // Check for false
    if (valueString.size() == 5 &&
        tolower(valueString[0]) == 'f' &&
        tolower(valueString[1]) == 'a' &&
        tolower(valueString[2]) == 'l' &&
        tolower(valueString[3]) == 's' &&
        tolower(valueString[4]) == 'e')
    {
        value = false;
        return StatusSuccess;
    }
    
    // String conversion error if we get here
    return StatusStringConversionError;
}


/*
    print
*/
void KeyValueReader::print()
{
    printf("\n--- KeyValueReader Data ---\n");
    for (size_t i = 0; i < c_data->keyVector.size(); i++) {
        printf("    %s %s\n", c_data->keyVector[i].c_str(), 
                              c_data->valueVector[i].c_str());
    }
    printf("\n");
}

