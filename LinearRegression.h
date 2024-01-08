#ifndef LINEARREGRESSION_LINEARREGRESSION_H
#define LINEARREGRESSION_LINEARREGRESSION_H

#include <stddef.h>

/*
 * This would be more efficient to store the
 * Xs together, and the Ys together for vectorisation.
 * It would also allow for easier intrinsics.
 *
 * But for simplicity, this will work fine.
 */

typedef struct
{
	long x;
	long y;
}
DataSet;

double Gradient(const DataSet* dataSet, size_t length);
double Constant(const DataSet* dataSet, size_t length);

#endif