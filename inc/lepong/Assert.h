//
// Created by lepouki on 10/12/2020.
//

#pragma once

#include "Log.h"

///
/// I prefer to keep asserts pretty soft for this project.<br>
/// The usual debug break seems a bit overkill.
///
#define LEPONG_ASSERT_OR_RETURN(cnd, val, msg) if (cnd); else { Log::Log("%s: " msg, __FUNCDNAME__); return val; }
