//Authors
//Yaniel Gonzalez 
//Carlos Caraballo

//This program uses Huffman trees to compress a given string into binary code. Serializes the Huffman tree
//that was build from the string by leafs and branches. Finally, it is able decompress the binary, and serialized 
//codes back into the orignal string.

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <stack>
#include <string.h>

#include "HeapQueue.hpp"
#include "HuffmanBase.hpp"
#include "HuffmanTree.hpp"

HuffmanTree::HuffmanTree():Root(nullptr) {}     // Constructor

HuffmanTree::~HuffmanTree(){                    // Deconstructor
    if(Root != nullptr){
        postorderDelete(Root);                  // Call function to delete the tree with the given root
    }
    Root = nullptr;
}

std::string HuffmanTree::compress(const std::string inputStr){  // Compress the string into binary code

    std::map< char,int> map;                        // Map used to hold the charcters and their frequencies
    for(const char& character : inputStr){          // For-loop that traverses inputStr to build the map

        if(map.find(character) == map.end()){       // If character not found in map insert it 
            map.insert({character,1});

        }else{                                      // Else increase character frequency
            map.at(character)++;
        }
    }
    
    HeapQueue <HuffmanNode*, HuffmanNode::Compare> PriorityQ;           // Declare a Priority Queue using the template from HeapQueue
    for(auto it = map.begin(); it != map.end(); ++it){                  // Build the Huffman Tree nodes using the map and insert them to the Priority Queue

        HuffmanNode* key = new HuffmanNode(it->first , it->second); // build new node from map entry
        PriorityQ.insert(key);  // Insert node to Priority Queue
    }

    while(PriorityQ.size() != 1){                   // Build Huffman tree using the nodes in Priority Queue

        HuffmanNode* leftChild = PriorityQ.min();   // Take the node with least frequency
        PriorityQ.removeMin();                      // Remove node from Prioirty Queue
        HuffmanNode* RightChild = PriorityQ.min();  // Take the node with least frequency
        PriorityQ.removeMin();                      // Remove node from Prioirty Queue

        int ParentFreq =  leftChild->getFrequency() + RightChild->getFrequency();   // Add the frequencies from the two nodes taken
        HuffmanNode* ParentNode = new HuffmanNode('\0', ParentFreq);                // Create a parent node for the two children with their combined frequency 

        ParentNode->left = leftChild;       // link the parent to the left child node
        ParentNode->right = RightChild;     // link the parent to the right child node
        RightChild->parent = ParentNode;    // link the right child node to the parent
        leftChild->parent = ParentNode;     // link the left child node to the parent
        PriorityQ.insert(ParentNode);       // insert the parent node back into the Priority Queue
    }

    Root = PriorityQ.min();                 // Assign the Root of the tree to the last item in the Priority Queue
    PriorityQ.removeMin();                  // Remove the last item in the Prioity Queue

    std::map<char , std::string> Encode;    // Map used to hold the character and its binary code
    std::string result = "";                // temporary string used to hold binary characters
    std::string output;                     // string that will hold the binary code for the inputStr

    BuildCode(Root, result, Encode);        // Call helper function to fill the map with entries
   

    for(const char& c : inputStr){          // For-loop that traverses inputStr to build the output string using the map
        output += Encode.at(c);             // Append corresponding binary code for character c
    }

    return output;                          // Return binary code string
}

void HuffmanTree::BuildCode(HuffmanNode* v, std::string result, std::map<char, std::string>& Encode ){  // Helper function that traverses the Huffman tree in Pre Order

    if(v->isLeaf()){
        Encode.insert({v->getCharacter(), result});     // IF node is a leaf insert the character and binary code to a map entry
    }

    if(v->left != NULL){                                
        BuildCode(v->left, result + "0", Encode);       // If node is a left child append 0 to temporary string and recurse 
    }

    if (v->right != NULL){  
        BuildCode(v->right, result + "1", Encode);      // If node is a right child append 1 to temporary string and recurse 
    }
}

std::string HuffmanTree::serializeTree() const{         // Create a serialized string of leafs and branches

    std::string serialized;                             // This string will hold the resulting serialized code
    series(serialized, Root);                           // Call helper function to traverse the HuffmanTree and fill the serialized string

    return serialized;                                  // Return the resulting stiring
}

void HuffmanTree::series(std::string &serialize, HuffmanNode* v) const{     // Helper Function to traverse Huffman tree in Post Order and build serialized string

    if (v->left != NULL){                   // Traverse Recursively to the left
        series(serialize, v->left);
    }  

    if (v->right != NULL){                  // Traverse Recursively to the right
        series(serialize, v->right);
    }

    if(v->isLeaf()){                        // If node is a leaf append 'L' and the node's character to the serialize string
        serialize += 'L' + std::string(1, v->getCharacter());

    }else{                                 // Else it is a branch and must append 'B'
        if(v->isBranch()){
            serialize += 'B';
        }
    }
}

std::string HuffmanTree::decompress(const std::string inputCode, const std::string serializedTree){     //Decompress back to the original string 

    std::stack<HuffmanNode*> StackTree;     // Declare stack that uses HuffmanNodes
    std::string decompressed= "";           // String that will hold the decompressed string

    for(const char * c = &serializedTree[0]; c< &serializedTree[serializedTree.size()]; c++){   //For-loop that builds a new Huffman tree with the help of a stack

        if(*(c) == 'L'){                                            // If character is equal to 'L':
            c++;                                                    // Move to the next character in the string
            HuffmanNode* LeafNode = new HuffmanNode(*c, 0);         // Create a new node with character c (Leaf node)
            StackTree.push(LeafNode);                               // Place the new node into the stack

        }else if(*c== 'B'){                                         // If character is equal to 'B':
            
            HuffmanNode* BranchNode = new HuffmanNode('\0', 0);     // Create a new node with no content (Branch node)

            BranchNode->right = StackTree.top();                    // Assign the top node of the stack as the right child of Branch node
            StackTree.top()->parent = BranchNode;                   // Link child node to the Branch node
            StackTree.pop();                                        // Remove the node that was just linked off of the stack

            BranchNode->left = StackTree.top();                     // Assign the top node of the stack as the left child of Branch node
            StackTree.top()->parent = BranchNode;                   // Link child node to the Branch node
            StackTree.pop();                                        // Remove the node that was just linked off of the stack

            StackTree.push(BranchNode);                             // Place the new Branch node onto the stack
        }
    }

    HuffmanNode* Root = StackTree.top();                            // Assign Root to be the last element in the stack
    StackTree.pop();                                                // Remove the last element from the stack

    std::map<char , std::string> Decode;                            // Map that will hold a character and its binary code 
    std::string Result ="";                                         // Temporary variable used to hold the binary code
    BuildCode(Root, Result, Decode);                                // Call helper function to fill the map with entries
    
    std::string temp = "";                                          // Temporary variable that will hold binary code to help find entries on the map
    for(const char & c : inputCode){                                // Traverse through inputCode

            temp += std::string(1,c);                               // Append 1 character from inputCode per iteration
            for (const auto& entry : Decode){                       // Traverse through the map entries

                if(entry.second == temp){                           // If the binary code in a map entry matches the code in temp
                    decompressed += entry.first;                    // Append the letter from the map entry to the decompressed string
                    temp= "";                                       // Reset temp back to empty so it can be used to look for the next letter
                    break;                                          // Break the loop so it stops searching the map
                }
            }
    }

    return decompressed;                                            // Return the resulting string
}

void HuffmanTree::postorderDelete(HuffmanNode *v) const{            // Function to delete the Huffman tree in Post Order
    if (v->left != NULL){                                           // Turn to the left node recursively
        postorderDelete(v->left);
    }
    if (v->right != NULL) {                                         // Turn to the right node recursively
        postorderDelete(v->right);
    }
    delete(v);                                                      // Delete node
}

//main
void help() {
	std::cout << "List of operation codes:" << std::endl;
	std::cout <<"\t'h' for help" << std::endl;
	std::cout <<"\t'c' for compression and serialization of data" << std::endl;;
	std::cout <<"\t'q' for quit" << std::endl;
}

void userInput(HuffmanTree &t){
    
    //Input
    std::string data; 
    std::cout << "Enter the data to be compressed and serialized: ";
    getline(std::cin, data);
    

    //Compress
    std::cout << std::endl;
    std::cout << "Compressed form:" << std::endl;
    std::cout << t.compress(data) << std::endl;

    //Serialize
    std::cout << std::endl;
    std::cout << "Serialized tree form:" << std::endl;
    std::cout << t.serializeTree() << std::endl;

    //Decompress
    std::cout << std::endl;
    std::cout << "Decompressing back to original form:" << std::endl;
    std::cout << t.decompress(t.compress(data), t.serializeTree()) << std::endl;
}

