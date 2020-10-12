//
// Created by lepouki on 10/12/2020.
//

#include "lepong/lepong.h"

int main()
{
    const auto kCanRun = lepong::Init();

    if (kCanRun)
    {
        lepong::Run();
        lepong::Cleanup();
    }
}
