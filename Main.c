#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>

#include <stdio.h>

#include <StringHandling.h>

#include "File.h"
#include "Parser.h"

/// Prompts the user for a double value.
/// \param prompt The prompt to print when trying to get the value.
/// \param result The resulting value given, or undefined behaviour if failed.
/// \return \b true if a \b double value was successfully read. \b false otherwise.
bool PromptDouble(const char* prompt, double* result)
{
	// Get string
	char* buffer;
	if(!PromptString_Buffer(prompt, &buffer, 128))
	{
		if(buffer != NULL) free(buffer);
		return false;
	}
	
	// Parse to double
	char* end;
	*result = strtod(buffer, &end);
	
	// Successful if the end pointer is further along than the start of the buffer.
	bool success = end != buffer;
	
	free(buffer);
	return success;
}

int main(int argc, char** argv)
{
	// Get the path to the dataset
	char* path;
	if(argc >= 2) ConcatString((const char**) &argv[1], argc - 1, &path);
	else path = PromptStringRepeat("Enter path to dataset: ");
	
	// Load file into buffer
	char* result = ReadFile(path);
	free(path);
	if(result == NULL) return EXIT_FAILURE;
	
	// Parse/Generate dataset
	DataSet* set = NULL;
	size_t setEntries = LoadDataSet(&set, result);
	if(set == NULL)
	{
		fprintf(stderr, "Failed to parse dataset.");
		return EXIT_FAILURE;
	}
	
	// Text buffer no longer needed
	free(result);
	
	// Calculate the values and print
	double m = Gradient(set, setEntries);
	double c = Constant(set, setEntries);
	
	// Set no longer needed
	free(set);
	
	// Print the formula
	printf("Formula: y = %lfx + %lf\n", m, c);
	
	// Calculate a Y value from a given X value
	double x;
	if(!PromptDouble("X Value: ", &x))
	{
		printf("No value given, exiting.\n");
		return EXIT_SUCCESS;
	}
	double y = m * x + c;
	printf("Y Value: %lf\n", y);
	
	return EXIT_SUCCESS;
}
