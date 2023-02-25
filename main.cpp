# include "compressionlib.h"
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
    auto start = std::chrono::high_resolution_clock::now();
    if (!compressFile(inputFilename, outputFilename)) 
        {
        std::cerr<<"Error while compression file "<<std::endl;
        return 1;
        }
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    double originalFileSize = sizeByteMetric(inputFilename);
    double compressedFileSize = sizeByteMetric(outputFilename);
    double compressionRatio = (originalFileSize) / (compressedFileSize);
    
    std::cout << "Original file size: " << originalFileSize << " bytes" <<std::endl \
    <<"Compressed file size: " << compressedFileSize<<std::endl;
    std::cout<<"THE Compression ratio is : "<<compressionRatio<<std::endl;
    std::cout<<"Time takes for compression :"<<duration.count() <<" microseconds"<< std::endl;
    
    }
    else if (argc ==4 && strcmp(argv[1],"-i")==0) // if input is a string
    {
        std::string inputString;
        std::string outputFilename = argv[3];
        std::cout<<"Enter the Input String"<<std::endl;
        std::getline(std::cin, inputString);
        auto start = std::chrono::high_resolution_clock::now();
        if (!compressString(inputString, outputFilename)) 
        {
        std::cerr<<"Error while compressing string "<<std::endl;
        return 1;
        }
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        double compressedFileSize = sizeByteMetric(outputFilename);
        double originalStringSize = inputString.size();
        double compressionRatio = originalStringSize/compressedFileSize;
        std::cout << "Original file size: " << originalStringSize << " bytes" <<std::endl \
        <<"Compressed file size: " << compressedFileSize<<std::endl;
        std::cout<<"THE Compression ratio is : "<<compressionRatio<<std::endl;
        std::cout<<"Time takes for compression :"<<duration.count() <<" microseconds"<< std::endl;
        return 0;
    }
    else
    {
        showHelp(argv[0]);
        return 1;
    }

}

