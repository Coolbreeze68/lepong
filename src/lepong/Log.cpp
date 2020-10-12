//
// Created by lepouki on 10/12/2020.
//

#include <cstdio>

#include "lepong/Log.h"

namespace lepong::Log
{

static FILE* sLog = nullptr;

bool Init() noexcept
{
    if (sLog)
    {
        return false;
    }

    fopen_s(&sLog, "lepong.log", "w");

    if (sLog)
    {
        Log("Log file begin.");
    }

    return sLog;
}

void Cleanup() noexcept
{
    if (sLog)
    {
        Log("Log file end.");
        fclose(sLog);
        sLog = nullptr;
    }
}

void Log(const char* message) noexcept
{
    if (sLog && message)
    {
        fputs(message, sLog);
        fputc('\n', sLog);
    }
}

} // namespace lepong::Log
