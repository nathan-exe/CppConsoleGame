#pragma once
#include "src/WindowsException.h"

#define THROW_IF_FAILED(X, msg)  if (X==FALSE) throw WindowsException(#msg)