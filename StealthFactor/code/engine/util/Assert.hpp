#pragma once

#include <cassert>

#define UNUSED(X) (void)(X)

#ifdef _DEBUG
#define ASSERT assert
#else
#define ASSERT UNUSED
#endif
