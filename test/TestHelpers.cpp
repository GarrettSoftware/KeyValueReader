#include "TestHelpers.h"


/*
    Read file tests
*/
bool trySuccess(void *kvr, 
                const std::string &filename)
{
    KVR_Error error = readFile(kvr, filename.c_str());
    if (error == KVR_Error_None)
        return true;
    return false;
}

bool tryFailure(void *kvr, 
                const std::string &filename, 
                const KVR_Error error)
{
    KVR_Error error1 = readFile(kvr, filename.c_str());
    if (error != error1)
        return false;
    return true;
}


/*
    Key Value Tests
*/
// String
bool tryKeyValueSuccessString(void *kvr, 
                              const std::string &key,
                              const std::string &value)
{
    char valueChars[100];
    KVR_Error error = getString(kvr, key.c_str(), valueChars);
    std::string value1(valueChars);

    if (error != KVR_Error_None)
        return false;
    if (value1 != value)
        return false;
    return true;
}
// int
bool tryKeyValueSuccessInt(void *kvr, 
                           const std::string &key,
                           const int value)
{
    int value1;
    KVR_Error error = getInt(kvr, key.c_str(), value1);

    if (error != KVR_Error_None)
        return false;
    if (value1 != value)
        return false;
    return true;
}
// double
bool tryKeyValueSuccessDouble(void *kvr, 
                              const std::string &key,
                              const double value)
{
    double value1;
    KVR_Error error = getDouble(kvr, key.c_str(), value1);

    if (error != KVR_Error_None)
        return false;
    if (value1 != value)
        return false;
    return true;
}
// float
bool tryKeyValueSuccessFloat(void *kvr, 
                             const std::string &key,
                             const float value)
{
    float value1;
    KVR_Error error = getFloat(kvr, key.c_str(), value1);

    if (error != KVR_Error_None)
        return false;
    if (value1 != value)
        return false;
    return true;
}
// bool
bool tryKeyValueSuccessBool(void *kvr, 
                            const std::string &key,
                            const bool value)
{
    bool value1;
    KVR_Error error = getBool(kvr, key.c_str(), value1);

    if (error != KVR_Error_None)
        return false;
    if (value1 != value)
        return false;
    return true;
}

// string
bool tryKeyValueFailureString(void *kvr, 
                              const std::string &key,
                              const KVR_Error error)
{
    char valueChars[100];
    KVR_Error error1 = getString(kvr, key.c_str(), valueChars);
    std::string value1(valueChars);

    if (error != error1)
        return false;
    return true;
}

// int
bool tryKeyValueFailureInt(void *kvr, 
                           const std::string &key,
                           const KVR_Error error)
{
    int value1;
    KVR_Error error1 = getInt(kvr, key.c_str(), value1);

    if (error != error1)
        return false;
    return true;
}

// double
bool tryKeyValueFailureDouble(void *kvr, 
                              const std::string &key,
                              const KVR_Error error)
{
    double value1;
    KVR_Error error1 = getDouble(kvr, key.c_str(), value1);

    if (error != error1)
        return false;
    return true;
}

// float
bool tryKeyValueFailureFloat(void *kvr, 
                             const std::string &key,
                             const KVR_Error error)
{
    float value1;
    KVR_Error error1 = getFloat(kvr, key.c_str(), value1);

    if (error != error1)
        return false;
    return true;
}

// bool
bool tryKeyValueFailureBool(void *kvr, 
                            const std::string &key,
                            const KVR_Error error)
{
    bool value1;
    KVR_Error error1 = getBool(kvr, key.c_str(), value1);

    if (error != error1)
        return false;
    return true;
}



