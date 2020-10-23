//
// Created by lepouki on 10/12/2020.
//

#include <cstdio>

#include "lepong/Assert.h"
#include "lepong/Log.h"

namespace lepong::Log
{

static FILE* sLog = nullptr;

bool Init() noexcept
{
    LEPONG_ASSERT_OR_RETURN_VAL(!sLog, false);

    return !fopen_s(&sLog, "lepong.log", "w");
}

void Cleanup() noexcept
{
    LEPONG_ASSERT_OR_RETURN(sLog);

    fclose(sLog);
    sLog = nullptr;
}

void Log(const char* message) noexcept
{
    LEPONG_ASSERT_OR_RETURN(sLog && message);

    fputs(message, sLog);
    fputc('\n', sLog); // Good enough for our needs.
}

} // namespace lepong::Log
