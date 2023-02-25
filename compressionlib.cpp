#include"compressionlib.h"

void showHelp(std::string progname)
{
        std::cout<<"Zlib Compression \n \
        A standalone executable in C++ that uses zlib compression to compress input strings/files.\n \
        Usage: "<< progname << " -f <input_file> \n \
            OR -i [Interactive Mode] \n \
        -o <output_file>" << std::endl;
}
bool compressFile(const std::string& inputFilename, const std::string& outputFilename) {
    
    std::ifstream inputFile(inputFilename.c_str(), std::ios::binary);
    if (!inputFile) {
        std::cerr <<"Error: input file not found. Please check path " << inputFilename << std::endl;
        return false;
    }

    
    std::ofstream outputFile(outputFilename.c_str(), std::ios::binary);
    if (!outputFile) {
        std::cerr << "Error: output file not found. Please check path " << outputFilename << std::endl;
        return false;
    }

    z_stream streamzlib;
    std::memset(&streamzlib, 0, sizeof(streamzlib));
    if (deflateInit(&streamzlib, Z_BEST_COMPRESSION) != Z_OK) {
        std::cerr << "Error: zlib Stream Init Failed" << std::endl;
        return false;
    }

    // Compress the input file and write the output to the output file
    
    char in[CHUNK_SIZE];
    char out[CHUNK_SIZE];
    int bytesRead = 0;
    int bytesWritten = 0;
    int stat;
    do {
        // Read a chunk of data from the input file
        inputFile.read(in, CHUNK_SIZE);
        bytesRead = inputFile.gcount();
        if (bytesRead == 0) {
            break;
        }
        // Compress the chunk of data using zlib
        streamzlib.avail_in = bytesRead;
        streamzlib.next_in = (Bytef*)in;
        do {
            streamzlib.avail_out = CHUNK_SIZE;
            streamzlib.next_out = (Bytef*)out;
            stat = deflate(&streamzlib, Z_FINISH);
            bytesWritten = CHUNK_SIZE - streamzlib.avail_out;
            outputFile.write(out, bytesWritten);
        } while (streamzlib.avail_out == 0 && stat == Z_OK);
    } while (bytesRead > 0 );

    // Finalize the zlib stream
    deflateEnd(&streamzlib);
    inputFile.close();
    outputFile.close();
    
    if (stat != Z_STREAM_END) // checking for errors
    {
        std::cerr<<"False positive error"<<std::endl;
        return false;
    }
    
    return true;
}
bool compressString(const std::string& inputString,const std::string& outputFilename)
{
    z_stream zstringStream;
    memset(&zstringStream, 0, sizeof(zstringStream));

    if (deflateInit(&zstringStream, Z_DEFAULT_COMPRESSION) != Z_OK)
    {
        std::cerr << "Error: zlib Stream Init Failed" << std::endl;
        return false;
    }
    
    std::ofstream outputFile(outputFilename.c_str(), std::ios::binary);
    if (!outputFile) {
        std::cerr << "Error: output file not found. Please check path " << outputFilename << std::endl;
        return false;
    }
    zstringStream.avail_in = inputString.size();
    zstringStream.next_in = (Bytef*)inputString.c_str();
    int stat;
    
    char bufferStr[CHUNK_SIZE];
    do{
        
        zstringStream.next_out = (Bytef*)bufferStr;
        zstringStream.avail_out = CHUNK_SIZE;

        stat = deflate(&zstringStream,Z_FINISH);
        int bytesWritten = CHUNK_SIZE - zstringStream.avail_out;
        outputFile.write(bufferStr, bytesWritten);
    }while(zstringStream.avail_out == 0 && stat == Z_OK);
    deflateEnd(&zstringStream);
    if (stat != Z_STREAM_END) // checking for errors
    {
        std::cerr<<"False positive error"<<std::endl;
        return false;
    }
    outputFile.close();
    return true;
}



// Function to get the size of a file in bytes
double sizeByteMetric(const std::string& filename) {
    std::ifstream fileToAnalyze(filename, std::ios::binary);
    fileToAnalyze.seekg(0, std::ios::end);
    double sizeOfFile = (double)fileToAnalyze.tellg();
    return sizeOfFile;
}
