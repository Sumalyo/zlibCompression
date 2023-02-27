#ifndef COMPRESS_H
#include <iostream>  
#include <fstream>  // for file handling 
#include <cstring>  // to use some unsafe C things like memset
#include <sstream>
#include <zlib.h>  // for compression
#include <string.h> //for hadling string operations
#include <chrono>
#include <zstd.h>
#include <vector>
// #define CHUNK_SIZE 32768
#define CHUNK_SIZE 32768
#define ZSTD_LEVEL 15
bool compressFile(const std::string& inputFilename, const std::string& outputFilename,int mode);
double sizeByteMetric(const std::string& filename);
bool compressString(const std::string& inputString,const std::string& outputFilename, int mode);
bool zstdCompressor(std::ifstream& ifs,std::ofstream& ofs);
bool zstdCompressorString(const std::string& input,const std::string& outputFilename);
void showHelp(std::string progname);
#endif