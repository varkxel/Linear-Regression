#include "LinearRegression.h"

struct Sums
{
	double xSum;
	double ySum;
	double xySum;
	double xSqSum;
};

struct Sums CalculateSums(const DataSet* dataSet, const size_t length)
{
	struct Sums sums;
	for(size_t i = 0; i < length; i++)
	{
		const double
			x = (double) dataSet[i].x,
			y = (double) dataSet[i].y;
		
		sums.xSum += x;
		sums.ySum += y;
		sums.xySum += x * y;
		sums.xSqSum += x * x;
	}
	return sums;
}

double Gradient(const DataSet* dataSet, const size_t length)
{
	// Constants
	const double n = (double) length;
	
	// Calculate sums
	const struct Sums sums = CalculateSums(dataSet, length);
	const double
		xSum = sums.xSum,
		ySum = sums.ySum,
		xySum = sums.xySum,
		xSqSum = sums.xSqSum;
	
	// Formula
	double numerator = (ySum * xSqSum) - (xSum * xySum);
	double denominator = n * xSqSum - (xSum * xSum);
	return numerator / denominator;
}

double Constant(const DataSet* dataSet, const size_t length)
{
	// Constants
	const double n = (double) length;
	
	// Calculate sums
	const struct Sums sums = CalculateSums(dataSet, length);
	const double
		xSum = sums.xSum,
		ySum = sums.ySum,
		xySum = sums.xySum,
		xSqSum = sums.xSqSum;
	
	// Formula
	double numerator = (n * xySum) - (xSum * ySum);
	double denominator = (n * xSqSum) - (xSum * xSum);
	return numerator / denominator;
}
