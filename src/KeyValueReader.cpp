#include "KeyValueReader.h"
#include <vector>
#include <fstream>
#include <stdio.h>

using namespace std;



class KeyValueReader::PrivateData
{
public:
    void parseLine(const int lineNum, const string &filename, const string &line);
    
    vector<string> keyVector;
    vector<string> valueVector;
    bool isFileRead;
};


static
void getRidOfComments(string &line)
{
    size_t commentStart = line.find('#');
    if (commentStart != string::npos)
        line = line.substr(0, commentStart);
}


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


void KeyValueReader::PrivateData::parseLine(const int lineNum, 
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
        return;
    
    // Get key
    popToken(parsedLine, key);
    if (key == "") {
        printf("Parse error in file %s on line %d\n", filename.c_str(), lineNum);
        return;
    }
    
    // Delete whitespace
    numWhitespace = deleteWhitespace(parsedLine);
    if (numWhitespace == 0) {
        printf("Parse error in file %s on line %d\n", filename.c_str(), lineNum);
        return;
    }
    
    // Get value
    popToken(parsedLine, value);
    if (value == "") {
        printf("Parse error in file %s on line %d\n", filename.c_str(), lineNum);
        return;
    }
    
    // Delete whitespace
    deleteWhitespace(parsedLine);
    
    // Check for non-empty line
    if (parsedLine.size() != 0) {
        printf("Parse error in file %s on line %d\n", filename.c_str(), lineNum);
        return;
    }
    
    // If here, the line parsed correctly
    keyVector.push_back(key);
    valueVector.push_back(value);
}


KeyValueReader::KeyValueReader()
{
    c_data = new PrivateData();
    c_data->isFileRead = false;
}


KeyValueReader::~KeyValueReader()
{
    delete c_data;
}


KeyValueReader::STATUS KeyValueReader::readFile(const string &filename)
{
    ifstream file;
    file.open(filename);
    
    std::string line;
    int lineNum = 1;
    while (std::getline(file, line)) {
        //printf("%s\n", line.c_str());
        c_data->parseLine(lineNum, filename, line);
        lineNum++;
    }
    print();
    
    file.close();
    return StatusSuccess;
}


KeyValueReader::STATUS KeyValueReader::getString(const std::string &key, std::string &value)
{
    for (int i = 0; i < c_data->keyVector.size(); i++) {
        if (key == c_data->keyVector[i]) {
            value = c_data->keyVector[i];
            return StatusSuccess;
        }
    }
    
    return StatusKeyNotFound;
}


KeyValueReader::STATUS KeyValueReader::getInt(const std::string &key, int &value)
{
    string valueString;
    STATUS status;
    
    status = getString(key, valueString);
    if (status != StatusSuccess) {
        value = 0;
        return status;
    }
    
    value = stoi(valueString);
    
    return StatusSuccess;
}


KeyValueReader::STATUS KeyValueReader::getDouble(const std::string &key, double &value)
{
    return StatusSuccess;
}


KeyValueReader::STATUS KeyValueReader::getBool(const std::string &key, bool &value)
{
    return StatusSuccess;
}


void KeyValueReader::print()
{
    for (int i = 0; i < c_data->keyVector.size(); i++) {
        printf("%s %s\n", c_data->keyVector[i].c_str(), c_data->valueVector[i].c_str());
    }
}

