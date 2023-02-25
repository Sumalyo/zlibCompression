# include "compressionlib.h"
/*
TO DO for the project : 
 -  [X] Make it a bit more professional using heafer files , header guards and proper imports
 -  [ ] Add support for input string and input files
 -  [ ] Add better metrics { time to compress, entrophy of file }
        and try to show some cool terminal art if not good graphics
 -  [ ] Lick the zlib documenataion clean and add options for Huffman Coding when ever possible
 -  [X] Add 
            `sudo apt install zlib1g-dev -y` 
            `g++ compressionzlib.cpp compressionlib.cpp -o zlibcompress -lz`
        to the input steps
 -  [X] Add a MAKERFILE and suuport for make
*/

// Function to compress a file using zlib library
// Usage : `./zlibcompress compressionlib.cpp compressionzlib.zlib`


int main(int argc, char* argv[]) {
    if (argc < 5 ) { 
        if (argc ==2 && strcmp(argv[1],"-h")==0)
        {
        showHelp(argv[0]);
        return 1;
  
        }
        else if (argc ==4 && strcmp(argv[1],"-i")==0)
        {
        std::cout<<"Interactive Mode"<<std::endl;
        } 
        else
        {
        std::cerr << "Usage: " << argv[0] << " -f <input_file> \n \
        OR -i [Interactive Mode] \n \
        -o <output_file>" << std::endl;
        return 1;
        }
    }

    
    
    
    // Compress the input file if in argument input style is set to file
    if (strcmp(argv[1],"-f")==0)
    {
    const std::string outputFilename = argv[4];
    const std::string inputFilename = argv[2];
    if (!compressFile(inputFilename, outputFilename)) 
        {
        std::cerr<<"Error while compression file "<<std::endl;
        return 1;
        }
    // const std::streampos originalFileSize = sizeByteMetric(inputFilename);
    // const std::streampos compressedFileSize = sizeByteMetric(outputFilename);
    double originalFileSize = sizeByteMetric(inputFilename);
    double compressedFileSize = sizeByteMetric(outputFilename);
    double compressionRatio = (originalFileSize) / (compressedFileSize);
    
    std::cout << "Original file size: " << originalFileSize << " bytes" << std::endl<< "Compressed file size: " << compressedFileSize<<std::endl;
    std::cout<<"THE Compression ratio is : "<<compressionRatio<<std::endl;
    
    }
    else if (argc ==4 && strcmp(argv[1],"-i")==0) // if input is a string
    {
        std::string inputString;
        std::string outputFilename = argv[3];
        std::cout<<"Enter the Input String"<<std::endl;
        std::cin>>inputString;
        if (!compressString(inputString, outputFilename)) 
        {
        std::cerr<<"Error while compressing string "<<std::endl;
        return 1;
        }
        return 0;
    }
    else
    {
        showHelp(argv[0]);
        return 1;
    }

}

