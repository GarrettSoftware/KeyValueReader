/*
The MIT License (MIT)

Copyright (c) 2016 C. Kristopher Garrett

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

#include "TestHelpers.h"

/*
    Read file tests
*/
bool trySuccess(
    void *kvr, 
    const std::string &filename)
{
    KVR_Status error = KVR_readFile(kvr, filename.c_str());
    if (error == KVR_Success)
        return true;
    return false;
}

bool tryFailure(
    void *kvr, 
    const std::string &filename, 
    const KVR_Status error)
{
    KVR_Status error1 = KVR_readFile(kvr, filename.c_str());
    if (error != error1)
        return false;
    return true;
}


/*
    Key Value Tests
*/
// String
bool tryKeyValueSuccessString(
    const void *kvr, 
    const std::string &key,
    const std::string &value)
{
    char valueChars[100];
    KVR_Status error = KVR_getString(kvr, key.c_str(), valueChars);
    std::string value1(valueChars);

    if (error != KVR_Success)
        return false;
    if (value1 != value)
        return false;
    return true;
}
// int
bool tryKeyValueSuccessInt(
    const void *kvr, 
    const std::string &key,
    const int value)
{
    int value1;
    KVR_Status error = KVR_getInt(kvr, key.c_str(), value1);

    if (error != KVR_Success)
        return false;
    if (value1 != value)
        return false;
    return true;
}
// double
bool tryKeyValueSuccessDouble(
    const void *kvr, 
    const std::string &key,
    const double value)
{
    double value1;
    KVR_Status error = KVR_getDouble(kvr, key.c_str(), value1);

    if (error != KVR_Success)
        return false;
    if (value1 != value)
        return false;
    return true;
}
// float
bool tryKeyValueSuccessFloat(
    const void *kvr, 
    const std::string &key,
    const float value)
{
    float value1;
    KVR_Status error = KVR_getFloat(kvr, key.c_str(), value1);

    if (error != KVR_Success)
        return false;
    if (value1 != value)
        return false;
    return true;
}
// bool
bool tryKeyValueSuccessBool(
    const void *kvr, 
    const std::string &key,
    const bool value)
{
    bool value1;
    KVR_Status error = KVR_getBool(kvr, key.c_str(), value1);

    if (error != KVR_Success)
        return false;
    if (value1 != value)
        return false;
    return true;
}

// string
bool tryKeyValueFailureString(
    const void *kvr, 
    const std::string &key,
    const KVR_Status error)
{
    char valueChars[100];
    KVR_Status error1 = KVR_getString(kvr, key.c_str(), valueChars);
    std::string value1(valueChars);

    if (error != error1)
        return false;
    return true;
}

// int
bool tryKeyValueFailureInt(
    const void *kvr, 
    const std::string &key,
    const KVR_Status error)
{
    int value1;
    KVR_Status error1 = KVR_getInt(kvr, key.c_str(), value1);

    if (error != error1)
        return false;
    return true;
}

// double
bool tryKeyValueFailureDouble(
    const void *kvr, 
    const std::string &key,
    const KVR_Status error)
{
    double value1;
    KVR_Status error1 = KVR_getDouble(kvr, key.c_str(), value1);

    if (error != error1)
        return false;
    return true;
}

// float
bool tryKeyValueFailureFloat(
    const void *kvr, 
    const std::string &key,
    const KVR_Status error)
{
    float value1;
    KVR_Status error1 = KVR_getFloat(kvr, key.c_str(), value1);

    if (error != error1)
        return false;
    return true;
}

// bool
bool tryKeyValueFailureBool(
    const void *kvr, 
    const std::string &key,
    const KVR_Status error)
{
    bool value1;
    KVR_Status error1 = KVR_getBool(kvr, key.c_str(), value1);

    if (error != error1)
        return false;
    return true;
}


/*
    Max value length tests
*/
bool tryMaxValueLengthSuccess(
    const void *kvr,
    const int length)
{
    int length1;
    KVR_Status error = KVR_getMaxValueLength(kvr, &length1);

    if (error != KVR_Success)
        return false;
    if (length != length1)
        return false;
    return true;
}

bool tryMaxValueLengthFailure(
    const void *kvr,
    const KVR_Status error)
{
    int length1;
    KVR_Status error1 = KVR_getMaxValueLength(kvr, &length1);

    if (error != error1)
        return false;
    return true;
}

