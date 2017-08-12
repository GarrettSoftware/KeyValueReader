#include "TestHelpers.h"


/*
    Read file tests
*/
bool trySuccess(GarrettSoftware::KeyValueReader &kvr, 
                const std::string &filename)
{
    try {
        kvr.readFile(filename);
        return true;
    }
    catch (...) { }
    return false;
}

bool tryFailure(GarrettSoftware::KeyValueReader &kvr, 
                const std::string &filename, 
                const GarrettSoftware::KeyValueReader::Exception e)
{
    try {
        kvr.readFile(filename);
        return false;
    }
    catch (GarrettSoftware::KeyValueReader::Exception e1) {
        if (e1 != e)
            return false;
    }
    return true;
}


/*
    Key Value Tests
*/
// String
bool tryKeyValueSuccessString(GarrettSoftware::KeyValueReader &kvr, 
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
bool tryKeyValueSuccessInt(GarrettSoftware::KeyValueReader &kvr, 
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
bool tryKeyValueSuccessDouble(GarrettSoftware::KeyValueReader &kvr, 
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
bool tryKeyValueSuccessFloat(GarrettSoftware::KeyValueReader &kvr, 
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
bool tryKeyValueSuccessBool(GarrettSoftware::KeyValueReader &kvr, 
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
bool tryKeyValueFailureString(GarrettSoftware::KeyValueReader &kvr, 
                              const std::string &key,
                              const GarrettSoftware::KeyValueReader::Exception e)
{
    std::string value1;
    
    try {
        kvr.getString(key, value1);
        return false;
    }
    catch (GarrettSoftware::KeyValueReader::Exception e1) {
        if (e1 != e)
            return false;
    }
    return true;
}

// int
bool tryKeyValueFailureInt(GarrettSoftware::KeyValueReader &kvr, 
                           const std::string &key,
                           const GarrettSoftware::KeyValueReader::Exception e)
{
    int value1;
    
    try {
        kvr.getInt(key, value1);
        return false;
    }
    catch (GarrettSoftware::KeyValueReader::Exception e1) {
        if (e1 != e)
            return false;
    }
    return true;
}

// double
bool tryKeyValueFailureDouble(GarrettSoftware::KeyValueReader &kvr, 
                              const std::string &key,
                              const GarrettSoftware::KeyValueReader::Exception e)
{
    double value1;
    
    try {
        kvr.getDouble(key, value1);
        return false;
    }
    catch (GarrettSoftware::KeyValueReader::Exception e1) {
        if (e1 != e)
            return false;
    }
    return true;
}

// float
bool tryKeyValueFailureFloat(GarrettSoftware::KeyValueReader &kvr, 
                             const std::string &key,
                             const GarrettSoftware::KeyValueReader::Exception e)
{
    float value1;
    
    try {
        kvr.getFloat(key, value1);
        return false;
    }
    catch (GarrettSoftware::KeyValueReader::Exception e1) {
        if (e1 != e)
            return false;
    }
    return true;
}

// bool
bool tryKeyValueFailureBool(GarrettSoftware::KeyValueReader &kvr, 
                            const std::string &key,
                            const GarrettSoftware::KeyValueReader::Exception e)
{
    bool value1;
    
    try {
        kvr.getBool(key, value1);
        return false;
    }
    catch (GarrettSoftware::KeyValueReader::Exception e1) {
        if (e1 != e)
            return false;
    }
    return true;
}



