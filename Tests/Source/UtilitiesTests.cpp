/*
    Copyright (c) 2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/FileSystem/blob/master/LICENSE.txt
*/

#include "UtilitiesTests.h"
#include "Ishiko/FileSystem/Utilities.h"
#include "Ishiko/FileSystem/ErrorCategory.h"
#include <boost/filesystem/operations.hpp>

using namespace Ishiko::Tests;

UtilitiesTests::UtilitiesTests(const TestNumber& number, const TestEnvironment& environment)
    : TestSequence(number, "Utilities tests", environment)
{
    append<HeapAllocationErrorsTest>("Exists test 1", ExistsTest1);
    append<HeapAllocationErrorsTest>("Exists test 2", ExistsTest2);
    append<HeapAllocationErrorsTest>("Exists test 3", ExistsTest3);
    append<HeapAllocationErrorsTest>("IsDirectory test 1", IsDirectoryTest1);
    append<HeapAllocationErrorsTest>("IsDirectory test 2", IsDirectoryTest2);
    append<HeapAllocationErrorsTest>("IsDirectory test 3", IsDirectoryTest3);
    append<HeapAllocationErrorsTest>("IsEmpty test 1", IsEmptyTest1);
    append<HeapAllocationErrorsTest>("IsEmpty test 2", IsEmptyTest2);
    append<HeapAllocationErrorsTest>("IsEmpty test 3", IsEmptyTest3);
    append<HeapAllocationErrorsTest>("IsEmpty test 4", IsEmptyTest4);
    append<HeapAllocationErrorsTest>("IsEmpty test 5", IsEmptyTest5);
    append<HeapAllocationErrorsTest>("ReadFile test 1", ReadFileTest1);
    append<HeapAllocationErrorsTest>("ReadFile test 2", ReadFileTest2);
    append<HeapAllocationErrorsTest>("ReadFile test 3", ReadFileTest3);
}

void UtilitiesTests::ExistsTest1(Ishiko::Tests::Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "doesnotexist");

    ISHTF_FAIL_IF(Ishiko::FileSystem::Exists(inputPath.string().c_str()));
    ISHTF_PASS();
}

void UtilitiesTests::ExistsTest2(Ishiko::Tests::Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "file1.txt");

    ISHTF_FAIL_IF_NOT(Ishiko::FileSystem::Exists(inputPath.string().c_str()));
    ISHTF_PASS();
}

void UtilitiesTests::ExistsTest3(Ishiko::Tests::Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory());

    ISHTF_FAIL_IF_NOT(Ishiko::FileSystem::Exists(inputPath.string().c_str()));
    ISHTF_PASS();
}

void UtilitiesTests::IsDirectoryTest1(Ishiko::Tests::Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory());

    Ishiko::Error error;
    bool isDir = Ishiko::FileSystem::IsDirectory(inputPath.string().c_str(), error);

    ISHTF_FAIL_IF(error);
    ISHTF_FAIL_IF_NOT(isDir);
    ISHTF_PASS();
}

void UtilitiesTests::IsDirectoryTest2(Ishiko::Tests::Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "file1.txt");

    Ishiko::Error error;
    bool isDir = Ishiko::FileSystem::IsDirectory(inputPath.string().c_str(), error);

    ISHTF_FAIL_IF(error);
    ISHTF_FAIL_IF(isDir);
    ISHTF_PASS();
}

void UtilitiesTests::IsDirectoryTest3(Ishiko::Tests::Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "doesnotexist");

    Ishiko::Error error;
    bool isDir = Ishiko::FileSystem::IsDirectory(inputPath.string().c_str(), error);

    ISHTF_FAIL_IF_NOT(error);
    ISHTF_FAIL_IF_NEQ(error.condition().value(), Ishiko::FileSystem::ErrorCategory::eNotFound);
    ISHTF_FAIL_IF(isDir);
    ISHTF_PASS();
}

void UtilitiesTests::IsEmptyTest1(Ishiko::Tests::Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "empty.txt");

    Ishiko::Error error;
    bool empty = Ishiko::FileSystem::IsEmpty(inputPath.string().c_str(), error);

    ISHTF_FAIL_IF(error);
    ISHTF_FAIL_IF_NOT(empty);
    ISHTF_PASS();
}

void UtilitiesTests::IsEmptyTest2(Ishiko::Tests::Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "file1.txt");

    Ishiko::Error error;
    bool empty = Ishiko::FileSystem::IsEmpty(inputPath.string().c_str(), error);

    ISHTF_FAIL_IF(error);
    ISHTF_FAIL_IF(empty);
    ISHTF_PASS();
}

void UtilitiesTests::IsEmptyTest3(Ishiko::Tests::Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestOutputDirectory() / "empty");
    boost::filesystem::create_directory(inputPath);

    Ishiko::Error error;
    bool empty = Ishiko::FileSystem::IsEmpty(inputPath.string().c_str(), error);

    ISHTF_FAIL_IF(error);
    ISHTF_FAIL_IF_NOT(empty);
    ISHTF_PASS();
}

void UtilitiesTests::IsEmptyTest4(Ishiko::Tests::Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory());

    Ishiko::Error error;
    bool empty = Ishiko::FileSystem::IsEmpty(inputPath.string().c_str(), error);

    ISHTF_FAIL_IF(error);
    ISHTF_FAIL_IF(empty);
    ISHTF_PASS();
}

void UtilitiesTests::IsEmptyTest5(Ishiko::Tests::Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "doesnotexist");

    Ishiko::Error error;
    bool empty = Ishiko::FileSystem::IsEmpty(inputPath.string().c_str(), error);

    ISHTF_FAIL_IF_NOT(error);
    ISHTF_FAIL_IF_NEQ(error.condition().value(), Ishiko::FileSystem::ErrorCategory::eNotFound);
    ISHTF_FAIL_IF(empty);
    ISHTF_PASS();
}

void UtilitiesTests::ReadFileTest1(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "file1.txt");

    Ishiko::Error error;
    const int bufferSize = 10;
    char buffer[bufferSize];
    size_t bytesRead = Ishiko::FileSystem::ReadFile(inputPath.string().c_str(), buffer, bufferSize, error);

    ISHTF_FAIL_IF(error);
    ISHTF_FAIL_IF_NEQ(bytesRead, 5);
    ISHTF_PASS();
}

void UtilitiesTests::ReadFileTest2(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "doesnotexist");

    Ishiko::Error error;
    const int bufferSize = 10;
    char buffer[bufferSize];
    size_t bytesRead = Ishiko::FileSystem::ReadFile(inputPath.string().c_str(), buffer, bufferSize, error);

    ISHTF_FAIL_IF_NOT(error);
    ISHTF_FAIL_IF_NEQ(bytesRead, 0);
    ISHTF_PASS();
}

void UtilitiesTests::ReadFileTest3(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "file1.txt");

    Ishiko::Error error;
    const int bufferSize = 2;
    char buffer[bufferSize];
    size_t bytesRead = Ishiko::FileSystem::ReadFile(inputPath.string().c_str(), buffer, bufferSize, error);

    ISHTF_FAIL_IF_NOT(error);
    ISHTF_FAIL_IF_NEQ(error.condition().value(), Ishiko::FileSystem::ErrorCategory::eBufferOverflow);
    ISHTF_FAIL_IF_NEQ(bytesRead, 5);
    ISHTF_PASS();
}
