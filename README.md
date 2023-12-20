# Huffman-Code-Generator
AUTHORS:

Yaniel Gonzalez

Carlos Caraballo


OVERVIEW

This C++ project implements a Huffman coding algorithm to compress and decompress data efficiently.
Huffman coding is a widely used algorithm for lossless data compression. The program utilizes maps, trees, 
and a priority queue to construct Huffman codes for each input symbol, allowing for effective compression 
and subsequent decompression without any loss of data.


FEATURES 

-Huffman Coding: 
Utilizes the Huffman coding algorithm to create variable-length binary codes for each input symbol based 
on their frequencies.

-Compression: 
Compresses input data using the generated Huffman codes, reducing the overall size of the data.

-Serialized Tree:
Constructs a serialized code of the binary tree built from the input, using 'B' for branches and 'L' for leafs.

-Decompression:
Decompresses previously compressed data, reconstructing the original input without any loss, using the binary codes,
and the serialized tree form.


DEPENDENCIES

This project relies on a C++ compiler that supports the C++11 standard or later.


USAGE

Compilation:

To compile the program, use the following command:

    g++ -Wall -std=c++17 HuffmanTree.cpp HuffmanBase.cpp main.cpp

Input:

The program includes a user interface to execute its functions.

-Enter 'h' to read the list of commands to that the program includes
    
-Enter 'c' to use the mentioned features, and enter input when instructed
    
-Enter 'q' to quit the program


CODE STRUCTURE

-'main.cpp': Contain the main function which implements the user interface.

-'HuffmanBase.cpp' and 'HuffmanBase.hpp': Contains the implementation of the Tree class and its methods.

-'HuffmanTree.cpp' and 'HuffmanTree.hpp': Contains the implementation of the Compress, Serialize Tree,
  and Decompress functions.
  
-'HeapQueue.hpp': Contains the implementation of a Heap Queue by defining a tree and its methods.


ACKNOLEDGEMENTS

The project was inspired by the Huffman coding algorithm, a fundamental concept in data compression.

