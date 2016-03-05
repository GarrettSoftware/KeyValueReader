# KeyValueReader 1.1

## Releases
Each release is tagged.
The main branch should contain the latest release.
The easiest way to get the latest release is to either `git clone` the repository or select the "Download ZIP" button from the main page.

## Overview 
This software implements a single class to easily add basic file input to your programs.
Just put KeyValueReader.cpp and KeyValueReader.h in your project and add the extra sources to your build.
Note: this software requires the C++11 standard.
For g++ you will need the flag `--std=c++11`.

Basic usage looks like the following.
For simple programs, you may not want to use a try/catch block and simply let the program abort from any exception that occurs.

    string runType;
    int problemSize;
    double tolerance;
    bool doExtraThing;

    CKG_Utils::KeyValueReader kvr;
    try {
        kvr.readFile("input.kv");
        kvr.getString("RUN_TYPE", runType);
        kvr.getInt("PROBLEM_SIZE", problemSize);
        kvr.getDouble("TOLERANCE", tolerance);
        kvr.getBool("DO_EXTRA_THING", doExtraThing);
    }
    catch (KeyValueReader::Exception e) {
        // Catch errors
    }

## Interface
    enum Exception {
        ExceptionAlreadyReadAFile,
        ExceptionFileNotRead,
        ExceptionOpenFileError,
        ExceptionParseFileError,
        ExceptionKeyNotFound,
        ExceptionStringConversionError
    };
    
    void readFile(const std::string &filename);
    void getString(const std::string &key, std::string &value) const;
    void getInt(const std::string &key, int &value) const;
    void getDouble(const std::string &key, double &value) const;
    void getFloat(const std::string &key, float &value) const;
    void getBool(const std::string &key, bool &value) const;
    void print() const;
    void reset();


### readFile
This function reads and parses the file given by `filename`.
If a file has already been parse, `ExceptionAlreadyReadAFile` is thrown.
If the file cannot be opened, `ExceptionOpenFileError` is thrown.
If there is a parse error, `ExceptionParseFileError` is returned, but in this case, some lines may be parsed correctly and those lines will be stored by the KeyValueReader.
In the case of parse errors, a line is printed to standard out specifying the line number of the error.

### getString, getInt, ...
These functions take a `key` as input and return the appropriate `value` in the KeyValueReader.
If a file has not been read, `ExceptionFileNotRead` is thrown.
If the `key` does not exist, `ExceptionKeyNotFound` is thrown.
If something other than getString is called, a conversion from a string value to the appropriate value is made.
In this case it is possible to get an `ExceptionStringConversionError` returned.
Note, the key search is not case sensitive, but the value returned from getString does not change the case of `value` from the input file.

### print
This function prints all the key/value pairs in the KeyValueReader.
If a file has not been read, `ExceptionFileNotRead` is thrown.

### reset
Resets the KeyValueReader to a state where a new file may be read.


## File Format
The key/value file format is a line based format (i.e. 1 key/value pair should be held on a single line).
The class allows for single line comments starting with the `#` character.
Whitespace is ignored except to delimit the key from the value.
A line can consist of a key/value pair with or without a comment, just a comment, or solely whitespace.
Below is the specification for the key/value file format.

    (<whitespace>)* <token> (<whitespace)+ <token> (<whitespace>)* <comment>
    (<whitespace>)* <comment>
    (<whitespace>)*

* Each whitespace character is either a space or tab.
* Each token is made up of either letters, numbers, or "+-_.".
* A comment consists of `#` followed by any characters

An example of an input file might look like the following.
    
    # My Example Key-Value File
    RUN_TYPE        type1   
    PROBLEM_SIZE    1000    # Big Problem
    TOLERANCE       0.01    # Small Tolerance
    DO_EXTRA_THING  true





