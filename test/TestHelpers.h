#ifndef __TEST_HELPERS_H__
#define __TEST_HELPERS_H__

#include <string>
#include "../include/KeyValueReader.h"

bool trySuccess(void *kvr, 
                const std::string &filename);

bool tryFailure(void *kvr, 
                const std::string &filename, 
                const KVR_Error error);

bool tryKeyValueSuccessString(void *kvr, 
                              const std::string &key,
                              const std::string &value);

bool tryKeyValueSuccessInt(void *kvr, 
                           const std::string &key,
                           const int value);

bool tryKeyValueSuccessDouble(void *kvr, 
                              const std::string &key,
                              const double value);

bool tryKeyValueSuccessFloat(void *kvr, 
                             const std::string &key,
                             const float value);

bool tryKeyValueSuccessBool(void *kvr, 
                            const std::string &key,
                            const bool value);

bool tryKeyValueFailureString(void *kvr, 
                              const std::string &key,
                              const KVR_Error error);

bool tryKeyValueFailureInt(void *kvr, 
                           const std::string &key,
                           const KVR_Error error);

bool tryKeyValueFailureDouble(void *kvr, 
                              const std::string &key,
                              const KVR_Error error);

bool tryKeyValueFailureFloat(void *kvr, 
                             const std::string &key,
                             const KVR_Error error);

bool tryKeyValueFailureBool(void *kvr, 
                            const std::string &key,
                            const KVR_Error error);

#endif
