#ifndef __TEST_HELPERS_H__
#define __TEST_HELPERS_H__

#include <string>
#include "../src/KeyValueReader.h"

bool trySuccess(CKG_Utils::KeyValueReader &kvr, 
                const std::string &filename);

bool tryFailure(CKG_Utils::KeyValueReader &kvr, 
                const std::string &filename, 
                const CKG_Utils::KeyValueReader::Exception e);

bool tryKeyValueSuccessString(CKG_Utils::KeyValueReader &kvr, 
                              const std::string &key,
                              const std::string &value);

bool tryKeyValueSuccessInt(CKG_Utils::KeyValueReader &kvr, 
                           const std::string &key,
                           const int value);

bool tryKeyValueSuccessDouble(CKG_Utils::KeyValueReader &kvr, 
                              const std::string &key,
                              const double value);

bool tryKeyValueSuccessFloat(CKG_Utils::KeyValueReader &kvr, 
                             const std::string &key,
                             const float value);

bool tryKeyValueSuccessBool(CKG_Utils::KeyValueReader &kvr, 
                            const std::string &key,
                            const bool value);

bool tryKeyValueFailureString(CKG_Utils::KeyValueReader &kvr, 
                              const std::string &key,
                              const CKG_Utils::KeyValueReader::Exception e);

bool tryKeyValueFailureInt(CKG_Utils::KeyValueReader &kvr, 
                           const std::string &key,
                           const CKG_Utils::KeyValueReader::Exception e);

bool tryKeyValueFailureDouble(CKG_Utils::KeyValueReader &kvr, 
                              const std::string &key,
                              const CKG_Utils::KeyValueReader::Exception e);

bool tryKeyValueFailureFloat(CKG_Utils::KeyValueReader &kvr, 
                             const std::string &key,
                             const CKG_Utils::KeyValueReader::Exception e);

bool tryKeyValueFailureBool(CKG_Utils::KeyValueReader &kvr, 
                            const std::string &key,
                            const CKG_Utils::KeyValueReader::Exception e);

#endif
