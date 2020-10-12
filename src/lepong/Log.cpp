//
// Created by lepouki on 10/12/2020.
//

#include <cstdio>

#include "lepong/Assert.h"

namespace lepong::Log
{

static bool sInitialized = false;
static FILE* sLog;

bool Init() noexcept
{
    if (sInitialized)
    {
        return false;
    }

    sInitialized = !fopen_s(&sLog, "lepong.log", "w");

    if (sInitialized)
    {
        Log::Log("Log file begin.");
    }

    return sInitialized;
}

void Cleanup() noexcept
{
    if (sInitialized)
    {
        Log::Log("Log file end.");
        fclose(sLog);
        sInitialized = false;
    }
}

void Log(const char* message) noexcept
{
    if (sInitialized)
    {
        LEPONG_ASSERT_OR_RETURN(message,
            /* void */,
            "Message can't be nullptr.");

        fputs(message, sLog);
        fputc('\n', sLog);
    }
}

} // namespace lepong::Log
