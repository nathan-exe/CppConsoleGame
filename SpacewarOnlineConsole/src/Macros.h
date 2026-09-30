#pragma once
#include <stdexcept>


#define THROW_IF_FAILED(X, msg)  if (X==FALSE) throw std::logic_error(#msg)