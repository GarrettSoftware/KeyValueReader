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

#ifndef __TEST_HELPERS_H__
#define __TEST_HELPERS_H__

#include "../include/KeyValueReader.h"
#include <string>

bool trySuccess(
    void *kvr, 
    const std::string &filename);

bool tryFailure(
    void *kvr, 
    const std::string &filename, 
    const KVR_Status error);

bool tryKeyValueSuccessString(
    const void *kvr, 
    const std::string &key,
    const std::string &value);

bool tryKeyValueSuccessInt(
    const void *kvr, 
    const std::string &key,
    const int value);

bool tryKeyValueSuccessDouble(
    const void *kvr, 
    const std::string &key,
    const double value);

bool tryKeyValueSuccessFloat(
    const void *kvr, 
    const std::string &key,
    const float value);

bool tryKeyValueSuccessBool(
    const void *kvr, 
    const std::string &key,
    const bool value);

bool tryKeyValueFailureString(
    const void *kvr, 
    const std::string &key,
    const KVR_Status error);

bool tryKeyValueFailureInt(
    const void *kvr, 
    const std::string &key,
    const KVR_Status error);

bool tryKeyValueFailureDouble(
    const void *kvr, 
    const std::string &key,
    const KVR_Status error);

bool tryKeyValueFailureFloat(
    const void *kvr, 
    const std::string &key,
    const KVR_Status error);

bool tryKeyValueFailureBool(
    const void *kvr, 
    const std::string &key,
    const KVR_Status error);

bool tryMaxValueLengthSuccess(
    const void *kvr,
    const int length);

bool tryMaxValueLengthFailure(
    const void *kvr,
    const KVR_Status error);

#endif
