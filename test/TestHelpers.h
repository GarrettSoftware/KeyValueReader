#ifndef __TEST_HELPERS_H__
#define __TEST_HELPERS_H__

#include <string>
#include "../src/KeyValueReader.h"

void trySuccess(CKG_Utils::KeyValueReader &kvr, const std::string &filename, 
                const char test, std::string &errors);

void tryFailure(CKG_Utils::KeyValueReader &kvr, const std::string &filename, 
                const char test, std::string &errors, 
                const CKG_Utils::KeyValueReader::Exception exceptionToMatch);

void tryKeyValueSuccessString(CKG_Utils::KeyValueReader &kvr, const std::string &key,
                              const std::string &value, const char test,
                              std::string &errors);

void tryKeyValueSuccessInt(CKG_Utils::KeyValueReader &kvr, const std::string &key,
                           const int value, const char test,
                           std::string &errors);

void tryKeyValueSuccessDouble(CKG_Utils::KeyValueReader &kvr, const std::string &key,
                              const double value, const char test,
                              std::string &errors);

void tryKeyValueSuccessFloat(CKG_Utils::KeyValueReader &kvr, const std::string &key,
                             const float value, const char test,
                             std::string &errors);

void tryKeyValueSuccessBool(CKG_Utils::KeyValueReader &kvr, const std::string &key,
                            const bool value, const char test,
                            std::string &errors);

void tryKeyValueFailureString(CKG_Utils::KeyValueReader &kvr, const std::string &key,
                              const char test, std::string &errors, 
                              const CKG_Utils::KeyValueReader::Exception exceptionToMatch);

void tryKeyValueFailureInt(CKG_Utils::KeyValueReader &kvr, const std::string &key,
                           const char test, std::string &errors, 
                           const CKG_Utils::KeyValueReader::Exception exceptionToMatch);

void tryKeyValueFailureDouble(CKG_Utils::KeyValueReader &kvr, const std::string &key,
                              const char test, std::string &errors, 
                              const CKG_Utils::KeyValueReader::Exception exceptionToMatch);

void tryKeyValueFailureFloat(CKG_Utils::KeyValueReader &kvr, const std::string &key,
                             const char test, std::string &errors, 
                             const CKG_Utils::KeyValueReader::Exception exceptionToMatch);

void tryKeyValueFailureBool(CKG_Utils::KeyValueReader &kvr, const std::string &key,
                            const char test, std::string &errors, 
                            const CKG_Utils::KeyValueReader::Exception exceptionToMatch);

#endif
