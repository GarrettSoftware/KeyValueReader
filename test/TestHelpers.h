#ifndef __TEST_HELPERS_H__
#define __TEST_HELPERS_H__

#include <string>
#include "../src/KeyValueReader.h"

void trySuccess(KeyValueReader &kvr, const std::string &filename, 
                const char test, std::string &errors);

void tryFailure(KeyValueReader &kvr, const std::string &filename, 
                const char test, std::string &errors, 
                const KeyValueReader::Exception exceptionToMatch);

void tryKeyValueSuccessString(KeyValueReader &kvr, const std::string &key,
                              const std::string &value, const char test,
                              std::string &errors);

void tryKeyValueSuccessInt(KeyValueReader &kvr, const std::string &key,
                           const int value, const char test,
                           std::string &errors);

void tryKeyValueSuccessDouble(KeyValueReader &kvr, const std::string &key,
                              const double value, const char test,
                              std::string &errors);

void tryKeyValueSuccessFloat(KeyValueReader &kvr, const std::string &key,
                             const float value, const char test,
                             std::string &errors);

void tryKeyValueSuccessBool(KeyValueReader &kvr, const std::string &key,
                            const bool value, const char test,
                            std::string &errors);

void tryKeyValueFailureString(KeyValueReader &kvr, const std::string &key,
                              const char test, std::string &errors, 
                              const KeyValueReader::Exception exceptionToMatch);

void tryKeyValueFailureInt(KeyValueReader &kvr, const std::string &key,
                           const char test, std::string &errors, 
                           const KeyValueReader::Exception exceptionToMatch);

void tryKeyValueFailureDouble(KeyValueReader &kvr, const std::string &key,
                              const char test, std::string &errors, 
                              const KeyValueReader::Exception exceptionToMatch);

void tryKeyValueFailureFloat(KeyValueReader &kvr, const std::string &key,
                             const char test, std::string &errors, 
                             const KeyValueReader::Exception exceptionToMatch);

void tryKeyValueFailureBool(KeyValueReader &kvr, const std::string &key,
                            const char test, std::string &errors, 
                            const KeyValueReader::Exception exceptionToMatch);

#endif
