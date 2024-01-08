#include "File.h"

#include <stddef.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

long FileSize(FILE* file)
{
	assert(file != NULL);
	
	// Store the previous position
	const long previousPosition = ftell(file);
	
	// Seek to end and get position
	fseek(file, 0L, SEEK_END);
	long result = ftell(file);
	
	// Go back to the original position
	fseek(file, previousPosition, SEEK_SET);
	
	return result;
}

unsigned int LineCount(const char* buffer)
{
	// Get the size of the data string
	const size_t bufferSize = strlen(buffer);
	
	// Line count starts at 1 as there's always at least 1 line.
	unsigned int lineCount = 1;
	
	// Iterate through & add increment line count with each newline character.
	size_t index = 0;
	do
	{
		if(buffer[index] == '\n') lineCount++;
	}
	while(++index < bufferSize);
	
	return lineCount;
}

char* ReadFile(const char* path)
{
	// Open file for reading
	FILE* file = fopen(path, "r");
	if(file == NULL)
	{
		fprintf(stderr, "File \"%s\" does not exist.\n", path);
		return NULL;
	}
	
	// Create buffer to load file into
	const long size = FileSize(file);
	char* buffer = malloc((size + 1) * sizeof(char));
	buffer[size] = '\0'; // Null terminator
	
	// Read into the buffer
	fread(buffer, size, 1, file);
	
	// Close file as it's no longer needed
	fclose(file);
	
	return buffer;
}
