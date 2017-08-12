#include "TestHelpers.h"


/*
    Read file tests
*/
bool trySuccess(CKG_Utils::KeyValueReader &kvr, 
                const std::string &filename)
{
    try {
        kvr.readFile(filename);
        return true;
    }
    catch (...) { }
    return false;
}

bool tryFailure(CKG_Utils::KeyValueReader &kvr, 
                const std::string &filename, 
                const CKG_Utils::KeyValueReader::Exception e)
{
    try {
        kvr.readFile(filename);
        return false;
    }
    catch (CKG_Utils::KeyValueReader::Exception e1) {
        if (e1 != e)
            return false;
    }
    return true;
}


/*
    Key Value Tests
*/
// String
bool tryKeyValueSuccessString(CKG_Utils::KeyValueReader &kvr, 
                              const std::string &key,
                              const std::string &value)
{
    std::string value1;
    
    try {
        kvr.getString(key, value1);
        if (value1 != value)
            return false;
    }
    catch (...) {
        return false;
    }
    return true;
}
// int
bool tryKeyValueSuccessInt(CKG_Utils::KeyValueReader &kvr, 
                           const std::string &key,
                           const int value)
{
    int value1;
    
    try {
        kvr.getInt(key, value1);
        if (value1 != value)
            return false;
    }
    catch (...) {
        return false;
    }
    return true;
}
// double
bool tryKeyValueSuccessDouble(CKG_Utils::KeyValueReader &kvr, 
                              const std::string &key,
                              const double value)
{
    double value1;
    
    try {
        kvr.getDouble(key, value1);
        if (value1 != value)
            return false;
    }
    catch (...) {
        return false;
    }
    return true;
}
// float
bool tryKeyValueSuccessFloat(CKG_Utils::KeyValueReader &kvr, 
                             const std::string &key,
                             const float value)
{
    float value1;
    
    try {
        kvr.getFloat(key, value1);
        if (value1 != value)
            return false;
    }
    catch (...) {
        return false;
    }
    return true;
}
// bool
bool tryKeyValueSuccessBool(CKG_Utils::KeyValueReader &kvr, 
                            const std::string &key,
                            const bool value)
{
    bool value1;
    
    try {
        kvr.getBool(key, value1);
        if (value1 != value)
            return false;
    }
    catch (...) {
        return false;
    }
    return true;
}

// string
bool tryKeyValueFailureString(CKG_Utils::KeyValueReader &kvr, 
                              const std::string &key,
                              const CKG_Utils::KeyValueReader::Exception e)
{
    std::string value1;
    
    try {
        kvr.getString(key, value1);
        return false;
    }
    catch (CKG_Utils::KeyValueReader::Exception e1) {
        if (e1 != e)
            return false;
    }
    return true;
}

// int
bool tryKeyValueFailureInt(CKG_Utils::KeyValueReader &kvr, 
                           const std::string &key,
                           const CKG_Utils::KeyValueReader::Exception e)
{
    int value1;
    
    try {
        kvr.getInt(key, value1);
        return false;
    }
    catch (CKG_Utils::KeyValueReader::Exception e1) {
        if (e1 != e)
            return false;
    }
    return true;
}

// double
bool tryKeyValueFailureDouble(CKG_Utils::KeyValueReader &kvr, 
                              const std::string &key,
                              const CKG_Utils::KeyValueReader::Exception e)
{
    double value1;
    
    try {
        kvr.getDouble(key, value1);
        return false;
    }
    catch (CKG_Utils::KeyValueReader::Exception e1) {
        if (e1 != e)
            return false;
    }
    return true;
}

// float
bool tryKeyValueFailureFloat(CKG_Utils::KeyValueReader &kvr, 
                             const std::string &key,
                             const CKG_Utils::KeyValueReader::Exception e)
{
    float value1;
    
    try {
        kvr.getFloat(key, value1);
        return false;
    }
    catch (CKG_Utils::KeyValueReader::Exception e1) {
        if (e1 != e)
            return false;
    }
    return true;
}

// bool
bool tryKeyValueFailureBool(CKG_Utils::KeyValueReader &kvr, 
                            const std::string &key,
                            const CKG_Utils::KeyValueReader::Exception e)
{
    bool value1;
    
    try {
        kvr.getBool(key, value1);
        return false;
    }
    catch (CKG_Utils::KeyValueReader::Exception e1) {
        if (e1 != e)
            return false;
    }
    return true;
}



