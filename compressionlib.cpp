#include"compressionlib.h"

void showHelp(std::string progname)
{
        std::cout<<"Zlib Compression \n \
        A standalone executable in C++ that uses zlib compression to compress input strings/files.\n \
        Usage: "<< progname << " -f <input_file> \n \
        -o <output_file>-<mode> \n \
        \t MODES : \n \
        \t \t zlib: DEFAULT mode using zlib\n \
        \t \t zstd: To use the zstd library by meta\
        OR -i [Interactive Mode] " << std::endl;
}
bool compressFile(const std::string& inputFilename, const std::string& outputFilename, int mode = 0) {
    
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
    if (mode == 1)
    {
        std::cout<<"Using zstd here"<<std::endl;
        bool zstdcompress = zstdCompressor(inputFile,outputFile);
        return zstdcompress;
    }
    else
    {
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
    int flush;
    do {
        // Read a chunk of data from the input file
        inputFile.read(in, CHUNK_SIZE);
        flush  = inputFile.eof() ? Z_FINISH : Z_NO_FLUSH;
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
            stat = deflate(&streamzlib, flush);
            bytesWritten = CHUNK_SIZE - streamzlib.avail_out;
            outputFile.write(out, bytesWritten);
        } while (streamzlib.avail_out == 0);
    } while (flush != Z_FINISH);
    // Finalize the zlib stream
    deflateEnd(&streamzlib);
    inputFile.close();
    outputFile.close();
    
    if (stat != Z_STREAM_END) // checking for errors
    {
        std::cerr<<"False positive error"<<std::endl;
        return false;
    }

    }
    
    return true;
}
bool compressString(const std::string& inputString,const std::string& outputFilename, int mode = 0)
{
    std::ofstream outputFile(outputFilename.c_str(), std::ios::binary);
    if (!outputFile) {
        std::cerr << "Error: output file not found. Please check path " << outputFilename << std::endl;
        return false;
    }
    if (mode == 1)
    {
        std::cout<<"Using zstd here"<<std::endl;
        bool zstdcompressStr = zstdCompressorString(inputString,outputFilename);
        return zstdcompressStr;
    }
    else
    {
    z_stream zstringStream;
    memset(&zstringStream, 0, sizeof(zstringStream));

    if (deflateInit(&zstringStream, Z_DEFAULT_COMPRESSION) != Z_OK)
    {
        std::cerr << "Error: zlib Stream Init Failed" << std::endl;
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
    std::cout << std::dec << std::endl;
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
}

bool zstdCompressor(std::ifstream& ifs,std::ofstream& ofs)
{
    size_t bufferSize = ZSTD_CStreamInSize() + ZSTD_CStreamOutSize();
    std::vector<char> bufferForFile(bufferSize);

    
    ZSTD_CCtx* zcompressorContextFile = ZSTD_createCCtx();
    if (!zcompressorContextFile) {
        std::cerr << "The  ZSTD Compression Context Can not be initialized" << std::endl;
        return false;
    }

    
    while (ifs) {
        
        ifs.read(bufferForFile.data(), bufferForFile.size());
        const size_t bytesRead = ifs.gcount();
        if (bytesRead == 0) {
            break; 
        }

        
        ZSTD_inBuffer in = { bufferForFile.data(), bytesRead, 0 };
        while (in.pos < in.size) {
            ZSTD_outBuffer out = { bufferForFile.data(), bufferForFile.size(), 0 }; // the compression stream buffer
            size_t bytesWrittentoFile = ZSTD_compressStream(zcompressorContextFile, &out, &in);
            if (ZSTD_isError(bytesWrittentoFile)) {
                std::cerr << "Compression of the file with ZSTD has failed" << std::endl;
                ZSTD_freeCCtx(zcompressorContextFile);
                return false;
            }
            ofs.write(bufferForFile.data(), out.pos);
        }
    }
    ZSTD_outBuffer out = { bufferForFile.data(), bufferForFile.size(), 0 };
    size_t bytesWrittenAfterCompression = ZSTD_endStream(zcompressorContextFile, &out);
    if (ZSTD_isError(bytesWrittenAfterCompression)) {
        std::cerr << "Compression of the file with ZSTD has failed" << std::endl;
        ZSTD_freeCCtx(zcompressorContextFile);
        return false;
    }
    ofs.write(bufferForFile.data(), out.pos);
    ZSTD_freeCCtx(zcompressorContextFile);
    return true;
}

bool zstdCompressorString(const std::string& inputString,const std::string& outputFilename){
    std::ofstream outputFile(outputFilename.c_str(), std::ios::binary);
    if (!outputFile) {
        std::cerr << "Error: output file not found. Please check path " << outputFilename << std::endl;
        return "";
    }

    size_t maxCompressedSizeString = ZSTD_compressBound(inputString.size()); // Estimate the bytes for compression
    std::string compressedZSTDString(maxCompressedSizeString, '\0');

    const size_t compressedSize = ZSTD_compress(
        &compressedZSTDString[0],
        compressedZSTDString.size(),
        inputString.data(),
        inputString.size(),
        ZSTD_LEVEL
    );

    // Check for errors
    if (ZSTD_isError(compressedSize)) {
        std::cerr << "Error: ZSTD compression failed: " << ZSTD_getErrorName(compressedSize) << std::endl;
        return "";
    }
    compressedZSTDString.resize(compressedSize);
    outputFile<<compressedZSTDString;
    outputFile.close();
    if (compressedZSTDString.empty()) {
        return false; 
    }
    return true;
}
// Function to get the size of a file in bytes
double sizeByteMetric(const std::string& filename) {
    std::ifstream fileToAnalyze(filename, std::ios::binary);
    fileToAnalyze.seekg(0, std::ios::end);
    double sizeOfFile = (double)fileToAnalyze.tellg();
    return sizeOfFile;
}
