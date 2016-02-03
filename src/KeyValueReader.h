#ifndef __KEY_VALUE_READER_H
#define __KEY_VALUE_READER_H

#include <string>

class KeyValueReader final
{
public:
    
    // Status error values
    enum STATUS {
        StatusSuccess,
        StatusOpenFileError,
        StatusParseFileError,
        StatusKeyNotFound,
        StatusStringConversionError
    };
    
    // Constructor/Destructor
    explicit KeyValueReader();
    ~KeyValueReader();
    
    // Don't allow copy or assignment operators
    KeyValueReader(const KeyValueReader &kvr) = delete;
    KeyValueReader &operator=(const KeyValueReader &kvr) = delete;
    
    // Interface
    STATUS readFile(const std::string &filename);
    STATUS getString(const std::string &key, std::string &value);
    STATUS getInt(const std::string &key, int &value);
    STATUS getDouble(const std::string &key, double &value);
    STATUS getFloat(const std::string &key, float &value);
    STATUS getBool(const std::string &key, bool &value);
    void print();
    void setAbortOnError(bool willAbort);
    
private:
    struct Private;
    Private *c_data;
};

#endif
