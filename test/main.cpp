#include "../include/KeyValueReader.h"
#include "TestHelpers.h"
#include <gtest/gtest.h>


/////  Open File Tests  /////
TEST(OpenFileTests, DoesNotExistTest)
{
    void *kvr = KVR_create();
    KVR_Status error = KVR_OpenFileError;

    EXPECT_TRUE(tryFailure(kvr, "test_does_not_exist.kv", error));

    KVR_delete(kvr);
}


TEST(OpenFileTests, FileExistsTest)
{
    void *kvr = KVR_create();
    EXPECT_TRUE(trySuccess(kvr, "test_open.kv"));

    KVR_delete(kvr);
}


TEST(OpenFileTests, FileAlreadyOpenTest)
{
    void *kvr = KVR_create();
    KVR_Status error = KVR_AlreadyReadAFile;

    EXPECT_TRUE(trySuccess(kvr, "test_open.kv"));
    EXPECT_TRUE(tryFailure(kvr, "test_open.kv", error));

    KVR_delete(kvr);
}


/////  Parse File Tests  /////
TEST(ParseFileTests, ParseSuccessTest)
{
    void *kvr = KVR_create();
    EXPECT_TRUE(trySuccess(kvr, "test_parse1.kv"));

    KVR_delete(kvr);
}


TEST(ParseFileTests, ParseFailTest1)
{
    void *kvr = KVR_create();
    KVR_Status error = KVR_ParseFileError;

    EXPECT_TRUE(tryFailure(kvr, "test_parse2.kv", error));

    KVR_delete(kvr);
}


TEST(ParseFileTests, ParseFailTest2)
{
    void *kvr = KVR_create();
    KVR_Status error = KVR_ParseFileError;

    EXPECT_TRUE(tryFailure(kvr, "test_parse3.kv", error));

    KVR_delete(kvr);
}


TEST(ParseFileTests, ParseFailTest3)
{
    void *kvr = KVR_create();
    KVR_Status error = KVR_ParseFileError;

    EXPECT_TRUE(tryFailure(kvr, "test_parse4.kv", error));

    KVR_delete(kvr);
}


/////  Find Key/Value Tests  /////
TEST(KeyValueTests, KeyValueSuccessTest)
{
    void *kvr = KVR_create();
    
    EXPECT_TRUE(trySuccess(kvr, "test_kv.kv"));

    EXPECT_TRUE(tryKeyValueSuccessString(kvr, "key1", "string"));
    EXPECT_TRUE(tryKeyValueSuccessInt(kvr, "key2", 10));
    EXPECT_TRUE(tryKeyValueSuccessDouble(kvr, "key3", 10.0));
    EXPECT_TRUE(tryKeyValueSuccessFloat(kvr, "key3", 10.0f));
    EXPECT_TRUE(tryKeyValueSuccessBool(kvr, "key4", true));

    KVR_delete(kvr);
}


TEST(KeyValueTests, KeyDNETest)
{
    void *kvr = KVR_create();
    KVR_Status error = KVR_KeyNotFound;

    EXPECT_TRUE(trySuccess(kvr, "test_kv.kv"));

    EXPECT_TRUE(tryKeyValueFailureString(kvr, "key_dne", error));
    EXPECT_TRUE(tryKeyValueFailureInt(kvr, "key_dne", error));
    EXPECT_TRUE(tryKeyValueFailureDouble(kvr, "key_dne", error));
    EXPECT_TRUE(tryKeyValueFailureFloat(kvr, "key_dne", error));
    EXPECT_TRUE(tryKeyValueFailureBool(kvr, "key_dne", error));

    KVR_delete(kvr);
}


TEST(KeyValueTests, ValueConversionTest)
{
    void *kvr = KVR_create();
    KVR_Status error = KVR_ConversionError;

    EXPECT_TRUE(trySuccess(kvr, "test_kv.kv"));

    EXPECT_TRUE(tryKeyValueFailureInt(kvr, "key1", error));
    EXPECT_TRUE(tryKeyValueFailureDouble(kvr, "key1", error));
    EXPECT_TRUE(tryKeyValueFailureFloat(kvr, "key1", error));
    EXPECT_TRUE(tryKeyValueFailureBool(kvr, "key1", error));

    KVR_delete(kvr);
}


/////  Main  /////
int main(int argc, char **argv)
{
    ::testing ::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

