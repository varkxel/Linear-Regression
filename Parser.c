#include "Parser.h"

#include "File.h"

#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

bool IsEnd(char character)
{
	return character == '\n' || character == '\0';
}

bool IsInteger(char character)
{
	return isdigit(character) || character == '-' || character == '+';
}

size_t LoadDataSet(DataSet** dataSet, const char* buffer)
{
	const size_t lineCount = LineCount(buffer);
	
	// Allocate base amount
	*dataSet = malloc(lineCount * sizeof(DataSet));
	size_t setEntries = 0;
	
	size_t index = 0;
	for(size_t line = 0; line < lineCount; line++)
	{
		const char* startPosition = &buffer[index];
		const char* commaPosition = NULL;
		
		do
		{
			if(buffer[index] == ',') commaPosition = &buffer[index];
		}
		while(!IsEnd(buffer[++index]));	// Iterate to next line
		
		// Continue to next line if couldn't find a comma as the line is invalid.
		if(commaPosition == NULL) goto NextLine;
		
		// Get x value
		long x = strtol(startPosition, NULL, 10);
		
		// Increment to start of Y
		const char* yPos = commaPosition;
		while(!IsInteger(yPos[0]))
		{
			if(IsEnd(yPos[0])) goto NextLine;
			else yPos++;
		}
		
		// Get y value
		long y = strtol(yPos, NULL, 10);
		
		// Add to dataset
		(*dataSet)[setEntries++] = (DataSet) { .x = x, .y = y };
		
		// Shortcut to nextline check
		NextLine: {};
		// Increment by one if still on newline
		if(buffer[index] == '\n') index++;
	}
	
	*dataSet = realloc(*dataSet, setEntries * sizeof(DataSet));
	return setEntries;
}
