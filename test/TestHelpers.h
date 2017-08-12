#ifndef __TEST_HELPERS_H__
#define __TEST_HELPERS_H__

#include <string>
#include "../src/KeyValueReader.h"

bool trySuccess(GarrettSoftware::KeyValueReader &kvr, 
                const std::string &filename);

bool tryFailure(GarrettSoftware::KeyValueReader &kvr, 
                const std::string &filename, 
                const GarrettSoftware::KeyValueReader::Exception e);

bool tryKeyValueSuccessString(GarrettSoftware::KeyValueReader &kvr, 
                              const std::string &key,
                              const std::string &value);

bool tryKeyValueSuccessInt(GarrettSoftware::KeyValueReader &kvr, 
                           const std::string &key,
                           const int value);

bool tryKeyValueSuccessDouble(GarrettSoftware::KeyValueReader &kvr, 
                              const std::string &key,
                              const double value);

bool tryKeyValueSuccessFloat(GarrettSoftware::KeyValueReader &kvr, 
                             const std::string &key,
                             const float value);

bool tryKeyValueSuccessBool(GarrettSoftware::KeyValueReader &kvr, 
                            const std::string &key,
                            const bool value);

bool tryKeyValueFailureString(GarrettSoftware::KeyValueReader &kvr, 
                              const std::string &key,
                              const GarrettSoftware::KeyValueReader::Exception e);

bool tryKeyValueFailureInt(GarrettSoftware::KeyValueReader &kvr, 
                           const std::string &key,
                           const GarrettSoftware::KeyValueReader::Exception e);

bool tryKeyValueFailureDouble(GarrettSoftware::KeyValueReader &kvr, 
                              const std::string &key,
                              const GarrettSoftware::KeyValueReader::Exception e);

bool tryKeyValueFailureFloat(GarrettSoftware::KeyValueReader &kvr, 
                             const std::string &key,
                             const GarrettSoftware::KeyValueReader::Exception e);

bool tryKeyValueFailureBool(GarrettSoftware::KeyValueReader &kvr, 
                            const std::string &key,
                            const GarrettSoftware::KeyValueReader::Exception e);

#endif
