# KeyValueReader - simple key-value file reader

## Overview 
This software implements a single class to easily add basic file input to your programs.
Just put KeyValueReader.cpp and KeyValueReader.h in your project and add the extra sources to your build scripts.
Basic usage looks like the following (with error checking omitted for simplicity).

    string runType;
    int problemSize;
    double tolerance;
    bool doExtraThing;

    KeyValueReader kvr;
    kvr.readFile("input.kv");
    kvr.getString("RUN_TYPE", runType);
    kvr.getInt("PROBLEM_SIZE", problemSize);
    kvr.getDouble("TOLERANCE", tolerance);
    kvr.getBool("DO_EXTRA_THING", doExtraThing);

## Interface
    enum STATUS {
        StatusSuccess,
        StatusOpenFileError,
        StatusParseFileError,
        StatusKeyNotFound,
        StatusStringConversionError
    };
    
    explicit KeyValueReader();
    ~KeyValueReader();
    
    STATUS readFile(const std::string &filename);
    STATUS getString(const std::string &key, std::string &value);
    STATUS getInt(const std::string &key, int &value);
    STATUS getDouble(const std::string &key, double &value);
    STATUS getFloat(const std::string &key, float &value);
    STATUS getBool(const std::string &key, bool &value);
    void print();


### readFile
This function reads and parses the file given by `filename`.
It will return `StatusSuccess` if the file could be read and parsed correctly.
If the file cannot be opened, `StatusOpenFileError` is returned.
If there is a parse error, `StatusParseFileError` is returned, but in this case, some lines may be parsed correctly and those lines will be stored by the KeyValueReader.
In the case of parse errors, a line is printed to standard out specifying the file and line of the error.

### getString, getInt, ...
These functions take a `key` as input and return the appropriate `value` in the KeyValueReader.
If the `key` does not exist, `StatusKeyNotFound` is returned.
If something other than getString is called, a conversion from a string value to the appropriate value is made.
In this case it is possible to get a `StatusStringConversionError` returned.
If there is no error, `StatusSuccess` is returned.
Note, the key search is not case sensitive, but the value returned from getString does not change the case of `value` from the input file.

### print
This function prints all the key/value pairs in the KeyValueReader.

### Error checking macro
To do...


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





