/*
    Copyright (c) 2020-2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/FileSystem/blob/master/LICENSE.txt
*/

#include "ErrorCategory.h"

namespace Ishiko
{
namespace FileSystem
{

const ErrorCategory& ErrorCategory::Get() noexcept
{
    static ErrorCategory theCategory;
    return theCategory;
}

const char* ErrorCategory::name() const noexcept
{
    return "Ishiko::FileSystem::ErrorCategory";
}

void Fail(Error& error, ErrorCategory::EErrorValues value) noexcept
{
    error.fail(value, ErrorCategory::Get());
}

void Fail(Error& error, ErrorCategory::EErrorValues value, const std::string& message, const char* file,
    int line) noexcept
{
    error.fail(value, ErrorCategory::Get(), message, file, line);
}

}
}
