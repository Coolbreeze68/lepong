//
// Created by lepouki on 10/12/2020.
//

#pragma once

#define LEPONG_ASSERT_OR_RETURN(cnd) \
    if (cnd); else return

#define LEPONG_ASSERT_OR_RETURN_VAL(cnd, val) \
    LEPONG_ASSERT_OR_RETURN(cnd) val
