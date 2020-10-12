//
// Created by lepouki on 10/12/2020.
//

#include "lepong/lepong.h"

int main()
{
    if (lepong::Init())
    {
        lepong::Run();
        lepong::Cleanup();
    }
}
