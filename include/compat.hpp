#ifndef COMPAT_H
#define COMPAT_H

#include <config.hpp>

#ifndef MAT_IMPL_NO_STL
# include <cstddef>
# include <cstdio>
# include <algorithm>
# include <limits>
# ifndef MAT_IMPL_NO_MATH
#  include <cmath>
# endif
#else
# include <stddef.h>
#endif

#include <math.hpp>

#endif
