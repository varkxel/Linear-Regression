#ifndef LINEARREGRESSION_FILE_H
#define LINEARREGRESSION_FILE_H

#include <stddef.h>
#include <stdio.h>

/// Gets the size of the given file.
/// \param file The file to read.
/// \return The size of the given file.
long FileSize(FILE* file);

/// Counts the amount of lines in the given buffer.
/// \param buffer The buffer to read and count the lines in.
/// \return The amount of lines in the buffer.
unsigned int LineCount(const char* buffer);

/// Reads a file into an \b allocated buffer.
/// Remember to free this buffer.
/// \param path The path to the file to read.
/// \return The buffer containing the contents of the given file,
/// or NULL if the file isn't found.
/// Remember to free this buffer.
char* ReadFile(const char* path);

#endif