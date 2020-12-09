//
// Created by lepouki on 10/12/2020.
//

#pragma once

#include "Log.h"

#define LEPONG_CHECK_OR_RETURN(cnd) \
    if (cnd); else return

#define LEPONG_CHECK_OR_RETURN_VAL(cnd, val) \
    LEPONG_CHECK_OR_RETURN(cnd) val

#define LEPONG_CHECK_OR_LOG(cnd, msg) \
    if (cnd); else Log::Log(msg)
