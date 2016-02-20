#include "TestHelpers.h"


/*
    Read file tests
*/
void trySuccess(KeyValueReader &kvr, const std::string &filename, 
                const char test, std::string &errors)
{
    try {
        kvr.readFile(filename);
    }
    catch (...) {
        errors += test;
    }
}

void tryFailure(KeyValueReader &kvr, const std::string &filename, 
                const char test, std::string &errors, 
                const KeyValueReader::Exception exceptionToMatch)
{
    try {
        kvr.readFile(filename);
        errors += test;
    }
    catch (KeyValueReader::Exception e) {
        if (e != exceptionToMatch)
            errors += test;
    }
}


/*
    Key Value Tests
*/
// String
void tryKeyValueSuccessString(KeyValueReader &kvr, const std::string &key,
                              const std::string &value, const char test,
                              std::string &errors)
{
    std::string value1;
    
    try {
        kvr.getString(key, value1);
        if (value1 != value)
            errors += test;
    }
    catch (...) {
        errors += test;
    }
}
// int
void tryKeyValueSuccessInt(KeyValueReader &kvr, const std::string &key,
                           const int value, const char test,
                           std::string &errors)
{
    int value1;
    
    try {
        kvr.getInt(key, value1);
        if (value1 != value)
            errors += test;
    }
    catch (...) {
        errors += test;
    }
}
// double
void tryKeyValueSuccessDouble(KeyValueReader &kvr, const std::string &key,
                              const double value, const char test,
                              std::string &errors)
{
    double value1;
    
    try {
        kvr.getDouble(key, value1);
        if (value1 != value)
            errors += test;
    }
    catch (...) {
        errors += test;
    }
}
// float
void tryKeyValueSuccessFloat(KeyValueReader &kvr, const std::string &key,
                             const float value, const char test,
                             std::string &errors)
{
    float value1;
    
    try {
        kvr.getFloat(key, value1);
        if (value1 != value)
            errors += test;
    }
    catch (...) {
        errors += test;
    }
}
// bool
void tryKeyValueSuccessBool(KeyValueReader &kvr, const std::string &key,
                            const bool value, const char test,
                            std::string &errors)
{
    bool value1;
    
    try {
        kvr.getBool(key, value1);
        if (value1 != value)
            errors += test;
    }
    catch (...) {
        errors += test;
    }
}

// string
void tryKeyValueFailureString(KeyValueReader &kvr, const std::string &key,
                              const char test, std::string &errors, 
                              const KeyValueReader::Exception exceptionToMatch)
{
    std::string value1;
    
    try {
        kvr.getString(key, value1);
        errors += test;
    }
    catch (KeyValueReader::Exception e) {
        if (e != exceptionToMatch)
            errors += test;
    }
}

// int
void tryKeyValueFailureInt(KeyValueReader &kvr, const std::string &key,
                           const char test, std::string &errors, 
                           const KeyValueReader::Exception exceptionToMatch)
{
    int value1;
    
    try {
        kvr.getInt(key, value1);
        errors += test;
    }
    catch (KeyValueReader::Exception e) {
        if (e != exceptionToMatch)
            errors += test;
    }
}

// double
void tryKeyValueFailureDouble(KeyValueReader &kvr, const std::string &key,
                              const char test, std::string &errors, 
                              const KeyValueReader::Exception exceptionToMatch)
{
    double value1;
    
    try {
        kvr.getDouble(key, value1);
        errors += test;
    }
    catch (KeyValueReader::Exception e) {
        if (e != exceptionToMatch)
            errors += test;
    }
}

// float
void tryKeyValueFailureFloat(KeyValueReader &kvr, const std::string &key,
                             const char test, std::string &errors, 
                             const KeyValueReader::Exception exceptionToMatch)
{
    float value1;
    
    try {
        kvr.getFloat(key, value1);
        errors += test;
    }
    catch (KeyValueReader::Exception e) {
        if (e != exceptionToMatch)
            errors += test;
    }
}

// bool
void tryKeyValueFailureBool(KeyValueReader &kvr, const std::string &key,
                            const char test, std::string &errors, 
                            const KeyValueReader::Exception exceptionToMatch)
{
    bool value1;
    
    try {
        kvr.getBool(key, value1);
        errors += test;
    }
    catch (KeyValueReader::Exception e) {
        if (e != exceptionToMatch)
            errors += test;
    }
}



