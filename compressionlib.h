#ifndef COMPRESS_H
#include <iostream>  
#include <fstream>  // for file handling 
#include <cstring>  // to use some unsafe C things like memset
#include <sstream>
#include <zlib.h>  // for compression
#include <string.h> //for hadling string operations
#include <chrono>
// #define CHUNK_SIZE 32768
#define CHUNK_SIZE 32768
bool compressFile(const std::string& inputFilename, const std::string& outputFilename);
double sizeByteMetric(const std::string& filename);
bool compressString(const std::string& inputString,const std::string& outputFilename);
void showHelp(std::string progname);
#endif