#include "../src/KeyValueReader.h"
#include "TestHelpers.h"
#include <gtest/gtest.h>


/////  Open File Tests  /////
TEST(OpenFileTests, DoesNotExistTest)
{
    GarrettSoftware::KeyValueReader kvr;
    GarrettSoftware::KeyValueReader::Exception e = 
        GarrettSoftware::KeyValueReader::ExceptionOpenFileError;

    EXPECT_TRUE(tryFailure(kvr, "test_does_not_exist.kv", e));
}


TEST(OpenFileTests, FileExistsTest)
{
    GarrettSoftware::KeyValueReader kvr;
    EXPECT_TRUE(trySuccess(kvr, "test_open.kv"));
}


TEST(OpenFileTests, FileAlreadyOpenTest)
{
    GarrettSoftware::KeyValueReader kvr;
    GarrettSoftware::KeyValueReader::Exception e = 
        GarrettSoftware::KeyValueReader::ExceptionAlreadyReadAFile;

    EXPECT_TRUE(trySuccess(kvr, "test_open.kv"));
    EXPECT_TRUE(tryFailure(kvr, "test_open.kv", e));
    
    kvr.reset();
    EXPECT_TRUE(trySuccess(kvr, "test_open.kv"));
}


/////  Parse File Tests  /////
TEST(ParseFileTests, ParseSuccessTest)
{
    GarrettSoftware::KeyValueReader kvr;
    EXPECT_TRUE(trySuccess(kvr, "test_parse1.kv"));
}


TEST(ParseFileTests, ParseFailTest1)
{
    GarrettSoftware::KeyValueReader kvr;
    GarrettSoftware::KeyValueReader::Exception e = 
        GarrettSoftware::KeyValueReader::ExceptionParseFileError;

    EXPECT_TRUE(tryFailure(kvr, "test_parse2.kv", e));
}


TEST(ParseFileTests, ParseFailTest2)
{
    GarrettSoftware::KeyValueReader kvr;
    GarrettSoftware::KeyValueReader::Exception e = 
        GarrettSoftware::KeyValueReader::ExceptionParseFileError;

    EXPECT_TRUE(tryFailure(kvr, "test_parse3.kv", e));
}


TEST(ParseFileTests, ParseFailTest3)
{
    GarrettSoftware::KeyValueReader kvr;
    GarrettSoftware::KeyValueReader::Exception e = 
        GarrettSoftware::KeyValueReader::ExceptionParseFileError;

    EXPECT_TRUE(tryFailure(kvr, "test_parse4.kv", e));
}


/////  Find Key/Value Tests  /////
TEST(KeyValueTests, KeyValueSuccessTest)
{
    GarrettSoftware::KeyValueReader kvr;
    
    EXPECT_TRUE(trySuccess(kvr, "test_kv.kv"));

    EXPECT_TRUE(tryKeyValueSuccessString(kvr, "key1", "string"));
    EXPECT_TRUE(tryKeyValueSuccessInt(kvr, "key2", 10));
    EXPECT_TRUE(tryKeyValueSuccessDouble(kvr, "key3", 10.0));
    EXPECT_TRUE(tryKeyValueSuccessFloat(kvr, "key3", 10.0f));
    EXPECT_TRUE(tryKeyValueSuccessBool(kvr, "key4", true));
}


TEST(KeyValueTests, KeyDNETest)
{
    GarrettSoftware::KeyValueReader kvr;
    GarrettSoftware::KeyValueReader::Exception e = 
        GarrettSoftware::KeyValueReader::ExceptionKeyNotFound;

    EXPECT_TRUE(trySuccess(kvr, "test_kv.kv"));

    EXPECT_TRUE(tryKeyValueFailureString(kvr, "key_dne", e));
    EXPECT_TRUE(tryKeyValueFailureInt(kvr, "key_dne", e));
    EXPECT_TRUE(tryKeyValueFailureDouble(kvr, "key_dne", e));
    EXPECT_TRUE(tryKeyValueFailureFloat(kvr, "key_dne", e));
    EXPECT_TRUE(tryKeyValueFailureBool(kvr, "key_dne", e));
}


TEST(KeyValueTests, ValueConversionTest)
{
    GarrettSoftware::KeyValueReader kvr;
    GarrettSoftware::KeyValueReader::Exception e = 
        GarrettSoftware::KeyValueReader::ExceptionStringConversionError;

    EXPECT_TRUE(trySuccess(kvr, "test_kv.kv"));

    EXPECT_TRUE(tryKeyValueFailureInt(kvr, "key1", e));
    EXPECT_TRUE(tryKeyValueFailureDouble(kvr, "key1", e));
    EXPECT_TRUE(tryKeyValueFailureFloat(kvr, "key1", e));
    EXPECT_TRUE(tryKeyValueFailureBool(kvr, "key1", e));
}


/////  Main  /////
int main(int argc, char **argv)
{
    ::testing ::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

