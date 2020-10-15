//
// Created by lepouki on 10/12/2020.
//

#pragma once

#define LEPONG_ATTRIBUTE(name) \
    [[name]]

#define LEPONG_MAYBE_UNUSED \
    LEPONG_ATTRIBUTE(maybe_unused)

#define LEPONG_NODISCARD \
    LEPONG_ATTRIBUTE(nodiscard)

#define LEPONG_FALLTHROUGH \
    LEPONG_ATTRIBUTE(fallthrough)
