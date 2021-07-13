/***************************************************************************************************
 * Copyright Five AI 2020.
 * All rights reserved.
 ***************************************************************************************************/

#pragma once

#include "ShmAllocator.h"

#include <boost/interprocess/containers/vector.hpp>

namespace fiveai { namespace platform { namespace shm
{
    template <typename T, typename A = shm::Allocator<T>>
    using Vector = boost::interprocess::vector<T, A>;
}}}

