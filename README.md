# Zlib Compression
A standalone executable in C++ that uses zlib compression to compress input strings/files.

## Prerequisites
### Linux 
`sudo apt install zlib1g-dev -y`

## Compiling  Code
### Using make
1. Clone the repo
2. `cd zlibCompression`
3. `make`

### Alternatively 
The executable can be compiled with<br>
`g++ compressionzlib.cpp compressionlib.cpp -o zlibcompress -lz`

### Usage
`./zlibcompress <INPUT_FILE> <OUTPUTFILE>`