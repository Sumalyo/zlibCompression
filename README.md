# Zlib Compression
A standalone executable in C++ that uses zlib compression or zstd compression to compress input strings/files.

## Prerequisites
### Linux 
`sudo apt install zlib1g-dev -y`
<br>
### Installing zstd (by meta)
a. `git clone https://github.com/facebook/zstd.git` <br>
b.  `cd zstd` <br>
c. `make install` <br>

## Compiling  Code
### Using make
1. Clone the repo
2. `cd zlibCompression`
3. `make`

### Alternatively 
The executable can be compiled with<br>
`g++ main.cpp compressionlib.cpp -o zlibcompress -lz`

### Usage
![helpPage](help.png)

1. In File Mode <br> 
`./zlibcompress -f <INPUT_FILE> -o <OUTPUT_FILE>` <br>
Eg . To compress a file "example.txt" and store it in "compressed.txt" use:<br>
`./zlibcompress -f example.txt -o compressed.txt`<br>
To run the **ztsd** mode run something like<br>
`./zlibcompress -f compressionlib.cpp -o output.zst -zstd`


2. Interactive Mode: <br>
`./zlibcompress -i -o <OUTPUT_FILE>`<br>
Then enter a string in the terminal prompt. <br>
Then enter the mode for compression hence `0` for compression using zlib `1` for using **zstd**
Eg . To save the compressed string in "compressed.txt"<br>
`./zlibcompress -i -o compressed.txt`<br>
---

![Screenshot](screenshot.png)

