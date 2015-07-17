#ifndef PRECISION_HPP_
#define PRECISION_HPP_
/*
 * Definitions to allow for compiling with either single- or double-precision values.
 *
 * The physics system uses single-precision (float) by default, but can be compiled for double-precision (double) by
 * defining the variable PREC_DOUBLE.
 *
 * Author: Nathan Hemmings
 *
 * Date created: 07/01/2015
 *
 */
#include <float.h>

namespace physics {
	#ifndef PREC_DOUBLE
		typedef float real;
		#define REAL_MAX FLT_MAX;
	#else
		typedef double real;
		#define REAL_MAX DBL_MAX;
	#endif

	#define real_pow powf
}	// End namespace physics

#endif // PRECISION_HPP_
