#include "TestHelpers.h"


/*
    Read file tests
*/
void trySuccess(CKG_Utils::KeyValueReader &kvr, const std::string &filename, 
                const char test, std::string &errors)
{
    try {
        kvr.readFile(filename);
    }
    catch (...) {
        errors += test;
    }
}

void tryFailure(CKG_Utils::KeyValueReader &kvr, const std::string &filename, 
                const char test, std::string &errors, 
                const CKG_Utils::KeyValueReader::Exception exceptionToMatch)
{
    try {
        kvr.readFile(filename);
        errors += test;
    }
    catch (CKG_Utils::KeyValueReader::Exception e) {
        if (e != exceptionToMatch)
            errors += test;
    }
}


/*
    Key Value Tests
*/
// String
void tryKeyValueSuccessString(CKG_Utils::KeyValueReader &kvr, const std::string &key,
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
void tryKeyValueSuccessInt(CKG_Utils::KeyValueReader &kvr, const std::string &key,
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
void tryKeyValueSuccessDouble(CKG_Utils::KeyValueReader &kvr, const std::string &key,
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
void tryKeyValueSuccessFloat(CKG_Utils::KeyValueReader &kvr, const std::string &key,
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
void tryKeyValueSuccessBool(CKG_Utils::KeyValueReader &kvr, const std::string &key,
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
void tryKeyValueFailureString(CKG_Utils::KeyValueReader &kvr, const std::string &key,
                              const char test, std::string &errors, 
                              const CKG_Utils::KeyValueReader::Exception exceptionToMatch)
{
    std::string value1;
    
    try {
        kvr.getString(key, value1);
        errors += test;
    }
    catch (CKG_Utils::KeyValueReader::Exception e) {
        if (e != exceptionToMatch)
            errors += test;
    }
}

// int
void tryKeyValueFailureInt(CKG_Utils::KeyValueReader &kvr, const std::string &key,
                           const char test, std::string &errors, 
                           const CKG_Utils::KeyValueReader::Exception exceptionToMatch)
{
    int value1;
    
    try {
        kvr.getInt(key, value1);
        errors += test;
    }
    catch (CKG_Utils::KeyValueReader::Exception e) {
        if (e != exceptionToMatch)
            errors += test;
    }
}

// double
void tryKeyValueFailureDouble(CKG_Utils::KeyValueReader &kvr, const std::string &key,
                              const char test, std::string &errors, 
                              const CKG_Utils::KeyValueReader::Exception exceptionToMatch)
{
    double value1;
    
    try {
        kvr.getDouble(key, value1);
        errors += test;
    }
    catch (CKG_Utils::KeyValueReader::Exception e) {
        if (e != exceptionToMatch)
            errors += test;
    }
}

// float
void tryKeyValueFailureFloat(CKG_Utils::KeyValueReader &kvr, const std::string &key,
                             const char test, std::string &errors, 
                             const CKG_Utils::KeyValueReader::Exception exceptionToMatch)
{
    float value1;
    
    try {
        kvr.getFloat(key, value1);
        errors += test;
    }
    catch (CKG_Utils::KeyValueReader::Exception e) {
        if (e != exceptionToMatch)
            errors += test;
    }
}

// bool
void tryKeyValueFailureBool(CKG_Utils::KeyValueReader &kvr, const std::string &key,
                            const char test, std::string &errors, 
                            const CKG_Utils::KeyValueReader::Exception exceptionToMatch)
{
    bool value1;
    
    try {
        kvr.getBool(key, value1);
        errors += test;
    }
    catch (CKG_Utils::KeyValueReader::Exception e) {
        if (e != exceptionToMatch)
            errors += test;
    }
}



