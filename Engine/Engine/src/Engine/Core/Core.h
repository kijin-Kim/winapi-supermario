#pragma once


#include "Logger.h"

#ifdef _DEBUG
#define ASSERT(x, y) if(!(x)) { LOG(y); __debugbreak(); }
#else
#define ASSERT(x, y)
#endif