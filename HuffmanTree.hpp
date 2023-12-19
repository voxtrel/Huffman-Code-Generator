//Authors:
//Yaniel Gonzalez
//Carlos Caraballo

// Header file for the HuffmanTree.cpp file

#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H
#include <map>
#include "HeapQueue.hpp"
#include "HuffmanBase.hpp"

class HuffmanTree : public HuffmanTreeBase{

    public:
    std::string compress(const std::string inputStr);   // Compresses a given string into a binary code
    std::string serializeTree() const;                  // Uses the Huffman tree to serialize it into leafs and branches
    std::string decompress(const std::string inputCode, const std::string serializedTree); // Use the binary code and serialized string to obtain the original string

    HuffmanTree();  //Constructor 
    ~HuffmanTree(); //Deconstructor
    void BuildCode(HuffmanNode* v, std::string result ,std::map<char, std::string>& Encode ); // Helper function that traverses the tree in Pre Order to build the map with binary codes 
    void series(std::string &serialize, HuffmanNode* v) const; // Helper function that traverses the tree in Post Order to serialize the tree into leafs and branches
    void postorderDelete(HuffmanNode *v) const; // Recursive delete all nodes in the tree in Post Order

    private:
    HuffmanNode* Root; // Root for the Huffman tree
};

//Main
void help();
void userInput(HuffmanTree &t);

#endif