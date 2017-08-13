#include "../include/KeyValueReader.h"
#include "TestHelpers.h"
#include <gtest/gtest.h>


/////  Open File Tests  /////
TEST(OpenFileTests, DoesNotExistTest)
{
    void *kvr = createKeyValueReader();
    KVR_Error error = KVR_Error_OpenFileError;

    EXPECT_TRUE(tryFailure(kvr, "test_does_not_exist.kv", error));
}


TEST(OpenFileTests, FileExistsTest)
{
    void *kvr = createKeyValueReader();
    EXPECT_TRUE(trySuccess(kvr, "test_open.kv"));
}


TEST(OpenFileTests, FileAlreadyOpenTest)
{
    void *kvr = createKeyValueReader();
    KVR_Error error = KVR_Error_AlreadyReadAFile;

    EXPECT_TRUE(trySuccess(kvr, "test_open.kv"));
    EXPECT_TRUE(tryFailure(kvr, "test_open.kv", error));
}


/////  Parse File Tests  /////
TEST(ParseFileTests, ParseSuccessTest)
{
    void *kvr = createKeyValueReader();
    EXPECT_TRUE(trySuccess(kvr, "test_parse1.kv"));
}


TEST(ParseFileTests, ParseFailTest1)
{
    void *kvr = createKeyValueReader();
    KVR_Error error = KVR_Error_ParseFileError;

    EXPECT_TRUE(tryFailure(kvr, "test_parse2.kv", error));
}


TEST(ParseFileTests, ParseFailTest2)
{
    void *kvr = createKeyValueReader();
    KVR_Error error = KVR_Error_ParseFileError;

    EXPECT_TRUE(tryFailure(kvr, "test_parse3.kv", error));
}


TEST(ParseFileTests, ParseFailTest3)
{
    void *kvr = createKeyValueReader();
    KVR_Error error = KVR_Error_ParseFileError;

    EXPECT_TRUE(tryFailure(kvr, "test_parse4.kv", error));
}


/////  Find Key/Value Tests  /////
TEST(KeyValueTests, KeyValueSuccessTest)
{
    void *kvr = createKeyValueReader();
    
    EXPECT_TRUE(trySuccess(kvr, "test_kv.kv"));

    EXPECT_TRUE(tryKeyValueSuccessString(kvr, "key1", "string"));
    EXPECT_TRUE(tryKeyValueSuccessInt(kvr, "key2", 10));
    EXPECT_TRUE(tryKeyValueSuccessDouble(kvr, "key3", 10.0));
    EXPECT_TRUE(tryKeyValueSuccessFloat(kvr, "key3", 10.0f));
    EXPECT_TRUE(tryKeyValueSuccessBool(kvr, "key4", true));
}


TEST(KeyValueTests, KeyDNETest)
{
    void *kvr = createKeyValueReader();
    KVR_Error error = KVR_Error_KeyNotFound;

    EXPECT_TRUE(trySuccess(kvr, "test_kv.kv"));

    EXPECT_TRUE(tryKeyValueFailureString(kvr, "key_dne", error));
    EXPECT_TRUE(tryKeyValueFailureInt(kvr, "key_dne", error));
    EXPECT_TRUE(tryKeyValueFailureDouble(kvr, "key_dne", error));
    EXPECT_TRUE(tryKeyValueFailureFloat(kvr, "key_dne", error));
    EXPECT_TRUE(tryKeyValueFailureBool(kvr, "key_dne", error));
}


TEST(KeyValueTests, ValueConversionTest)
{
    void *kvr = createKeyValueReader();
    KVR_Error error = KVR_Error_StringConversionError;

    EXPECT_TRUE(trySuccess(kvr, "test_kv.kv"));

    EXPECT_TRUE(tryKeyValueFailureInt(kvr, "key1", error));
    EXPECT_TRUE(tryKeyValueFailureDouble(kvr, "key1", error));
    EXPECT_TRUE(tryKeyValueFailureFloat(kvr, "key1", error));
    EXPECT_TRUE(tryKeyValueFailureBool(kvr, "key1", error));
}


/////  Main  /////
int main(int argc, char **argv)
{
    ::testing ::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

