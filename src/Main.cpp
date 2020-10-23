//
// Created by lepouki on 10/12/2020.
//

#include "lepong/lepong.h"

int main()
{
    LEPONG_ASSERT_OR_RETURN_VAL(lepong::Init(), -1);

    lepong::Run();
    lepong::Cleanup();
}
