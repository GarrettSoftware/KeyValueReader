#include "KeyValueReader_C.h"
#include "KeyValueReader.h"


extern "C" {

using namespace GarrettSoftware;

void* KVR_createKeyValueReader()
{
    KeyValueReader *kvr = new KeyValueReader();
    return kvr;
}

void KVR_deleteKeyValueReader(void *kvr)
{
    KeyValueReader *kvr1 = (KeyValueReader*)kvr;
    delete kvr1;
}


KVR_Error KVR_readFile(void *kvr, const char *filename)
{
    KeyValueReader *kvr1 = (KeyValueReader*)kvr;
    try
    {
        kvr1->readFile(filename);
    }
    catch(...) {

    }

    return KVR_Error_None;
}

//KVR_Error KVR_getString(void *kvr, const char *key, char *value);
//KVR_Error KVR_getInt(void *kvr, const char *key, int *value);
//KVR_Error KVR_getDouble(void *kvr, const char *key, double *value);
//KVR_Error KVR_getFloat(void *kvr, const char *key, float *value);
//KVR_Error KVR_getBool(void *kvr, const char *key, int *value);
//KVR_Error KVR_print();
//KVR_Error KVR_reset();



}
