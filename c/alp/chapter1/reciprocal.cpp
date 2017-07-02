#include <cassert>
#include "reciprocal.hpp"

double reciprocal (int i)
{
    // I should be non-zero
#ifndef NDEBUG
    assert (i != 0);
#endif
    return 1.0/i;
}
